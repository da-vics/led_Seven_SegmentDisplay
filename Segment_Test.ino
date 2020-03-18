#include <avr/io.h>
#include <avr/interrupt.h>
#include "segment_control.h"
#include "rtc_time_control.h"

///#define DEBUG

time_compute time_now;
time_h initiate_time;

volatile int seconds_counter = 0, /// seconds  indicator
             time_min_count = 0;


ISR (TIMER1_OVF_vect)
{
  ///TCNT1 = 49910;
  TCNT1 = 65520;       /// 1 milli_seconds overflow

  ++seconds_counter;
  ++time_min_count;

  if (seconds_counter >= 1000)
  {
    segment_state.seconds_state = !segment_state.seconds_state;
    ++time_now.time_seconds_value1;
    seconds_counter = 0;
  } ////

  ++segment_state.switch_seg;
  if (segment_state.switch_seg > 3)  segment_state.switch_seg = 0;

  switch (segment_state.switch_seg)
  {
    case 0:
      segment_state.seconds1_state = 1;
      segment_state.min1_state = 0;
      segment_state.seconds2_state = 0;
      segment_state.min2_state = 0;
      break;

    case 1:
      segment_state.seconds2_state = 1;
      segment_state.min1_state = 0;
      segment_state.seconds1_state = 0;
      segment_state.min2_state = 0;
      break;

    case 2:
      segment_state.min1_state = 1;
      segment_state.seconds2_state = 0;
      segment_state.seconds1_state = 0;
      segment_state.min2_state = 0;
      break;

    case 3:
      segment_state.min2_state = 1;
      segment_state.seconds2_state = 0;
      segment_state.min1_state = 0;
      segment_state.seconds1_state = 0;
      break;

  }

  digitalWrite(digit5, segment_state.seconds_state);  /// cursor

  digitalWrite(digit1, segment_state.min2_state);
  digitalWrite(digit2, segment_state.min1_state);
  digitalWrite(digit4, segment_state.seconds1_state);
  digitalWrite(digit3, segment_state.seconds2_state);
}

void setup()
{
  TCCR1A = 0x00; //normal mode
  TIMSK1 = (1 << TOIE1); //enable timer 1 OVERFLOW interrupt
  TCCR1B = (1 << CS12) | (1 << CS10); //set timer prescaler 1024 Prescalar selected
  TCNT1 = 65520;

  Serial.begin(9600);

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

  digitalWrite(segDP, HIGH); /// cursor control//

  initiate_time.initial_time_set(&time_now);
}

void loop()
{

#ifdef DEBUG
  Serial.print("secs: ");
  Serial.println(segment_state.seconds_state);
  Serial.print("seconds1: ");
  Serial.println(segment_state.seconds1_state);
  Serial.print("seconds2: ");
  Serial.println(segment_state.seconds2_state); m
#endif

  if (time_now.time_seconds_value1 > 9)
  {
    time_now.time_seconds_value1 = 0;
    ++time_now.time_seconds_value2;

    if (time_now.time_seconds_value2 > 6)
    {
      time_now.time_seconds_value2 = 0;
      ++time_now.time_min_value1;

      if (time_now.time_min_value1 > 9)
      {
        time_now.time_min_value1 = 0;
        ++time_now.time_min_value2;
      }///

    }///

  }////

  if (segment_state.seconds1_state)
  {
    lightNumber(time_now.time_seconds_value1);
  }

  else if (segment_state.seconds2_state)
  {
    lightNumber(time_now.time_seconds_value2);
  }

  else if (segment_state.min1_state)
  {
    lightNumber(time_now.time_min_value1);
  }

  else if (segment_state.min2_state)
  {
    lightNumber(time_now.time_min_value2);
  }

}///end of loop
