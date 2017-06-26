#include "Arduino.h"

#include <ArduinoOTA.h>
#include <Interval.h>
#include <ScheduleRepository.h>
#include <SimpleWifi.h>
#include <ESP8266WebServer.h>
#include <JsonListener.h>
#include <JsonTransformer.h>

#define SSID "H369A38F343"
#define PWD "D4FF27CDFD7E"
#define LED D0
#define SYNC_TIME 10000

SimpleWifi internet;
ScheduleRepository scheduleRepo;
Interval scheduleUpdater;
ESP8266WebServer server(80);
bool isLedOn;

void switchLed()
{
  digitalWrite(LED, isLedOn);
  isLedOn = !isLedOn;
}

Schedules getSchedules()
{
  Serial.println("HEAP 2:" + String(ESP.getFreeHeap()));
  String json = scheduleRepo.get();
  JsonTransformer listener = JsonTransformer();
  Schedules result = listener.parseJson(json);
  Serial.println("HEAP 3:" + String(ESP.getFreeHeap()));
  return result;
}

String schedulesToString(Schedules schedules)
{
  String result = schedules.central[0] + "\n" +
                  schedules.central[1] + "\n" +
                  schedules.west[0] + "\n" +
                  schedules.west[1];
}

void handleRoot()
{
  switchLed();

  Serial.println("HEAP 1:" + String(ESP.getFreeHeap()));
  Schedules schedules = getSchedules();
  Serial.println("HEAP 4:" + String(ESP.getFreeHeap()));

  server.send(200, "text/json", schedulesToString(schedules));
}

void handleNotFound()
{
  Serial.println("LED switc!h");
  digitalWrite(LED, isLedOn);
  isLedOn = !isLedOn;
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
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

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

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
  scheduleUpdater.begin(SYNC_TIME, [&]() {
    scheduleRepo.set();
    getSchedules();
  });

  setupServer();
}

void loop(void)
{
  server.handleClient();
  scheduleUpdater.loop();
  ArduinoOTA.handle();
}
