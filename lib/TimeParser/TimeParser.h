#pragma once

#include <time.h>
#include "Arduino.h"

class TimeParser
{
public:
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
  inline unsigned long parseToLinuxTime(String timeString)
  {
    struct tm tm = parse(timeString);
    return mktime(&tm);
  }
};
