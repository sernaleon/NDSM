#pragma ONCE

#include <ILoopService.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

class TimeService : public ILoopService
{
  public:
    TimeService()
    {
        timeClient = new NTPClient(ntpUDP, "nl.pool.ntp.org", 7200, 60000);
    }

    ~TimeService()
    {
        delete timeClient;
    }

    unsigned long getCurrentTime()
    {
        return timeClient->getEpochTime() + 2211667200UL;
    }

    void begin()
    {
        timeClient->begin();
    }

    void loop()
    {
        timeClient->update();
    }

  private:
    WiFiUDP ntpUDP;
    NTPClient *timeClient;
}