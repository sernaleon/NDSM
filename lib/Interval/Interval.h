#ifndef INTERVAL_H
#define INTERVAL_H

#include <Arduino.h>
#include <functional>
using namespace std;

class Interval
{
public:
  inline void begin(unsigned long interval, function<void(void)> handler)
  {
    this->isEnabled = true;
    this->previous = 0;
    this->interval = interval;
    this->handler = handler;
  }
  void enable()
  {
    isEnabled = true;
  }
  void disable()
  {
    isEnabled = false;
  }
  void loop()
  {
    unsigned long current = millis();
    if (isEnabled && (current - previous >= interval))
    {
      previous = current;
      handler();
    }
  }

private:
  bool isEnabled;
  unsigned long previous;
  unsigned long interval;
  function<void(void)> handler;
};

#endif