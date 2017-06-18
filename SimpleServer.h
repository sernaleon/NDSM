#ifndef SIMPLE_SERVER_H
#define SIMPLE_SERVER_H

#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#include <functional>

using namespace std;

class SimpleServer
{
public:
  void begin();

  void beforeEachRequest(function<void(void)> beforeEachHandler);

  void on(const char* uri, function<void(void)> handler);

  void send(String message);

  void loop();

private:
  ESP8266WebServer server;
  function<void(void)> beforeEachHandler;

  void handleNotFound();
};

#endif
