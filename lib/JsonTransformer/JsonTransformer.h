#pragma once

#include <JsonStreamingParser.h>
#include <JsonListener.h>
#include <TimeParser.h>
#include <time.h>

struct Schedules {
  tm central[2];
  tm west[2];
};

class JsonTransformer: public JsonListener {
  public:
    inline void whitespace(char c) {}
    inline void startDocument() {}
    inline void endDocument() {}
    inline void endArray() {}
    inline void endObject() {}
    inline void startArray() {}
    inline void startObject() {}
    virtual void key(String key);
    virtual void value(String value);

    Schedules parseJson(String json);
  private:
    void matcher();
    String partialDestination;
    String partialTime;

    bool catchATime;
    bool catchADestination;

    Schedules result;
};