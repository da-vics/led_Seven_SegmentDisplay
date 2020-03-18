#include <avr/io.h>
#include <avr/interrupt.h>
#include "segment_control.h"
#include "rtc_time_control.h"

///#define DEBUG

// common cathode
byte digit1 = 11;  //Digit1
byte digit2 = 10;  //Digit2
byte digit3 = 9;   //Digit3
byte digit4 = 6;   //Digit4
byte digit5 = 5;   //Secs


volatile int seconds_counter = 0, /// seconds  indicator
             time_min_count = 0;

volatile byte seconds_state = 0,  /// for second indicator digital state
              seconds1_state = 1,
              seconds2_state = 0,
              min1_state = 0,
              min2_state = 0,
              switch_seg = 0;

volatile short time_seconds_value1 = 0,
               time_seconds_value2 = 0,
               time_min_value1 = 0,
               time_min_value2 = 0;


ISR (TIMER1_OVF_vect)
{
  ///TCNT1 = 49910;
  TCNT1 = 65520;       /// 1 milli_seconds overflow

  ++seconds_counter;
  ++time_min_count;

  if (seconds_counter >= 1000)
  {
    seconds_state = !seconds_state;
    ++time_seconds_value1;
    seconds_counter = 0;
  } ////

  ++switch_seg;
  if (switch_seg > 3)  switch_seg = 0;

  switch (switch_seg)
  {
    case 0:
      seconds1_state = 1;
      min1_state = 0;
      seconds2_state = 0;
      min2_state = 0;
      break;

    case 1:
      seconds2_state = 1;
      min1_state = 0;
      seconds1_state = 0;
      min2_state = 0;
      break;

    case 2:
      min1_state = 1;
      seconds2_state = 0;
      seconds1_state = 0;
      min2_state = 0;
      break;

    case 3:
      min2_state = 1;
      seconds2_state = 0;
      min1_state = 0;
      seconds1_state = 0;
      break;

  }

  digitalWrite(digit5, seconds_state);  /// cursor

  digitalWrite(digit1, min2_state);
  digitalWrite(digit2, min1_state);
  digitalWrite(digit4, seconds1_state);
  digitalWrite(digit3, seconds2_state);
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
}

void loop()
{

#ifdef DEBUG
  Serial.print("secs: ");
  Serial.println(seconds_state);
  Serial.print("seconds1: ");
  Serial.println(seconds1_state);
  Serial.print("seconds2: ");
  Serial.println(seconds2_state); m
#endif

  if (time_seconds_value1 > 9)
  {
    time_seconds_value1 = 0;
    ++time_seconds_value2;

    if (time_seconds_value2 > 6)
    {
      time_seconds_value2 = 0;
      ++time_min_value1;

      if (time_min_value1 > 9)
      {
        time_min_value1 = 0;
        ++time_min_value2;
      }///

    }///

  }////

  if (seconds1_state)
  {
    lightNumber(time_seconds_value1);
  }

  else if (seconds2_state)
  {
    lightNumber(time_seconds_value2);
  }

  else if (min1_state)
  {
    lightNumber(time_min_value1);
  }

  else if (min2_state)
  {
    lightNumber(time_min_value2);
  }

}///end of loop
