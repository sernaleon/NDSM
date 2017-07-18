#pragma once

#include <TM1637Display.h>
#include <Schedules.h>

class DisplayController
{
  public:
    inline void setup()
    {  
        d1.setBrightness(0x0f);
        d2.setBrightness(0x0f);
        d3.setBrightness(0x0f);
        d4.setBrightness(0x0f);
    }

    inline bool displaySeconds(int c1, int c2, int w1, int w2)
    {
        Serial.println("DISPLAY");
        display(d1, c1);
        display(d2, c2);
        display(d3, w1);
        display(d4, w2);
    }

  private:
    TM1637Display d1  = TM1637Display(D1, D0);
    TM1637Display d2  = TM1637Display(D3, D2);
    TM1637Display d3  = TM1637Display(D4, D5);
    TM1637Display d4  = TM1637Display(D7, D8);

    void display(TM1637Display display, int seconds)
    {
        int s = seconds % 60;
        int m = seconds / 60;

        if (m > 99) {
            m = 99;
            s = 99;
        }

        Serial.println((m * 100 + s));

	    display.showNumberDecEx(m * 100 + s, (0x80 >> 1), true);
    }
};
