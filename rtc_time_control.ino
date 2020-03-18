#include "rtc_time_control.h"

void time_h::initial_time_set(time_compute *time_now)
{
  if ( ! rtc.begin()) {
    Serial.println("Couldn't find RTC");
  }

  DateTime now = rtc.now();

  this->_hr = (int)now.hour() - 12; /// 12 hour system...
  this->_min = (int)now.minute();

}
