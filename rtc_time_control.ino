#include "rtc_time_control.h"

DS3231 Clock;
RTClib RTC;

void time_h::count_timer() {
  if (time_now->time_min_value1 > 9) {
    time_now->time_min_value1 = 0;
    ++time_now->time_min_value2;

    if (time_now->time_min_value2 > 5) {
      time_now->time_min_value2 = 0;
      ++time_now->time_hr_value1;

      if (time_now->time_hr_value2 == 1 && time_now->time_hr_value1 > 2) {
        time_now->time_hr_value1 = 0;
        time_now->time_hr_value2 = 0;
      }

      else if (time_now->time_hr_value1 > 9) {
        time_now->time_hr_value1 = 0;
        ++time_now->time_hr_value2;
      }///

    }///

  }////
}

void time_h::initial_time_set() {
  Clock.setClockMode(false);
  DateTime now = RTC.now();

  this->_Hour = (short)now.hour() - 12; /// 12 hour system...
  this->_Minute = (short)now.minute();

  time_now->temp_min = this->_Minute;
  time_now->temp_hr = this->_Hour;

  this->filter_hour();
  this->filter_min();
}

void time_h::setTime() {
  Clock.setHour(_Hour + 12);
  Clock.setMinute(_Minute);
}

void time_h::filter_hour() {

  if (this->_Hour < 10) {
    time_now->time_hr_value1 = this->_Hour;
    time_now->time_hr_value2 = 0;
  }

  else {
    switch (this->_Hour) {
      case 10:
        time_now->time_hr_value1 = 0;
        time_now->time_hr_value2 = 1;
        break;

      case 11:
        time_now->time_hr_value1 = 1;
        time_now->time_hr_value2 = 1;
        break;

      case 12:
        time_now->time_hr_value1 = 2;
        time_now->time_hr_value2 = 1;
        break;

      default:
        break;
    }

  }///else

}

void time_h::filter_min() {

  if (this->_Minute < 10) {
    time_now->time_min_value1 = this->_Minute;
    time_now->time_min_value2 = 0;
  }

  else if (this->_Minute == 10) {
    time_now->time_min_value1 = 0;
    time_now->time_min_value2 = 1;
  }

  else {
    short temp = this->_Minute,
          sub = 10;
    while (1) {
      temp -= 10;
      if (temp < 10) break;
      sub += 10;
    }///

    time_now->time_min_value1 = temp;
    time_now->time_min_value2 = (sub * 0.1);
  }///

}///filter
