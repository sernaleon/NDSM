#pragma once

#include <ESP8266HTTPClient.h>

class OvApi
{
public:
  inline String getDeparturesJson()
  {
    String value;
    HTTPClient http;
    http.begin("http://v0.ovapi.nl/stopareacode/09902/departures");
    int httpCode = http.GET();

    if (httpCode == HTTP_CODE_OK)
    {
      value = http.getString();
    }
    else
    {
      Serial.printf("[HTTP] GET failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();

    return value;
  }
};
