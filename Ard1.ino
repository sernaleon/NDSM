#include <ArduinoJson.h>

#include "Interval.h"
#include "ScheduleRepository.h"
#include "SimpleServer.h"

#define LED D0
#define SSID "AndroidAP"
#define PWD "joon3171"
#define SERVER_PORT 80
#define SYNC_TIME 60000

SimpleServer server = SimpleServer(SSID, PWD, SERVER_PORT);
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
  Serial.println("PRIMI");
  String json = scheduleRepo.get();

  // JsonObject &root = jsonBuffer.parseObject(json);
  //JsonObject &next = root["09902"]; // String(root["09902"].as<String>());//["30009902"]);
  //root.printTo(json)
  //  server.send(next);
  Serial.println("LA SEGUNDA YA TAL");

  server.send(json);
}

void syncJson(){
    scheduleRepo.set();
    /*
    ([&](){scheduleRepo.set();});
    */
}

void setup(void)
{
  Serial.begin(115200);
  Serial.println("SIP");


  scheduleUpdater.begin(SYNC_TIME, syncJson);

  pinMode(LED, OUTPUT);

  server.start();
  server.beforeEachRequest(beforeRequest);
  server.on("/", handleRoot);
}

void loop(void)
{
  server.loop();
  scheduleUpdater.loop();
}
