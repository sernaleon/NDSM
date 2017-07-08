#pragma once

#include <Interval.h>
#include <ILoopService.h>
#include <JsonTransformer.h>
#include <TimeService.hpp>

struct Schedules
{
  unsigned long central[2];
  unsigned long west[2];
};

class SchedulesService : public ILoopService
{
public:
  SchedulesService(OvApi &ov, TimeService &time) : ovApi(ov),
                                                   timeService(time)
  {
  }

  Schedules get()
  {
    return schedules;
  }

  void update()
  {
    Serial.println("Updating schedules!");
    String json = ovApi.getDeparturesJson();
    if (json.length() > 0)
    {
      JsonTransformer listener = JsonTransformer();
      schedules = listener.parseJson(json, timeService.getCurrentTime());

      Serial.println(
          "C0: " + String(schedules.central[0]) + "\n" +
          "C1: " + String(schedules.central[1]) + "\n" +
          "W0: " + String(schedules.west[0]) + "\n" +
          "W1: " + String(schedules.west[1]) + "\n");
    }
    else
    {
      Serial.println("Error!");
    }
  }
  void begin()
  {
    interval.begin(600000, [&] { update(); });
  }
  void loop()
  {
    interval.loop();
  }

private:
  OvApi &ovApi;
  TimeService &timeService;
  Schedules schedules;
  Interval interval;
};