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
    Serial.println(partialDestination + "=" + partialTime);

    TimeParser ts;
    ts.print(result.central[0]);
    ts.print(result.central[1]);
    
    if (partialDestination.equals("CS"))
    {
      tm parsedTime = ts.parse(partialTime);

      if (result.central[0].tm_year == 0)
      {
        result.central[0] = parsedTime;
      }
      else if (ts.firstIsNewer(parsedTime, result.central[0]))
      {
        result.central[1] = result.central[0];
        result.central[0] = parsedTime;
      }
      else
      {
        Serial.println("First is OLDER, NO-OP");
      }
    }
    else if (partialDestination.equals("WTDD"))
    {
    }
    else
    {
      Serial.println("WTF?!?!");
    }

    partialDestination = "";
    partialTime = "";
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
