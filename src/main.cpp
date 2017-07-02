#include "Arduino.h"

#include <SimpleOta.h>
#include <Interval.h>
#include <OvApi.h>
#include <SimpleWifi.h>
#include <ESP8266WebServer.h>
#include <JsonListener.h>
#include <JsonTransformer.h>
#include <TimeParser.h>
#include <DisplayController.h>
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define SSID "H369A38F343"
#define PWD "D4FF27CDFD7E"
#define LED D0
#define SYNC_TIME 1200000

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "nl.pool.ntp.org", 7200, 60000);
SimpleWifi internet;
OvApi ovApi;
Interval scheduleUpdater;
Interval displayUpdater;
ESP8266WebServer server(80);
Schedules schedules;
DisplayController display;
SimpleOta ota;

bool isLedOn;
void switchLed()
{
  digitalWrite(LED, isLedOn);
  isLedOn = !isLedOn;
}

String schedulesToString()
{
  return "C0: " + TimeParser::toString(schedules.central[0]) + "\n" +
         "C1: " + TimeParser::toString(schedules.central[1]) + "\n" +
         "W0: " + TimeParser::toString(schedules.west[0]) + "\n" +
         "W1: " + TimeParser::toString(schedules.west[1]) + "\n";
}

void updateSchedules()
{
  Serial.println("Updating schedules!");
  String json = ovApi.getDeparturesJson();
  if (json.length() > 0)
  {
    JsonTransformer listener = JsonTransformer();
    schedules = listener.parseJson(json);

    Serial.println(schedulesToString());
  }
  else
  {
    Serial.println("Error!");
  }
}

void handleRoot()
{
  switchLed();
  server.send(200, "text/json", schedulesToString());
}

void setupServer()
{
  server.on("/", handleRoot);
  server.begin();
  Serial.println("Server started");
}

void updateDisplay()
{
  Serial.println(timeClient.getFormattedTime());
  display.displaySchedules(schedules);
}

void setup(void)
{
  Serial.begin(115200);
  pinMode(LED, OUTPUT);

  display.setup();
  internet.begin(SSID, PWD);

  timeClient.begin();
  ota.setup();

  scheduleUpdater.begin(SYNC_TIME, updateSchedules);
  displayUpdater.begin(1000, updateDisplay);

  setupServer();
  updateSchedules();
  updateDisplay();
  Serial.println("Setup completed");
}

void loop(void)
{
  server.handleClient();
  timeClient.update();
  scheduleUpdater.loop();
  displayUpdater.loop();
  ota.loop();
}
