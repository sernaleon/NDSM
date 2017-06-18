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
  void begin(const char *ssid, const char *pwd);

  void start();  
  void on(const char* uri, function<void(void)> handler);
  void beforeEachRequest(function<void(void)> beforeEachHandler);
  void send(String message);

  void loop();

private:
  ESP8266WebServer server;
  function<void(void)> beforeEachHandler;
  const char *ssid;
  const char *password;
  int port;

  void handleNotFound();
};

#endif
