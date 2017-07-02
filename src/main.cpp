#include "Arduino.h"

#include <ArduinoOTA.h>
#include <Interval.h>
#include <OvApi.h>
#include <SimpleWifi.h>
#include <ESP8266WebServer.h>
#include <JsonListener.h>
#include <JsonTransformer.h>
#include <TimeParser.h>
#include <LedControl.h>

#define SSID "H369A38F343"
#define PWD "D4FF27CDFD7E"
#define LED D0
#define SYNC_TIME 1200000

SimpleWifi internet;
OvApi ovApi;
Interval scheduleUpdater;
ESP8266WebServer server(80);
Schedules schedules;

// EasyESP or NodeMCU Pin 
// D8 to DIN, 
// D7 to Clk, 
// D6 to CS, 
// no.of devices is 8
LedControl lc2 = LedControl(D8, D6, D7, 8);
LedControl lc = LedControl(D4, D2, D3, 8);

void setUpDisplay()
{
  // Initialize the MAX7219 device
  lc.shutdown(0, false);  // Enable display
  lc.setIntensity(0, 15); // Set brightness level (0 is min, 15 is max)
  lc.clearDisplay(0);     // Clear display register
//  displayUpdater.begin(1000, loopDisplay);
  lc2.shutdown(0, false);  // Enable display
  lc2.setIntensity(0, 15); // Set brightness level (0 is min, 15 is max)
  lc2.clearDisplay(0);     // Clear display register

  
  lc.setDigit(0, 0, 0, false);
  lc.setDigit(0, 1, 3, false);
  lc.setDigit(0, 2, 0, false);
  lc.setDigit(0, 3, 5, false);

  lc.setDigit(0, 4, 6, false);
  lc.setDigit(0, 5, 5, false);
  lc.setDigit(0, 6, 4, false);
  lc.setDigit(0, 7, 5, false);

  for (int i = 0; i < 8; i++)
  {
    lc2.setDigit(0, i, i, false);
  }
}

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
  
  setUpDisplay();
}

void loop(void)
{
  
  server.handleClient();
  scheduleUpdater.loop();
  //displayUpdater.loop();
  ArduinoOTA.handle();
  
  loopDisplay();
}
