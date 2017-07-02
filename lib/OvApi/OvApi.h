#pragma once

#include <ESP8266HTTPClient.h>

class OvApi
{
public:
  inline String getDeparturesJson()
  {
    return "{\"09902\":{\"30009902\":{\"Stop\":{\"Longitude\":4.8917375,\"Latitude\":52.40094,\"TimingPointTown\":\"Amsterdam\",\"TimingPointName\":\"NDSM\",\"TimingPointCode\":\"30009902\",\"StopAreaCode\":\"09902\"},\"Passes\":{\"GVB_20170620_906_4_0\":{\"IsTimingStop\":true,\"DestinationName50\":\"Centraal Station\",\"DataOwnerCode\":\"GVB\",\"OperatorCode\":\"GVB\",\"FortifyOrderNumber\":0,\"TransportType\":\"BOAT\",\"Latitude\":52.40094,\"Longitude\":4.8917375,\"JourneyNumber\":4,\"JourneyPatternCode\":1287555197,\"LocalServiceLevelCode\":20170620,\"LineDirection\":1,\"OperationDate\":\"2017-06-20\",\"TimingPointCode\":\"30009902\",\"WheelChairAccessible\":\"ACCESSIBLE\",\"LineName\":\"NDSM - Centraal Station\",\"LinePublicNumber\":\"906\",\"LastUpdateTimeStamp\":\"2017-06-17T10:45:33+0200\",\"DestinationCode\":\"CS\",\"ExpectedDepartureTime\":\"2017-06-20T07:00:00\",\"UserStopOrderNumber\":1,\"ProductFormulaType\":\"18\",\"TimingPointName\":\"NDSM\",\"LinePlanningNumber\":\"906\",\"StopAreaCode\":\"09902\",\"TimingPointDataOwnerCode\":\"ALGEMEEN\",\"TimingPointTown\":\"Amsterdam\",\"TripStopStatus\":\"PLANNED\",\"UserStopCode\":\"09902\",\"JourneyStopType\":\"FIRST\",\"TargetArrivalTime\":\"2017-06-20T07:00:00\",\"TargetDepartureTime\":\"2017-06-20T07:00:00\",\"ExpectedArrivalTime\":\"2017-06-20T07:00:00\"},\"GVB_20170620_906_10_0\":{\"IsTimingStop\":true,\"DestinationName50\":\"Centraal Station\",\"DataOwnerCode\":\"GVB\",\"OperatorCode\":\"GVB\",\"FortifyOrderNumber\":0,\"TransportType\":\"BOAT\",\"Latitude\":52.40094,\"Longitude\":4.8917375,\"JourneyNumber\":10,\"JourneyPatternCode\":1287555197,\"LocalServiceLevelCode\":20170620,\"LineDirection\":1,\"OperationDate\":\"2017-06-20\",\"TimingPointCode\":\"30009902\",\"WheelChairAccessible\":\"ACCESSIBLE\",\"LineName\":\"NDSM - Centraal Station\",\"LinePublicNumber\":\"906\",\"LastUpdateTimeStamp\":\"2017-06-17T10:45:33+0200\",\"DestinationCode\":\"CS\",\"ExpectedDepartureTime\":\"2017-06-20T07:30:00\",\"UserStopOrderNumber\":1,\"ProductFormulaType\":\"18\",\"TimingPointName\":\"NDSM\",\"LinePlanningNumber\":\"906\",\"StopAreaCode\":\"09902\",\"TimingPointDataOwnerCode\":\"ALGEMEEN\",\"TimingPointTown\":\"Amsterdam\",\"TripStopStatus\":\"PLANNED\",\"UserStopCode\":\"09902\",\"JourneyStopType\":\"FIRST\",\"TargetArrivalTime\":\"2017-06-20T07:30:00\",\"TargetDepartureTime\":\"2017-06-20T07:30:00\",\"ExpectedArrivalTime\":\"2017-06-20T07:30:00\"},\"GVB_20170620_906_23_0\":{\"IsTimingStop\":true,\"DestinationName50\":\"Centraal Station\",\"DataOwnerCode\":\"GVB\",\"OperatorCode\":\"GVB\",\"FortifyOrderNumber\":0,\"TransportType\":\"BOAT\",\"Latitude\":52.40094,\"Longitude\":4.8917375,\"JourneyNumber\":23,\"JourneyPatternCode\":1287555197,\"LocalServiceLevelCode\":20170620,\"LineDirection\":1,\"OperationDate\":\"2017-06-20\",\"TimingPointCode\":\"30009902\",\"WheelChairAccessible\":\"ACCESSIBLE\",\"LineName\":\"NDSM - Centraal Station\",\"LinePublicNumber\":\"906\",\"LastUpdateTimeStamp\":\"2017-06-17T10:45:33+0200\",\"DestinationCode\":\"CS\",\"ExpectedDepartureTime\":\"2017-06-20T08:15:00\",\"UserStopOrderNumber\":1,\"ProductFormulaType\":\"18\",\"TimingPointName\":\"NDSM\",\"LinePlanningNumber\":\"906\",\"StopAreaCode\":\"09902\",\"TimingPointDataOwnerCode\":\"ALGEMEEN\",\"TimingPointTown\":\"Amsterdam\",\"TripStopStatus\":\"PLANNED\",\"UserStopCode\":\"09902\",\"JourneyStopType\":\"FIRST\",\"TargetArrivalTime\":\"2017-06-20T08:15:00\",\"TargetDepartureTime\":\"2017-06-20T08:15:00\",\"ExpectedArrivalTime\":\"2017-06-20T08:15:00\"},\"GVB_20170620_903_22_0\":{\"IsTimingStop\":true,\"DestinationName50\":\"Westerdoksdijk\",\"DataOwnerCode\":\"GVB\",\"OperatorCode\":\"GVB\",\"FortifyOrderNumber\":0,\"TransportType\":\"BOAT\",\"Latitude\":52.40094,\"Longitude\":4.8917375,\"JourneyNumber\":22,\"JourneyPatternCode\":1770403151,\"LocalServiceLevelCode\":20170620,\"LineDirection\":2,\"OperationDate\":\"2017-06-20\",\"TimingPointCode\":\"30009902\",\"WheelChairAccessible\":\"ACCESSIBLE\",\"LineName\":\"Westerdoksdijk - NDSM\",\"LinePublicNumber\":\"903\",\"LastUpdateTimeStamp\":\"2017-06-17T10:45:33+0200\",\"DestinationCode\":\"WTDD\",\"ExpectedDepartureTime\":\"2017-06-20T08:05:00\",\"UserStopOrderNumber\":1,\"ProductFormulaType\":\"18\",\"TimingPointName\":\"NDSM\",\"LinePlanningNumber\":\"903\",\"StopAreaCode\":\"09902\",\"TimingPointDataOwnerCode\":\"ALGEMEEN\",\"TimingPointTown\":\"Amsterdam\",\"TripStopStatus\":\"PLANNED\",\"UserStopCode\":\"09902\",\"JourneyStopType\":\"FIRST\",\"TargetArrivalTime\":\"2017-06-20T08:05:00\",\"TargetDepartureTime\":\"2017-06-20T08:05:00\",\"ExpectedArrivalTime\":\"2017-06-20T08:05:00\"},\"GVB_20170620_903_10_0\":{\"IsTimingStop\":true,\"DestinationName50\":\"Westerdoksdijk\",\"DataOwnerCode\":\"GVB\",\"OperatorCode\":\"GVB\",\"FortifyOrderNumber\":0,\"TransportType\":\"BOAT\",\"Latitude\":52.40094,\"Longitude\":4.8917375,\"JourneyNumber\":10,\"JourneyPatternCode\":1770403151,\"LocalServiceLevelCode\":20170620,\"LineDirection\":2,\"OperationDate\":\"2017-06-20\",\"TimingPointCode\":\"30009902\",\"WheelChairAccessible\":\"ACCESSIBLE\",\"LineName\":\"Westerdoksdijk - NDSM\",\"LinePublicNumber\":\"903\",\"LastUpdateTimeStamp\":\"2017-06-17T10:45:33+0200\",\"DestinationCode\":\"WTDD\",\"ExpectedDepartureTime\":\"2017-06-20T07:05:00\",\"UserStopOrderNumber\":1,\"ProductFormulaType\":\"18\",\"TimingPointName\":\"NDSM\",\"LinePlanningNumber\":\"903\",\"StopAreaCode\":\"09902\",\"TimingPointDataOwnerCode\":\"ALGEMEEN\",\"TimingPointTown\":\"Amsterdam\",\"TripStopStatus\":\"PLANNED\",\"UserStopCode\":\"09902\",\"JourneyStopType\":\"FIRST\",\"TargetArrivalTime\":\"2017-06-20T07:05:00\",\"TargetDepartureTime\":\"2017-06-20T07:05:00\",\"ExpectedArrivalTime\":\"2017-06-20T07:05:00\"},\"GVB_20170620_906_18_0\":{\"IsTimingStop\":true,\"DestinationName50\":\"Centraal Station\",\"DataOwnerCode\":\"GVB\",\"OperatorCode\":\"GVB\",\"FortifyOrderNumber\":0,\"TransportType\":\"BOAT\",\"Latitude\":52.40094,\"Longitude\":4.8917375,\"JourneyNumber\":18,\"JourneyPatternCode\":1287555197,\"LocalServiceLevelCode\":20170620,\"LineDirection\":1,\"OperationDate\":\"2017-06-20\",\"TimingPointCode\":\"30009902\",\"WheelChairAccessible\":\"ACCESSIBLE\",\"LineName\":\"NDSM - Centraal Station\",\"LinePublicNumber\":\"906\",\"LastUpdateTimeStamp\":\"2017-06-17T10:45:33+0200\",\"DestinationCode\":\"CS\",\"ExpectedDepartureTime\":\"2017-06-20T08:00:00\",\"UserStopOrderNumber\":1,\"ProductFormulaType\":\"18\",\"TimingPointName\":\"NDSM\",\"LinePlanningNumber\":\"906\",\"StopAreaCode\":\"09902\",\"TimingPointDataOwnerCode\":\"ALGEMEEN\",\"TimingPointTown\":\"Amsterdam\",\"TripStopStatus\":\"PLANNED\",\"UserStopCode\":\"09902\",\"JourneyStopType\":\"FIRST\",\"TargetArrivalTime\":\"2017-06-20T08:00:00\",\"TargetDepartureTime\":\"2017-06-20T08:00:00\",\"ExpectedArrivalTime\":\"2017-06-20T08:00:00\"},\"GVB_20170620_903_6_0\":{\"IsTimingStop\":true,\"DestinationName50\":\"Westerdoksdijk\",\"DataOwnerCode\":\"GVB\",\"OperatorCode\":\"GVB\",\"FortifyOrderNumber\":0,\"TransportType\":\"BOAT\",\"Latitude\":52.40094,\"Longitude\":4.8917375,\"JourneyNumber\":6,\"JourneyPatternCode\":1770403151,\"LocalServiceLevelCode\":20170620,\"LineDirection\":2,\"OperationDate\":\"2017-06-20\",\"TimingPointCode\":\"30009902\",\"WheelChairAccessible\":\"ACCESSIBLE\",\"LineName\":\"Westerdoksdijk - NDSM\",\"LinePublicNumber\":\"903\",\"LastUpdateTimeStamp\":\"2017-06-17T10:45:33+0200\",\"DestinationCode\":\"WTDD\",\"ExpectedDepartureTime\":\"2017-06-20T06:45:00\",\"UserStopOrderNumber\":1,\"ProductFormulaType\":\"18\",\"TimingPointName\":\"NDSM\",\"LinePlanningNumber\":\"903\",\"StopAreaCode\":\"09902\",\"TimingPointDataOwnerCode\":\"ALGEMEEN\",\"TimingPointTown\":\"Amsterdam\",\"TripStopStatus\":\"PLANNED\",\"UserStopCode\":\"09902\",\"JourneyStopType\":\"FIRST\",\"TargetArrivalTime\":\"2017-06-20T06:45:00\",\"TargetDepartureTime\":\"2017-06-20T06:45:00\",\"ExpectedArrivalTime\":\"2017-06-20T06:45:00\"},\"GVB_20170620_906_15_0\":{\"IsTimingStop\":true,\"DestinationName50\":\"Centraal Station\",\"DataOwnerCode\":\"GVB\",\"OperatorCode\":\"GVB\",\"FortifyOrderNumber\":0,\"TransportType\":\"BOAT\",\"Latitude\":52.40094,\"Longitude\":4.8917375,\"JourneyNumber\":15,\"JourneyPatternCode\":1287555197,\"LocalServiceLevelCode\":20170620,\"LineDirection\":1,\"OperationDate\":\"2017-06-20\",\"TimingPointCode\":\"30009902\",\"WheelChairAccessible\":\"ACCESSIBLE\",\"LineName\":\"NDSM - Centraal Station\",\"LinePublicNumber\":\"906\",\"LastUpdateTimeStamp\":\"2017-06-17T10:45:33+0200\",\"DestinationCode\":\"CS\",\"ExpectedDepartureTime\":\"2017-06-20T07:45:00\",\"UserStopOrderNumber\":1,\"ProductFormulaType\":\"18\",\"TimingPointName\":\"NDSM\",\"LinePlanningNumber\":\"906\",\"StopAreaCode\":\"09902\",\"TimingPointDataOwnerCode\":\"ALGEMEEN\",\"TimingPointTown\":\"Amsterdam\",\"TripStopStatus\":\"PLANNED\",\"UserStopCode\":\"09902\",\"JourneyStopType\":\"FIRST\",\"TargetArrivalTime\":\"2017-06-20T07:45:00\",\"TargetDepartureTime\":\"2017-06-20T07:45:00\",\"ExpectedArrivalTime\":\"2017-06-20T07:45:00\"},\"GVB_20170620_903_18_0\":{\"IsTimingStop\":true,\"DestinationName50\":\"Westerdoksdijk\",\"DataOwnerCode\":\"GVB\",\"OperatorCode\":\"GVB\",\"FortifyOrderNumber\":0,\"TransportType\":\"BOAT\",\"Latitude\":52.40094,\"Longitude\":4.8917375,\"JourneyNumber\":18,\"JourneyPatternCode\":1770403151,\"LocalServiceLevelCode\":20170620,\"LineDirection\":2,\"OperationDate\":\"2017-06-20\",\"TimingPointCode\":\"30009902\",\"WheelChairAccessible\":\"ACCESSIBLE\",\"LineName\":\"Westerdoksdijk - NDSM\",\"LinePublicNumber\":\"903\",\"LastUpdateTimeStamp\":\"2017-06-17T10:45:33+0200\",\"DestinationCode\":\"WTDD\",\"ExpectedDepartureTime\":\"2017-06-20T07:45:00\",\"UserStopOrderNumber\":1,\"ProductFormulaType\":\"18\",\"TimingPointName\":\"NDSM\",\"LinePlanningNumber\":\"903\",\"StopAreaCode\":\"09902\",\"TimingPointDataOwnerCode\":\"ALGEMEEN\",\"TimingPointTown\":\"Amsterdam\",\"TripStopStatus\":\"PLANNED\",\"UserStopCode\":\"09902\",\"JourneyStopType\":\"FIRST\",\"TargetArrivalTime\":\"2017-06-20T07:45:00\",\"TargetDepartureTime\":\"2017-06-20T07:45:00\",\"ExpectedArrivalTime\":\"2017-06-20T07:45:00\"},\"GVB_20170620_903_14_0\":{\"IsTimingStop\":true,\"DestinationName50\":\"Westerdoksdijk\",\"DataOwnerCode\":\"GVB\",\"OperatorCode\":\"GVB\",\"FortifyOrderNumber\":0,\"TransportType\":\"BOAT\",\"Latitude\":52.40094,\"Longitude\":4.8917375,\"JourneyNumber\":14,\"JourneyPatternCode\":1770403151,\"LocalServiceLevelCode\":20170620,\"LineDirection\":2,\"OperationDate\":\"2017-06-20\",\"TimingPointCode\":\"30009902\",\"WheelChairAccessible\":\"ACCESSIBLE\",\"LineName\":\"Westerdoksdijk - NDSM\",\"LinePublicNumber\":\"903\",\"LastUpdateTimeStamp\":\"2017-06-17T10:45:33+0200\",\"DestinationCode\":\"WTDD\",\"ExpectedDepartureTime\":\"2017-06-20T07:25:00\",\"UserStopOrderNumber\":1,\"ProductFormulaType\":\"18\",\"TimingPointName\":\"NDSM\",\"LinePlanningNumber\":\"903\",\"StopAreaCode\":\"09902\",\"TimingPointDataOwnerCode\":\"ALGEMEEN\",\"TimingPointTown\":\"Amsterdam\",\"TripStopStatus\":\"PLANNED\",\"UserStopCode\":\"09902\",\"JourneyStopType\":\"FIRST\",\"TargetArrivalTime\":\"2017-06-20T07:25:00\",\"TargetDepartureTime\":\"2017-06-20T07:25:00\",\"ExpectedArrivalTime\":\"2017-06-20T07:25:00\"}},\"GeneralMessages\":{}}}}";

    String value;
    HTTPClient http;
    http.begin("http://v0.ovapi.nl/stopareacode/09902/departures");
    int httpCode = http.GET();

    Serial.printf("[HTTP] GET... code: %d\n", httpCode);

    if (httpCode == HTTP_CODE_OK)
    {
      value = http.getString();
    }
    else
    {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();

    return value;
  }
};
