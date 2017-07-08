#pragma once

class ILoopService
{
  public:
    virtual void begin();
    virtual void loop();
};