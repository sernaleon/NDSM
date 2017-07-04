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
    inline bool displaySeconds(int c1, int c2, int w1, int w2)
    {
        display(lc2, 4, c1);
        display(lc, 4, c2);
        display(lc2, 0, w1);
        display(lc, 0, w2);
    }

  private:
    // D8 to DIN, D7 to Clk, D6 to CS, no.of devices is 8
    LedControl lc2 = LedControl(D8, D6, D7, 8);
    LedControl lc = LedControl(D4, D2, D3, 8);

    void display(LedControl lc, int addr, int seconds)
    {
        int s = seconds % 60;
        int m = seconds / 60;

        if (m > 99) {
            m = 99;
            s = 99;
        }
        
        lc.setDigit(0, 3 + addr, m / 10, false);
        lc.setDigit(0, 2 + addr, m % 10, false);
        lc.setDigit(0, 1 + addr, s / 10, false);
        lc.setDigit(0, 0 + addr, s % 10, false);
    }
};
