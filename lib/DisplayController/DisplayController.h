#pragma once

#include <LedControl.h>
#include <Schedules.h>
#include <ILoopService.h>
#include <Schedules.h>
#include <TimeService.hpp>

class DisplayService : public ILoopService
{
  public:
    DisplayService(ScheduleService &s, TimeService &time) : scheduleService(s),
                                                            timeService(time)
    {
    }

    void updateDisplay()
    {
        unsigned long currentTime = timeService.getCurrentTime();

        int c1 = schedules.central[0] - currentTime;
        int c2 = schedules.central[1] - currentTime;
        int w1 = schedules.west[0] - currentTime;
        int w2 = schedules.west[1] - currentTime;

        displaySeconds(c1, c2, w1, w2);

        if (c1 <= 0 || c2 <= 0 || w1 <= 0 || w2 <= 0)
        {
            Serial.println("Countdown to zero. Update");
            scheduleService.execute();
        }
    }
    void begin()
    {
        lc.shutdown(0, false);  // Enable display
        lc.setIntensity(0, 15); // Set brightness level (0 is min, 15 is max)
        lc.clearDisplay(0);     // Clear display register

        lc2.shutdown(0, false);  // Enable display
        lc2.setIntensity(0, 15); // Set brightness level (0 is min, 15 is max)
        lc2.clearDisplay(0);     // Clear display register

        interval.begin(1000, updateDisplay);
    }
    bool displaySeconds(int c1, int c2, int w1, int w2)
    {
        display(lc2, 4, c1);
        display(lc, 4, c2);
        display(lc2, 0, w1);
        display(lc, 0, w2);
    }
    void loop()
    {
        interval.loop();
    }

  private:
    Interval interval;
    LedControl lc2 = LedControl(D8, D6, D7, 8); // D8 - DIN, D7 - Clk, D6 - CS, 8 displays
    LedControl lc = LedControl(D4, D2, D3, 8);
    SchedueService &scheduleService;
    TimeService &timeService;

    void display(LedControl lc, int addr, int seconds)
    {
        int s = seconds % 60;
        int m = seconds / 60;

        if (m > 99)
        {
            m = 99;
            s = 99;
        }

        lc.setDigit(0, 3 + addr, m / 10, false);
        lc.setDigit(0, 2 + addr, m % 10, false);
        lc.setDigit(0, 1 + addr, s / 10, false);
        lc.setDigit(0, 0 + addr, s % 10, false);
    }
};
