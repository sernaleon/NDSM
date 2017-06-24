#pragma once

#include <ESP8266HTTPClient.h>

class ScheduleRepository
{
public:
  ScheduleRepository();

  String get();
  void set();
private:
  String lastValue;
  long numRefresh;
};
