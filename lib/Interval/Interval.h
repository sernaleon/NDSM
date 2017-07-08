#pragma once

#include <Arduino.h>
#include <ILoopService.h>

#include <functional>
using namespace std;

class Interval
{
public:
  inline void begin(unsigned long interval, function<void(void)> handler)
  {
    this->isEnabled = true;
    this->interval = interval;
    this->handler = handler;
    execute();
  }
  void execute()
  {
    previous = millis();
    handler();
  }
  void loop()
  {
    if (isEnabled && (millis() - previous >= interval))
    {
      execute();
    }
  }
  void enable()
  {
    isEnabled = true;
  }
  void disable()
  {
    isEnabled = false;
  }

private:
  bool isEnabled;
  unsigned long previous;
  unsigned long interval;
  function<void(void)> handler;
};