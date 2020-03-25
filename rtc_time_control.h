#pragma once

#include "RTClib.h"

struct time_compute
{
  byte time_seconds_value1{0},
       time_seconds_value2{0},
       time_min_value1{0},
       time_min_value2{0};
};

class time_h
{
  private:
    short _hr;
    short _min;

  public:
    void initial_time_set(time_compute *);
    void count_timer(time_compute *);
};
