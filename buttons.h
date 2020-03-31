#pragma once

#include "segment_control.h"

#define time_decr A3
#define time_incr A2
#define time_switch A1
#define time_set A0

class ButtonAction{

  private:
    bool _time_set{false};
    void Set_time(time_h *, time_compute *, segment_states &);

  public:
    void check_State(time_h *, time_compute *,segment_states &);

    bool updateTimeStats()
    {
      return this->_time_set;
    }

    void setTimeStats(bool time_set)
    {
      this->_time_set = time_set;
    }
};

/*
void milli(uint16_t x)
{
  unsigned long tim = 0;

  while (1)
  {
    if ((millis() - tim) >= x) break;
  }
}*/
