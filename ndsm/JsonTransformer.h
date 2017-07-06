#pragma once

#include "JsonStreamingParser.h"
#include "JsonListener.h"
#include "TimeParser.h"
#include <time.h>
#include "Schedules.h"

class JsonTransformer : public JsonListener
{
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

  Schedules parseJson(String json, unsigned long current);

private:
  void matcher();
  String partialDestination;
  String partialTime;
  unsigned long currentTime;

  bool catchATime;
  bool catchADestination;

  void addSorted(unsigned long (&result)[2], unsigned long parsedTime);

  Schedules result;
};