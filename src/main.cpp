#include "Arduino.h"

#include <ArduinoOTA.h>
#include <Interval.h>
#include <OvApi.h>
#include <SimpleWifi.h>
#include <ESP8266WebServer.h>
#include <JsonListener.h>
#include <JsonTransformer.h>
#include <TimeParser.h>

#define SSID "H369A38F343"
#define PWD "D4FF27CDFD7E"
#define LED D0
#define SYNC_TIME 120000

SimpleWifi internet;
OvApi ovApi;
Interval scheduleUpdater;
ESP8266WebServer server(80);
Schedules schedules;

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

void setupOTA()
{
  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR)
      Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR)
      Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR)
      Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR)
      Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR)
      Serial.println("End Failed");
  });
  ArduinoOTA.begin();
}

void setupServer()
{
  server.on("/", handleRoot);
  server.begin();
  Serial.println("Server started");
}

void setup(void)
{
  Serial.begin(115200);
  Serial.println("SIP");
  pinMode(LED, OUTPUT);
  internet.begin(SSID, PWD);
  setupOTA();

  scheduleUpdater.begin(SYNC_TIME, updateSchedules);

  setupServer();
}

void loop(void)
{
  server.handleClient();
  scheduleUpdater.loop();
  ArduinoOTA.handle();
}
