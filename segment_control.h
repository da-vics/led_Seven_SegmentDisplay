#pragma once
#include "rtc_time_control.h"

///.......................................
//>anode 7 segment display.....
#define segA 0  //Display pin A
#define segB 1  //Display pin b
#define segC 2  //Display pin c
#define segD 4  //Display pin d
#define segE 7  //Display pin e
#define segF 8  //Display pin f
#define segG 12 //Display pin g
#define segDP 3 // Display pin dot

// common cathode
#define digit1 11 //Digit1
#define digit2 10 //Digit2
#define digit3 9  //Digit3
#define digit4 6  //Digit4
#define digit5 5  //Secs

struct segment_states
{
  volatile byte seconds_state{0}, /// for second indicator digital state
           hour1_state{0},
           hour2_state{0},
           min1_state{1},
           min2_state{0},
           switch_seg{0},
           switch_value{3},
           switch_lowest{0};
};

class segmentControl{

  private:
    void lightNumber(const int &) const;

  public:
    void switch_seg_States(const time_compute *, const segment_states &) const;
};
