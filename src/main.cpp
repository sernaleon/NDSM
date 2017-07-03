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
#define SYNC_TIME 12000000000

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
TimeParser timeParser;

bool isLedOn;
void switchLed()
{
  digitalWrite(LED, isLedOn);
  isLedOn = !isLedOn;
}

String schedulesToString()
{
  return "C0: " + timeParser.toString(schedules.central[0]) + "\n" +
         "C1: " + timeParser.toString(schedules.central[1]) + "\n" +
         "W0: " + timeParser.toString(schedules.west[0]) + "\n" +
         "W1: " + timeParser.toString(schedules.west[1]) + "\n";
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

unsigned long getCurrentTime()
{                                    
  return timeClient.getEpochTime() +  2211667200UL; //2211665580UL + 1620;
}

void updateDisplay()
{
  Serial.println("-------");
  Serial.println(schedulesToString());
  Serial.print("CURRENT ");
  Serial.println(timeClient.getFormattedTime());
  Serial.print("CENTRAL ");
  Serial.println(timeParser.toString(schedules.central[0]));
  Serial.print("CURRENT ");
  Serial.println(getCurrentTime());
  Serial.print("CENTRAL ");
  Serial.println(timeParser.getLinuxTime(schedules.central[0]));

  int c1 = timeParser.getLinuxTime(schedules.central[0]) - getCurrentTime();
  int c2 = timeParser.getLinuxTime(schedules.central[1]) - getCurrentTime();
  int w1 = timeParser.getLinuxTime(schedules.west[0]) - getCurrentTime();
  int w2 = timeParser.getLinuxTime(schedules.west[1]) - getCurrentTime();
  Serial.println((int)c1);
  Serial.println(c2);
  Serial.println(w1);
  Serial.println(w2);

 // CENTRAL = CURRENT + X
 //3710779200 - 3705422190 - 1830 + X

  display.displaySeconds(c1,c2,w1,w2);
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
