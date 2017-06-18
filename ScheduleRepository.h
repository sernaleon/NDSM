#ifndef SCHEDULE_REPOSITORY_H
#define SCHEDULE_REPOSITORY_H

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

#endif
