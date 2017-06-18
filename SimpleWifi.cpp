
#include "SimpleWifi.h"

SimpleServer::SimpleServer(const char *ssid, const char *pwd, int port)
{
  this->ssid = ssid;
  this->password = pwd;
  this->port = port;
  this->server = ESP8266WebServer(port);
}

void SimpleServer::start()
{
  WiFi.begin(ssid, password);
  Serial.println("Vamos xarli!");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("amos ahi su puta madre conyeee Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266"))
  {
    Serial.println("MDNS responder started");
  }

  server.onNotFound([&]() {
    if (beforeEachHandler)
    {
      beforeEachHandler();
    }
    handleNotFound();
  });

  server.begin();
  Serial.println("HTTP server started");
}

void SimpleServer::beforeEachRequest(function<void(void)> beforeEachHandler)
{
  this->beforeEachHandler = beforeEachHandler;
}

void SimpleServer::on(const char *uri, function<void(void)> handler)
{
  server.on(uri, [&]() {
    if (beforeEachHandler)
    {
      beforeEachHandler();
    }
    handler();
  });
}

void SimpleServer::send(String message)
{
  server.send(200, "text/html", message);
}

void SimpleServer::loop()
{
  server.handleClient();
}

void SimpleServer::handleNotFound()
{
  String message = "Not Found\n\n";
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