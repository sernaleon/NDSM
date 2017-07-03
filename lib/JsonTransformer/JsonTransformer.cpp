#include "JsonTransformer.h"

/*
cosa = a["09902"]["30009902"]["Passes"]
for ( var c in cosa ) { 
   console.log(cosa[c]["DestinationCode"],cosa[c]["ExpectedDepartureTime"])
}
*/

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

void JsonTransformer::addSorted(unsigned long (&result)[2], unsigned long parsedTime)
{
  if (result[0] == 0 || parsedTime < result[0])
  {
    result[1] = result[0];
    result[0] = parsedTime;
  }
  else if (result[1] == 0 || parsedTime < result[1])
  {
    result[1] = parsedTime;
  }
}

void JsonTransformer::matcher()
{
  if (partialDestination.length() && partialTime.length())
  {
    TimeParser ts;
    unsigned long parsedTime = ts.parseToLinuxTime(partialTime);

    Serial.print(partialTime);
    Serial.print(" ");
    Serial.print(parsedTime);
    Serial.print("=");
    Serial.print(partialDestination);
    Serial.println();

    if (parsedTime <= currentTime)
    {
        Serial.println("Past time. Ignore.");
    }
    else if (partialDestination.equals("CS"))
    {
      addSorted(result.central, parsedTime);
    }
    else if (partialDestination.equals("WTDD"))
    {
      addSorted(result.west, parsedTime);
    }
    else
    {
      Serial.println("WTF?!?!");
    }

    partialDestination = "";
    partialTime = "";
  }
}

Schedules JsonTransformer::parseJson(String json, unsigned long current)
{
  Serial.println("About to parse json with length " + String(json.length()));
  Serial.print("Current time: ");
  Serial.println(currentTime);

  partialDestination = "";
  partialTime = "";
  catchADestination = false;
  catchATime = false;
  currentTime = current;
  JsonStreamingParser parser = JsonStreamingParser();
  parser.setListener(this);

  for (int i = 0; i < json.length(); i++)
  {
    parser.parse(json[i]);
  }

  Serial.print("Parse result: ");
  Serial.print( "C0: " + String(result.central[0]) + "\n" +
         "C1: " + String(result.central[1]) + "\n" +
         "W0: " + String(result.west[0]) + "\n" +
         "W1: " + String(result.west[1]) + "\n");

  return result;
}
