#include "rtc_time_control.h"

RTC_DS1307 rtc;

void time_h::initial_time_set(time_compute *time_now)
{
  if ( ! rtc.begin()) {
    Serial.println("Couldn't find RTC");
  }

  DateTime now = rtc.now();

  this->_hr = (int)now.hour() - 12; /// 12 hour system...
  this->_min = (int)now.minute();

}

void time_h::count_timer(time_compute *time_now)
{

  if (time_now->time_seconds_value1 > 9)
  {
    time_now->time_seconds_value1 = 0;
    ++time_now->time_seconds_value2;

    if (time_now->time_seconds_value2 > 6)
    {
      time_now->time_seconds_value2 = 0;
      ++time_now->time_min_value1;

      if (time_now->time_min_value1 > 9)
      {
        time_now->time_min_value1 = 0;
        ++time_now->time_min_value2;
      }///

    }///

  }////

}
