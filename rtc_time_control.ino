#include "rtc_time_control.h"

void time_h::initial_time_set(time_compute *time_now)
{
  if ( ! rtc.begin()) {
    Serial.println("Couldn't find RTC");
  }

  DateTime now = rtc.now();

  /*
    lcd.print(now.day(), DEC);
    lcd.print('/');
    lcd.print(now.month(), DEC);
    lcd.print('/');
    lcd.print(now.year(), DEC);
  */


  if (now.hour() > 12)
  {

    if ((now.hour() - 12) < 10) {
    ///  lcd.print('0');
    }

   /// lcd.print(now.hour() - 12, DEC);

  }
  else {
   /// lcd.print(now.hour(), DEC);
  }
}
