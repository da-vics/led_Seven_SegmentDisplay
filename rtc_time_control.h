#pragma once

#include <Wire.h>
#include "DS3231.h"
#include <DS3231.h>

struct time_compute{
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

  public:
    void initial_time_set(time_compute *);
    void count_timer(time_compute &);
    void setTime();
    void filter_min(time_compute *);
    void filter_hour(time_compute *);

    void SetHour(const short Hour){
      this->_Hour = Hour;
    }

    void SetMin(const short Minute){
      this->_Minute = Minute;
    }
};
