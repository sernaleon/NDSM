#ifndef SIMPLE_WIFI_H
#define SIMPLE_WIFI_H

#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#include <functional>

using namespace std;

class SimpleWifi
{
public:
  void begin(const char *ssid, const char *password);
};

#endif
