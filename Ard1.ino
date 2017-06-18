#include <ArduinoJson.h>

#include "Interval.h"
#include "ScheduleRepository.h"
#include "SimpleServer.h"
#include "SimpleWifi.h"

#define LED D0
#define SSID "AndroidAP"
#define PWD "joon3171"
#define SYNC_TIME 60000

SimpleWifi internet = SimpleWifi();
SimpleServer server = SimpleServer();
ScheduleRepository scheduleRepo = ScheduleRepository();
Interval scheduleUpdater = Interval();
DynamicJsonBuffer jsonBuffer;

bool isLedOn = false;

void beforeRequest()
{
  Serial.println("LED switch");
  digitalWrite(LED, isLedOn);
  isLedOn = !isLedOn;
}

void handleRoot()
{
  Serial.println("ROOT");
  String json = scheduleRepo.get();

  // JsonObject &root = jsonBuffer.parseObject(json);
  //JsonObject &next = root["09902"]; // String(root["09902"].as<String>());//["30009902"]);
  //root.printTo(json)
  //  server.send(next);

  server.send(json);
}

void setup(void)
{
  Serial.begin(115200);
  Serial.println("SIP");

  pinMode(LED, OUTPUT);

  internet.begin(SSID,PWD);

  scheduleUpdater.begin(SYNC_TIME, [&]() { scheduleRepo.set(); });

  server.begin();
  server.beforeEachRequest(beforeRequest);
  server.on("/", handleRoot);
}

void loop(void)
{
  server.loop();
  scheduleUpdater.loop();
}
