#pragma once

#include <time.h>
#include "Arduino.h"

class TimeParser
{
public:
  inline static String toString(tm t1)
  {
    return String(t1.tm_hour) + ":" + String(t1.tm_min) + ":" + String(t1.tm_sec) +
           " " + String(t1.tm_mday) + "/" + String(t1.tm_mon) + "/" + String(t1.tm_year);
  }
  inline void print(tm t1)
  {
    Serial.println(toString(t1));
  }
  inline bool firstIsNewer(tm t1, tm t2)
  {
    unsigned long d1 = mktime(&t1);
    unsigned long d2 = mktime(&t2);

    return d1 < d2;
  }
  inline tm parse(String timeString)
  {
    // 2017-06-20T07:25:00
    struct tm tm;
    char str[20];
    timeString.toCharArray(str, 20);
    char *pch;
    char *a = strtok(str, "-");
    char *mon = strtok(NULL, "-");
    char *d = strtok(NULL, "T");
    char *h = strtok(NULL, ":");
    char *min = strtok(NULL, ":");
    char *s = strtok(NULL, ":");

    tm.tm_year = String(a).toInt();
    tm.tm_mon = String(mon).toInt();
    tm.tm_mday = String(d).toInt();
    tm.tm_hour = String(h).toInt();
    tm.tm_min = String(min).toInt();
    tm.tm_sec = String(s).toInt();

    return tm;
  }
};
