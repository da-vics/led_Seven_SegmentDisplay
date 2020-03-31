#include "buttons.h"

void ButtonAction::check_State(time_h *set_time, time_compute * time_now, segment_states &segment_state) {

  if (digitalRead(time_set)) {
delay(800);
   this->setTimeStats(true);
   
    while (ButtonAction::updateTimeStats())
    {
     this->Set_time(set_time, time_now, segment_state);
      this->setTimeStats(false);
      segment_state.switch_value = 3;
      segment_state.switch_lowest = 0;
      break;
    }

  }///

} ///

void ButtonAction::Set_time(time_h *set_time, time_compute * time_now, segment_states &segment_state) {

    segment_state.hour2_state = 0;
    segment_state.hour1_state = 0;
    segment_state.min1_state = 0;
    segment_state.min2_state = 0;

      segment_state.switch_seg = 0;
      segment_state.switch_value = 1;
      segment_state.switch_lowest = 0;

      set_time->initial_time_set(time_now);

        volatile byte index = 1;

  bool done = false;
  while (!done) {

    #if DEBUG
    Serial.println("Inside!");
    Serial.println(segment_state.hour2_state);
    Serial.println(segment_state.hour1_state);
    Serial.println(segment_state.min1_state);
    Serial.println(segment_state.min2_state);
    #endif

    if (digitalRead(time_incr)) {
      delay(800);

      switch (index)
      {
        case 1:
          ((time_now->temp_min) < 59) ? ++time_now->temp_min : time_now->temp_min = 0;
          set_time->SetMin(time_now->temp_min);
          set_time->filter_min(time_now);
          break;

        case 2:
          ((time_now->temp_hr) < 12) ? ++time_now->temp_hr : time_now->temp_hr = 0;
          set_time->SetHour(time_now->temp_hr);
          set_time->filter_hour(time_now);
          break;

        default:
          break;
      }///

    #if DEBUG
    Serial.println("incrementing...");
    Serial.println(time_now->temp_min);
     Serial.println(time_now->temp_hr);
    #endif
    }

    else if (digitalRead(time_decr)) {
      delay(800);
      switch (index)
      {
        case 1:
          ((time_now->temp_min) > 0) ? --time_now->temp_min : time_now->temp_min = 59;
          set_time->SetMin(time_now->temp_min);
          set_time->filter_min(time_now);
          break;

        case 2:
          ((time_now->temp_hr) > 0) ? --time_now->temp_hr : time_now->temp_hr = 12;
          set_time->SetHour(time_now->temp_hr);
          set_time->filter_hour(time_now);
          break;

        default:
          break;
      }///
    #if DEBUG
    Serial.println("decrementing...");
    Serial.println(time_now->temp_min);
     Serial.println(time_now->temp_hr);
    #endif
    }

    else if (digitalRead(time_set)) {
      delay(800);
      done = true;
      set_time->setTime();
      break;
    }

    else if (digitalRead(time_switch)) {
      delay(800);
      (index < 2) ? ++index : index = 1;

      switch (index)
      {
        case 1:
          segment_state.switch_seg = 0;
          segment_state.switch_value = 1;
          segment_state.switch_lowest = 0;
          break;

        case 2:
          segment_state.switch_seg = 2;
          segment_state.switch_value = 3;
          segment_state.switch_lowest = 2;
          break;

        default:
          break;
      }

    #if DEBUG
    Serial.println("set active:");
    Serial.println(index);
    #endif
    }

  }/// done

}
