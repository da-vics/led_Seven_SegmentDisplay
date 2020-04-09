#include <avr/io.h>
#include <avr/interrupt.h>
#include "buttons.h"

#define DEBUG false

time_compute time_now;
segment_states segment_state;
segmentControl segContorl(&time_now, &segment_state);
time_h initiate_time(&time_now);
ButtonAction buttonOps(&initiate_time, &time_now, &segment_state);

volatile int seconds_counter = 0; /// seconds  indicator
volatile uint32_t seconds_counter2 = 0;
volatile int seconds_temp = 0;

ISR (TIMER1_OVF_vect) {
  ///TCNT1 = 49910;
  TCNT1 = 65520;       /// 1 milli_seconds overflow

  ///TCNT1 = 65534 100us
  ++seconds_counter;
  ++seconds_temp;

  (buttonOps.updateTimeStats() == false) ? ++seconds_counter2 : seconds_counter2;

  if (seconds_counter >= 1000) { /// 1 sec
    segment_state.seconds_state = !segment_state.seconds_state;
    seconds_counter = 0;
  } ////

  if (seconds_counter2 >= 60000) {  /// 1min
    seconds_counter2 = 0;
    if (buttonOps.updateTimeStats() == false)
    {
      ++time_now.time_min_value1;
      initiate_time.count_timer();
    }
  }

  if (seconds_temp >= 3) {
    seconds_temp = 0;
    ++segment_state.switch_seg;
    if (segment_state.switch_seg > segment_state.switch_value)  segment_state.switch_seg = segment_state.switch_lowest;

    switch (segment_state.switch_seg) {
      case 0:
        segment_state.min1_state = 1;
        segment_state.min2_state = 0;
        segment_state.hour1_state = 0;
        segment_state.hour2_state = 0;
        break;

      case 1:
        segment_state.min1_state = 0;
        segment_state.min2_state = 1;
        segment_state.hour1_state = 0;
        segment_state.hour2_state = 0;
        break;

      case 2:
        segment_state.min1_state = 0;
        segment_state.min2_state = 0;
        segment_state.hour1_state = 1;
        segment_state.hour2_state = 0;
        break;

      case 3:
        segment_state.min1_state = 0;
        segment_state.min2_state = 0;
        segment_state.hour1_state = 0;
        segment_state.hour2_state = 1;
        break;

      default:
        break;
    }
  }

  segContorl.clear_segments();

  digitalWrite(digit5, segment_state.seconds_state);  /// cursor

  digitalWrite(digit1, segment_state.hour2_state);
  digitalWrite(digit2, segment_state.hour1_state);
  digitalWrite(digit4, segment_state.min1_state);
  digitalWrite(digit3, segment_state.min2_state);

  segContorl.switch_seg_States();

}///<<

void setup() {

#if DEBUG
  Serial.begin(9600);
#endif

  Wire.begin();

  initiate_time.initial_time_set();

#if DEBUG
  RTClib RTC;
  DateTime now = RTC.now();
  Serial.println(now.hour() - 12, DEC); /// 12 hour system...
  Serial.println(now.minute(), DEC);
  delay(2000);
  Serial.println();
#endif

  TCCR1A = 0x00; //normal mode
  TIMSK1 = (1 << TOIE1); //enable timer 1 OVERFLOW interrupt
  TCCR1B = (1 << CS12) | (1 << CS10); //set timer prescaler 1024 Prescalar selected
  TCNT1 = 65520;
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);
  pinMode(segDP, OUTPUT);

  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);
  pinMode(digit3, OUTPUT);
  pinMode(digit4, OUTPUT);
  pinMode(digit5, OUTPUT);

  pinMode(time_decr, INPUT);
  pinMode(time_incr, INPUT);
  pinMode(time_switch, INPUT);
  pinMode(time_set, INPUT);

  digitalWrite(segDP, HIGH); /// cursor control//
}

void loop() {
#if DEBUG
  Serial.println(time_now.time_min_value1);
  Serial.println(time_now.time_min_value2);
  Serial.println(time_now.time_hr_value1);
  Serial.println(time_now.time_hr_value2);
  Serial.println();
#endif

  buttonOps.check_State();

}///end of loop
