#include "JsonTransformer.h"

void JsonTransformer::key(String key)
{
  if (key.equals("DestinationCode"))
  {
    catchADestination = true;
  }
  else if (key.equals("ExpectedDepartureTime"))
  {
    catchATime = true;
  }
}

void JsonTransformer::value(String value)
{
  if (catchADestination)
  {
    partialDestination = value;
    catchADestination = false;
    matcher();
  }
  else if (catchATime)
  {
    partialTime = value;
    catchATime = false;
    matcher();
  }
}

void JsonTransformer::matcher()
{
  if (partialDestination.length() && partialTime.length())
  {
    TimeParser ts;
    tm parsedTime = ts.parse(partialTime);

    Serial.print("PRE C0: ");
    ts.print(result.central[0]);
    Serial.print("PRE C1: ");
    ts.print(result.central[1]);
    Serial.print("PRE W0: ");
    ts.print(result.west[0]);
    Serial.print("PRE W1: ");
    ts.print(result.west[1]);

    Serial.print("-----IN: " + partialDestination + " ");
    ts.print(parsedTime);

    if (partialDestination.equals("CS"))
    {
      if (result.central[0].tm_year == 0 || ts.firstIsNewer(parsedTime, result.central[0]))
      {
        result.central[1] = result.central[0];
        result.central[0] = parsedTime;
      }
      else if (result.central[1].tm_year == 0 || ts.firstIsNewer(parsedTime, result.central[1]))
      {
        result.central[1] = parsedTime;
      }
    }
    else if (partialDestination.equals("WTDD"))
    {
      if (result.west[0].tm_year == 0 || ts.firstIsNewer(parsedTime, result.west[0]))
      {
        result.west[1] = result.west[0];
        result.west[0] = parsedTime;
      }
      else if (result.west[1].tm_year == 0 || ts.firstIsNewer(parsedTime, result.west[1]))
      {
        result.west[1] = parsedTime;
      }
    }
    else
    {
      Serial.println("WTF?!?!");
    }

    partialDestination = "";
    partialTime = "";

    Serial.print("POST C0: ");
    ts.print(result.central[0]);
    Serial.print("POST C1: ");
    ts.print(result.central[1]);
    Serial.print("POST W0: ");
    ts.print(result.west[0]);
    Serial.print("POST W1: ");
    ts.print(result.west[1]);
  }
}

Schedules JsonTransformer::parseJson(String json)
{
  Serial.println("Json length=" + String(json.length()));

  partialDestination = "";
  partialTime = "";
  catchADestination = false;
  catchATime = false;

  JsonStreamingParser parser = JsonStreamingParser();
  parser.setListener(this);

  for (int i = 0; i < json.length(); i++)
  {
    parser.parse(json[i]);
  }

  return result;
}
