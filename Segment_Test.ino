#include <avr/io.h>
#include <avr/interrupt.h>
#include "segment_control.h"

///#define DEBUG

time_compute time_now;
time_h initiate_time;
segmentControl segContorl;

volatile int seconds_counter = 0, /// seconds  indicator
             seconds_counter2 = 0;

ISR (TIMER1_OVF_vect)
{
  ///TCNT1 = 49910;
  TCNT1 = 65520;       /// 1 milli_seconds overflow

  ++seconds_counter;
  ++seconds_counter2;

  if (seconds_counter >= 1000)
  {
    segment_state.seconds_state = !segment_state.seconds_state;
    ++time_now.time_seconds_value1;
    seconds_counter = 0;
    initiate_time.count_timer(&time_now);
  } ////

  seconds_counter2 = 0;
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

}///<<

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

  ///initiate_time.initial_time_set(&time_now);
}

void loop()
{
  segContorl.switch_seg_States(&time_now);

}///end of loop
