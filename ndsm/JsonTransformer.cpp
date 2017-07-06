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

    if (parsedTime > currentTime)
    {
      //Past time. Ignore.
    }
    else if (partialDestination.equals("CS"))
    {
      addSorted(result.central, parsedTime);
    }
    else if (partialDestination.equals("WTDD"))
    {
      addSorted(result.west, parsedTime);
    }

    partialDestination = "";
    partialTime = "";
  }
}

Schedules JsonTransformer::parseJson(String json, unsigned long current)
{
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

  return result;
}
