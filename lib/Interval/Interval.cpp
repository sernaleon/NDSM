#include "Interval.h"

void Interval::begin(unsigned long interval, function<void(void)> handler)
{
    this->isEnabled = true;
    this->previous = 0;
    this->interval = interval;
    this->handler = handler;
}

void Interval::loop()
{
    unsigned long current = millis();
    if (isEnabled && (current - previous >= interval))
    {
        previous = current;
        handler();
    }
}

void Interval::enable()
{
    isEnabled = true;
}

void Interval::disable()
{
    isEnabled = false;
}