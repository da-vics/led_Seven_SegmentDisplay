#pragma once

#include <Wire.h>
#include "DS3231.h"
#include <DS3231.h>

struct time_compute {
  volatile byte time_min_value1{0},
           time_min_value2{0},
           time_hr_value1{0},
           time_hr_value2{0};

  volatile short temp_min{0},
           temp_hr{0};
};

class time_h {

  private:
    short _Hour;
    short _Minute;
    time_compute *time_now{nullptr};

  public:

    time_h(time_compute *timee)
    {
      this->time_now = timee;
    }

    void initial_time_set();
    void count_timer();
    void setTime();
    void filter_min();
    void filter_hour();

    void SetHour(const short Hour) {
      this->_Hour = Hour;
    }

    void SetMin(const short Minute) {
      this->_Minute = Minute;
    }
};
