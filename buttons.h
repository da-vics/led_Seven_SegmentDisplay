#pragma once

#include "segment_control.h"

#define time_decr A3
#define time_incr A2
#define time_switch A1
#define time_set A0

class ButtonAction {

  private:
    bool _time_set{false};
    void Set_time();
    time_h *set_time{nullptr};
    time_compute *time_now{nullptr};
    segment_states *segment_state{nullptr};

  public:
    void check_State();

    ButtonAction(time_h *sett, time_compute *t_now, segment_states *seg_s)
    {
      this->set_time = sett;
      this->time_now = t_now;
      this->segment_state = seg_s;
    }

    bool updateTimeStats() {
      return this->_time_set;
    }

    void setTimeStats(bool time_set) {
      this->_time_set = time_set;
    }
};

/*
  void milli(uint16_t x)
  {
  unsigned long tim = millis();

  while (1)
  {
    if ((millis() - tim) >= x) break;
  }
  }*/
