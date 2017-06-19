#include "Arduino.h"

#include <ArduinoJson.h>
#include <ArduinoOTA.h>

#include <Interval.h>
#include <ScheduleRepository.h>
#include <SimpleWifi.h>

#include <ESP8266WebServer.h>

#define LED D0
#define SSID "AndroidAP"
#define PWD "joon3171"
#define SYNC_TIME 6000

SimpleWifi internet = SimpleWifi();
//SimpleServer server = SimpleServer();
ScheduleRepository scheduleRepo = ScheduleRepository();
Interval scheduleUpdater = Interval();
//DynamicJsonBuffer jsonBuffer;
ESP8266WebServer server(80);

bool isLedOn = false;

void handleRoot()
{
  Serial.println("LED switch");
  digitalWrite(LED, isLedOn);
  isLedOn = !isLedOn;
  Serial.println("ROT");
  String json = scheduleRepo.get();
  
  JsonObject &root = jsonBuffer.parseObject(json);
  //JsonObject &next = root["09902"]; // String(root["09902"].as<String>());//["30009902"]);
  //root.printTo(json)
    
  server.send(200, "text/json",json);
}



void handleNotFound(){
  Serial.println("LED switch");
  digitalWrite(LED, isLedOn);
  isLedOn = !isLedOn;
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setupOTA() {
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
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
}

void setupServer() {
  server.on("/", handleRoot);

  server.on("/inline", [](){
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

  internet.begin(SSID,PWD);

  setupOTA();

  scheduleUpdater.begin(SYNC_TIME, [&]() { scheduleRepo.set(); });

  setupServer();
}

void loop(void)
{
  server.handleClient();
  scheduleUpdater.loop();
  ArduinoOTA.handle();
}
