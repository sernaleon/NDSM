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
#define SYNC_TIME 1000

SimpleWifi internet = SimpleWifi();
ScheduleRepository scheduleRepo = ScheduleRepository();
Interval scheduleUpdater = Interval();
ESP8266WebServer server(80);

bool isLedOn = false;

void handleRoot()
{
  Serial.println("LED switch");
  digitalWrite(LED, isLedOn);
  isLedOn = !isLedOn;
  Serial.println("ROT");

  //  String json = scheduleRepo.get();

const size_t bufferSize = JSON_OBJECT_SIZE(0) + 2*JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(10) + 10*JSON_OBJECT_SIZE(33) + 9880;
DynamicJsonBuffer jsonBuffer(bufferSize); //14632

const char* json = "{\"09902\":{\"30009902\":{\"Stop\":{\"Longitude\":4.8917375,\"Latitude\":52.40094,\"TimingPointTown\":\"Amsterdam\",\"TimingPointName\":\"NDSM\",\"TimingPointCode\":\"30009902\",\"StopAreaCode\":\"09902\"},\"Passes\":{\"GVB_20170620_906_4_0\":{\"IsTimingStop\":true,\"DestinationName50\":\"Centraal Station\",\"DataOwnerCode\":\"GVB\",\"OperatorCode\":\"GVB\",\"FortifyOrderNumber\":0,\"TransportType\":\"BOAT\",\"Latitude\":52.40094,\"Longitude\":4.8917375,\"JourneyNumber\":4,\"JourneyPatternCode\":1287555197,\"LocalServiceLevelCode\":20170620,\"LineDirection\":1,\"OperationDate\":\"2017-06-20\",\"TimingPointCode\":\"30009902\",\"WheelChairAccessible\":\"ACCESSIBLE\",\"LineName\":\"NDSM - Centraal Station\",\"LinePublicNumber\":\"906\",\"LastUpdateTimeStamp\":\"2017-06-17T10:45:33+0200\",\"DestinationCode\":\"CS\",\"ExpectedDepartureTime\":\"2017-06-20T07:00:00\",\"UserStopOrderNumber\":1,\"ProductFormulaType\":\"18\",\"TimingPointName\":\"NDSM\",\"LinePlanningNumber\":\"906\",\"StopAreaCode\":\"09902\",\"TimingPointDataOwnerCode\":\"ALGEMEEN\",\"TimingPointTown\":\"Amsterdam\",\"TripStopStatus\":\"PLANNED\",\"UserStopCode\":\"09902\",\"JourneyStopType\":\"FIRST\",\"TargetArrivalTime\":\"2017-06-20T07:00:00\",\"TargetDepartureTime\":\"2017-06-20T07:00:00\",\"ExpectedArrivalTime\":\"2017-06-20T07:00:00\"},\"GVB_20170620_906_10_0\":{\"IsTimingStop\":true,\"DestinationName50\":\"Centraal Station\",\"DataOwnerCode\":\"GVB\",\"OperatorCode\":\"GVB\",\"FortifyOrderNumber\":0,\"TransportType\":\"BOAT\",\"Latitude\":52.40094,\"Longitude\":4.8917375,\"JourneyNumber\":10,\"JourneyPatternCode\":1287555197,\"LocalServiceLevelCode\":20170620,\"LineDirection\":1,\"OperationDate\":\"2017-06-20\",\"TimingPointCode\":\"30009902\",\"WheelChairAccessible\":\"ACCESSIBLE\",\"LineName\":\"NDSM - Centraal Station\",\"LinePublicNumber\":\"906\",\"LastUpdateTimeStamp\":\"2017-06-17T10:45:33+0200\",\"DestinationCode\":\"CS\",\"ExpectedDepartureTime\":\"2017-06-20T07:30:00\",\"UserStopOrderNumber\":1,\"ProductFormulaType\":\"18\",\"TimingPointName\":\"NDSM\",\"LinePlanningNumber\":\"906\",\"StopAreaCode\":\"09902\",\"TimingPointDataOwnerCode\":\"ALGEMEEN\",\"TimingPointTown\":\"Amsterdam\",\"TripStopStatus\":\"PLANNED\",\"UserStopCode\":\"09902\",\"JourneyStopType\":\"FIRST\",\"TargetArrivalTime\":\"2017-06-20T07:30:00\",\"TargetDepartureTime\":\"2017-06-20T07:30:00\",\"ExpectedArrivalTime\":\"2017-06-20T07:30:00\"},\"GVB_20170620_906_23_0\":{\"IsTimingStop\":true,\"DestinationName50\":\"Centraal Station\",\"DataOwnerCode\":\"GVB\",\"OperatorCode\":\"GVB\",\"FortifyOrderNumber\":0,\"TransportType\":\"BOAT\",\"Latitude\":52.40094,\"Longitude\":4.8917375,\"JourneyNumber\":23,\"JourneyPatternCode\":1287555197,\"LocalServiceLevelCode\":20170620,\"LineDirection\":1,\"OperationDate\":\"2017-06-20\",\"TimingPointCode\":\"30009902\",\"WheelChairAccessible\":\"ACCESSIBLE\",\"LineName\":\"NDSM - Centraal Station\",\"LinePublicNumber\":\"906\",\"LastUpdateTimeStamp\":\"2017-06-17T10:45:33+0200\",\"DestinationCode\":\"CS\",\"ExpectedDepartureTime\":\"2017-06-20T08:15:00\",\"UserStopOrderNumber\":1,\"ProductFormulaType\":\"18\",\"TimingPointName\":\"NDSM\",\"LinePlanningNumber\":\"906\",\"StopAreaCode\":\"09902\",\"TimingPointDataOwnerCode\":\"ALGEMEEN\",\"TimingPointTown\":\"Amsterdam\",\"TripStopStatus\":\"PLANNED\",\"UserStopCode\":\"09902\",\"JourneyStopType\":\"FIRST\",\"TargetArrivalTime\":\"2017-06-20T08:15:00\",\"TargetDepartureTime\":\"2017-06-20T08:15:00\",\"ExpectedArrivalTime\":\"2017-06-20T08:15:00\"},\"GVB_20170620_903_22_0\":{\"IsTimingStop\":true,\"DestinationName50\":\"Westerdoksdijk\",\"DataOwnerCode\":\"GVB\",\"OperatorCode\":\"GVB\",\"FortifyOrderNumber\":0,\"TransportType\":\"BOAT\",\"Latitude\":52.40094,\"Longitude\":4.8917375,\"JourneyNumber\":22,\"JourneyPatternCode\":1770403151,\"LocalServiceLevelCode\":20170620,\"LineDirection\":2,\"OperationDate\":\"2017-06-20\",\"TimingPointCode\":\"30009902\",\"WheelChairAccessible\":\"ACCESSIBLE\",\"LineName\":\"Westerdoksdijk - NDSM\",\"LinePublicNumber\":\"903\",\"LastUpdateTimeStamp\":\"2017-06-17T10:45:33+0200\",\"DestinationCode\":\"WTDD\",\"ExpectedDepartureTime\":\"2017-06-20T08:05:00\",\"UserStopOrderNumber\":1,\"ProductFormulaType\":\"18\",\"TimingPointName\":\"NDSM\",\"LinePlanningNumber\":\"903\",\"StopAreaCode\":\"09902\",\"TimingPointDataOwnerCode\":\"ALGEMEEN\",\"TimingPointTown\":\"Amsterdam\",\"TripStopStatus\":\"PLANNED\",\"UserStopCode\":\"09902\",\"JourneyStopType\":\"FIRST\",\"TargetArrivalTime\":\"2017-06-20T08:05:00\",\"TargetDepartureTime\":\"2017-06-20T08:05:00\",\"ExpectedArrivalTime\":\"2017-06-20T08:05:00\"},\"GVB_20170620_903_10_0\":{\"IsTimingStop\":true,\"DestinationName50\":\"Westerdoksdijk\",\"DataOwnerCode\":\"GVB\",\"OperatorCode\":\"GVB\",\"FortifyOrderNumber\":0,\"TransportType\":\"BOAT\",\"Latitude\":52.40094,\"Longitude\":4.8917375,\"JourneyNumber\":10,\"JourneyPatternCode\":1770403151,\"LocalServiceLevelCode\":20170620,\"LineDirection\":2,\"OperationDate\":\"2017-06-20\",\"TimingPointCode\":\"30009902\",\"WheelChairAccessible\":\"ACCESSIBLE\",\"LineName\":\"Westerdoksdijk - NDSM\",\"LinePublicNumber\":\"903\",\"LastUpdateTimeStamp\":\"2017-06-17T10:45:33+0200\",\"DestinationCode\":\"WTDD\",\"ExpectedDepartureTime\":\"2017-06-20T07:05:00\",\"UserStopOrderNumber\":1,\"ProductFormulaType\":\"18\",\"TimingPointName\":\"NDSM\",\"LinePlanningNumber\":\"903\",\"StopAreaCode\":\"09902\",\"TimingPointDataOwnerCode\":\"ALGEMEEN\",\"TimingPointTown\":\"Amsterdam\",\"TripStopStatus\":\"PLANNED\",\"UserStopCode\":\"09902\",\"JourneyStopType\":\"FIRST\",\"TargetArrivalTime\":\"2017-06-20T07:05:00\",\"TargetDepartureTime\":\"2017-06-20T07:05:00\",\"ExpectedArrivalTime\":\"2017-06-20T07:05:00\"},\"GVB_20170620_906_18_0\":{\"IsTimingStop\":true,\"DestinationName50\":\"Centraal Station\",\"DataOwnerCode\":\"GVB\",\"OperatorCode\":\"GVB\",\"FortifyOrderNumber\":0,\"TransportType\":\"BOAT\",\"Latitude\":52.40094,\"Longitude\":4.8917375,\"JourneyNumber\":18,\"JourneyPatternCode\":1287555197,\"LocalServiceLevelCode\":20170620,\"LineDirection\":1,\"OperationDate\":\"2017-06-20\",\"TimingPointCode\":\"30009902\",\"WheelChairAccessible\":\"ACCESSIBLE\",\"LineName\":\"NDSM - Centraal Station\",\"LinePublicNumber\":\"906\",\"LastUpdateTimeStamp\":\"2017-06-17T10:45:33+0200\",\"DestinationCode\":\"CS\",\"ExpectedDepartureTime\":\"2017-06-20T08:00:00\",\"UserStopOrderNumber\":1,\"ProductFormulaType\":\"18\",\"TimingPointName\":\"NDSM\",\"LinePlanningNumber\":\"906\",\"StopAreaCode\":\"09902\",\"TimingPointDataOwnerCode\":\"ALGEMEEN\",\"TimingPointTown\":\"Amsterdam\",\"TripStopStatus\":\"PLANNED\",\"UserStopCode\":\"09902\",\"JourneyStopType\":\"FIRST\",\"TargetArrivalTime\":\"2017-06-20T08:00:00\",\"TargetDepartureTime\":\"2017-06-20T08:00:00\",\"ExpectedArrivalTime\":\"2017-06-20T08:00:00\"},\"GVB_20170620_903_6_0\":{\"IsTimingStop\":true,\"DestinationName50\":\"Westerdoksdijk\",\"DataOwnerCode\":\"GVB\",\"OperatorCode\":\"GVB\",\"FortifyOrderNumber\":0,\"TransportType\":\"BOAT\",\"Latitude\":52.40094,\"Longitude\":4.8917375,\"JourneyNumber\":6,\"JourneyPatternCode\":1770403151,\"LocalServiceLevelCode\":20170620,\"LineDirection\":2,\"OperationDate\":\"2017-06-20\",\"TimingPointCode\":\"30009902\",\"WheelChairAccessible\":\"ACCESSIBLE\",\"LineName\":\"Westerdoksdijk - NDSM\",\"LinePublicNumber\":\"903\",\"LastUpdateTimeStamp\":\"2017-06-17T10:45:33+0200\",\"DestinationCode\":\"WTDD\",\"ExpectedDepartureTime\":\"2017-06-20T06:45:00\",\"UserStopOrderNumber\":1,\"ProductFormulaType\":\"18\",\"TimingPointName\":\"NDSM\",\"LinePlanningNumber\":\"903\",\"StopAreaCode\":\"09902\",\"TimingPointDataOwnerCode\":\"ALGEMEEN\",\"TimingPointTown\":\"Amsterdam\",\"TripStopStatus\":\"PLANNED\",\"UserStopCode\":\"09902\",\"JourneyStopType\":\"FIRST\",\"TargetArrivalTime\":\"2017-06-20T06:45:00\",\"TargetDepartureTime\":\"2017-06-20T06:45:00\",\"ExpectedArrivalTime\":\"2017-06-20T06:45:00\"},\"GVB_20170620_906_15_0\":{\"IsTimingStop\":true,\"DestinationName50\":\"Centraal Station\",\"DataOwnerCode\":\"GVB\",\"OperatorCode\":\"GVB\",\"FortifyOrderNumber\":0,\"TransportType\":\"BOAT\",\"Latitude\":52.40094,\"Longitude\":4.8917375,\"JourneyNumber\":15,\"JourneyPatternCode\":1287555197,\"LocalServiceLevelCode\":20170620,\"LineDirection\":1,\"OperationDate\":\"2017-06-20\",\"TimingPointCode\":\"30009902\",\"WheelChairAccessible\":\"ACCESSIBLE\",\"LineName\":\"NDSM - Centraal Station\",\"LinePublicNumber\":\"906\",\"LastUpdateTimeStamp\":\"2017-06-17T10:45:33+0200\",\"DestinationCode\":\"CS\",\"ExpectedDepartureTime\":\"2017-06-20T07:45:00\",\"UserStopOrderNumber\":1,\"ProductFormulaType\":\"18\",\"TimingPointName\":\"NDSM\",\"LinePlanningNumber\":\"906\",\"StopAreaCode\":\"09902\",\"TimingPointDataOwnerCode\":\"ALGEMEEN\",\"TimingPointTown\":\"Amsterdam\",\"TripStopStatus\":\"PLANNED\",\"UserStopCode\":\"09902\",\"JourneyStopType\":\"FIRST\",\"TargetArrivalTime\":\"2017-06-20T07:45:00\",\"TargetDepartureTime\":\"2017-06-20T07:45:00\",\"ExpectedArrivalTime\":\"2017-06-20T07:45:00\"},\"GVB_20170620_903_18_0\":{\"IsTimingStop\":true,\"DestinationName50\":\"Westerdoksdijk\",\"DataOwnerCode\":\"GVB\",\"OperatorCode\":\"GVB\",\"FortifyOrderNumber\":0,\"TransportType\":\"BOAT\",\"Latitude\":52.40094,\"Longitude\":4.8917375,\"JourneyNumber\":18,\"JourneyPatternCode\":1770403151,\"LocalServiceLevelCode\":20170620,\"LineDirection\":2,\"OperationDate\":\"2017-06-20\",\"TimingPointCode\":\"30009902\",\"WheelChairAccessible\":\"ACCESSIBLE\",\"LineName\":\"Westerdoksdijk - NDSM\",\"LinePublicNumber\":\"903\",\"LastUpdateTimeStamp\":\"2017-06-17T10:45:33+0200\",\"DestinationCode\":\"WTDD\",\"ExpectedDepartureTime\":\"2017-06-20T07:45:00\",\"UserStopOrderNumber\":1,\"ProductFormulaType\":\"18\",\"TimingPointName\":\"NDSM\",\"LinePlanningNumber\":\"903\",\"StopAreaCode\":\"09902\",\"TimingPointDataOwnerCode\":\"ALGEMEEN\",\"TimingPointTown\":\"Amsterdam\",\"TripStopStatus\":\"PLANNED\",\"UserStopCode\":\"09902\",\"JourneyStopType\":\"FIRST\",\"TargetArrivalTime\":\"2017-06-20T07:45:00\",\"TargetDepartureTime\":\"2017-06-20T07:45:00\",\"ExpectedArrivalTime\":\"2017-06-20T07:45:00\"},\"GVB_20170620_903_14_0\":{\"IsTimingStop\":true,\"DestinationName50\":\"Westerdoksdijk\",\"DataOwnerCode\":\"GVB\",\"OperatorCode\":\"GVB\",\"FortifyOrderNumber\":0,\"TransportType\":\"BOAT\",\"Latitude\":52.40094,\"Longitude\":4.8917375,\"JourneyNumber\":14,\"JourneyPatternCode\":1770403151,\"LocalServiceLevelCode\":20170620,\"LineDirection\":2,\"OperationDate\":\"2017-06-20\",\"TimingPointCode\":\"30009902\",\"WheelChairAccessible\":\"ACCESSIBLE\",\"LineName\":\"Westerdoksdijk - NDSM\",\"LinePublicNumber\":\"903\",\"LastUpdateTimeStamp\":\"2017-06-17T10:45:33+0200\",\"DestinationCode\":\"WTDD\",\"ExpectedDepartureTime\":\"2017-06-20T07:25:00\",\"UserStopOrderNumber\":1,\"ProductFormulaType\":\"18\",\"TimingPointName\":\"NDSM\",\"LinePlanningNumber\":\"903\",\"StopAreaCode\":\"09902\",\"TimingPointDataOwnerCode\":\"ALGEMEEN\",\"TimingPointTown\":\"Amsterdam\",\"TripStopStatus\":\"PLANNED\",\"UserStopCode\":\"09902\",\"JourneyStopType\":\"FIRST\",\"TargetArrivalTime\":\"2017-06-20T07:25:00\",\"TargetDepartureTime\":\"2017-06-20T07:25:00\",\"ExpectedArrivalTime\":\"2017-06-20T07:25:00\"}},\"GeneralMessages\":{}}}}";

  JsonObject &root = jsonBuffer.parseObject(json);
  JsonObject& next = root["09902"]["30009902"]["Passes"];

  String output;
  next.prettyPrintTo(output);

  server.send(200, "text/json", output);
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

  scheduleUpdater.begin(SYNC_TIME, [&]() { scheduleRepo.set(); });

  setupServer();
}

void loop(void)
{
  server.handleClient();
  scheduleUpdater.loop();
  ArduinoOTA.handle();
}
