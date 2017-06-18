#ifndef INTERVAL_H
#define INTERVAL_H

#include <Arduino.h>

#include <functional>

using namespace std;

class Interval
{
  public:
    void begin(unsigned long interval, function<void(void)> handler);
    void loop();

    void enable();
    void disable();
  private:
    bool isEnabled;
    unsigned long previous;
    unsigned long interval;
    function<void(void)> handler;
};

#endif