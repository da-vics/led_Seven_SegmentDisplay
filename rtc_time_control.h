#pragma once

#include "RTClib.h"
RTC_DS1307 rtc;

struct time_compute
{

  byte time_seconds_value1,
       time_seconds_value2,
       time_min_value1,
       time_min_value2;

  time_compute()
  {
    time_seconds_value1 = 0;
    time_seconds_value2 = 0;
    time_min_value1 = 0;
    time_min_value2 = 0;
  }

};

struct time_h
{
    void initial_time_set(time_compute *);s
};
