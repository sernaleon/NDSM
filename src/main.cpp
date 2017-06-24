#include "Arduino.h"

#include <ArduinoOTA.h>
#include <Interval.h>
#include <ScheduleRepository.h>
#include <SimpleWifi.h>
#include <ESP8266WebServer.h>
#include <JsonStreamingParser.h>
#include <JsonListener.h>
#include <JsonTransformer.h>

#define SSID "H369A38F343"
#define PWD "D4FF27CDFD7E"
#define LED D0
#define SYNC_TIME 1000

SimpleWifi internet = SimpleWifi();
ScheduleRepository scheduleRepo = ScheduleRepository();
Interval scheduleUpdater = Interval();
ESP8266WebServer server(80);

JsonStreamingParser parser;
ExampleListener listener;

bool isLedOn = false;

void handleRoot()
{
  Serial.println("LED switch");
  digitalWrite(LED, isLedOn);
  isLedOn = !isLedOn;
  Serial.println("ROT");
  String json = scheduleRepo.get();

  server.send(200, "text/json", json);
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

void setupJson() {
  Serial.println(String(ESP.getFreeHeap()));
  parser.setListener(&listener);
  // put your setup code here, to run once:
  char json[] = "{\"a\":3, \"b\":{\"c\":\"d\"}}";
  for (int i = 0; i < sizeof(json); i++) {
    parser.parse(json[i]); 
  }
  Serial.println(String(ESP.getFreeHeap()));
}

void setup(void)
{
  Serial.begin(115200);
  Serial.println("SIP");

  pinMode(LED, OUTPUT);

  internet.begin(SSID, PWD);

  setupOTA();
  setupJson();
  scheduleUpdater.begin(SYNC_TIME, [&]() { scheduleRepo.set(); });

  setupServer();
}

void loop(void)
{
  server.handleClient();
  scheduleUpdater.loop();
  ArduinoOTA.handle();
}
