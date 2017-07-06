#pragma once

#include <ESP8266mDNS.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

using namespace std;

class SimpleWifi
{
public:
  inline void begin(const char *ssid, const char *password)
  {
    WiFi.begin(ssid, password);

    Serial.print("Connecting to ");
    Serial.print(ssid);
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(500);
      Serial.print(".");
    }
    Serial.println("connected!");

    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    if (MDNS.begin("esp8266"))
    {
      Serial.println("MDNS responder started");
    }
  }
};
