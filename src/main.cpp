#include "Arduino.h"

#include <SimpleOta.h>
#include <Interval.h>
#include <OvApi.h>
#include <SimpleWifi.h>
#include <TimeParser.h>
#include <ESP8266WiFi.h>

#include <Schedules.h>
#include <TimeService.hpp>

#define SSID "H369A38F343"
#define PWD "D4FF27CDFD7E"
#define LED D0


TimeService timeClient;
OvApi ovApi;
SchedulesService scheduleUpdater = SchedulesService(ovApi, timeClient);
DisplayService display =  DisplayService(scheduleUpdater)

SimpleWifi wifi;

Schedules schedules;

OtaService ota;


void setup(void)
{
  Serial.begin(115200);

  display.begin();

  wifi.begin(SSID, PWD);
  timeClient.begin();
  ota.begin();
  scheduleUpdater.begin();
  displayUpdater.begin();
  Serial.println("Setup completed");
}

void loop(void)
{
  timeClient.loop();
  scheduleUpdater.loop();
  displayUpdater.loop();
  ota.loop();
}
