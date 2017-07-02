#pragma once

#include <LedControl.h>
#include <Schedules.h>

class DisplayController
{
  public:
    inline void setup()
    {
        lc.shutdown(0, false);  // Enable display
        lc.setIntensity(0, 15); // Set brightness level (0 is min, 15 is max)
        lc.clearDisplay(0);     // Clear display register

        lc2.shutdown(0, false);  // Enable display
        lc2.setIntensity(0, 15); // Set brightness level (0 is min, 15 is max)
        lc2.clearDisplay(0);     // Clear display register
    }

    inline void displaySchedules(Schedules schedules)
    {
        lc.clearDisplay(0);
        lc2.clearDisplay(0);
        //First C
        lc2.setDigit(0, 7, schedules.central[0].tm_min / 10, false);
        lc2.setDigit(0, 6, schedules.central[0].tm_min % 10, false);
        lc2.setDigit(0, 5, schedules.central[0].tm_sec / 10, false);
        lc2.setDigit(0, 4, schedules.central[0].tm_sec % 10, false);
        //Second C
        lc.setDigit(0, 7, schedules.central[1].tm_min / 10, false);
        lc.setDigit(0, 6, schedules.central[1].tm_min % 10, false);
        lc.setDigit(0, 5, schedules.central[1].tm_sec / 10, false);
        lc.setDigit(0, 4, schedules.central[1].tm_sec % 10, false);
        //First W
        lc.setDigit(0, 3, schedules.west[0].tm_min / 10, false);
        lc.setDigit(0, 2, schedules.west[0].tm_min % 10, false);
        lc.setDigit(0, 1, schedules.west[0].tm_sec / 10, false);
        lc.setDigit(0, 0, schedules.west[0].tm_sec % 10, false);
        //Second W
        lc2.setDigit(0, 3, schedules.west[1].tm_min / 10, false);
        lc2.setDigit(0, 2, schedules.west[1].tm_min % 10, false);
        lc2.setDigit(0, 1, schedules.west[1].tm_sec / 10, false);
        lc2.setDigit(0, 0, schedules.west[1].tm_sec % 10, false);
    }

  private:
    // D8 to DIN, D7 to Clk, D6 to CS, no.of devices is 8
    LedControl lc2 = LedControl(D8, D6, D7, 8);
    LedControl lc = LedControl(D4, D2, D3, 8);
};
