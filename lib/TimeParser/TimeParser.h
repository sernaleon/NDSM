#pragma once

#include <time.h>

using namespace std;

class TimeParser
{
public:
  inline bool print(tm t1) {
    Serial.println(String(t1.tm_hour) + ":"  + String(t1.tm_min) + ":"  + String(t1.tm_sec) +
    " " + String(t1.tm_mday) + "/" + String(t1.tm_mon) + "/" + String(t1.tm_year));
  }
  inline bool firstIsNewer(tm t1, tm t2)
  {
    Serial.println("LE TIME 1: ");
    Serial.println("LE TIME 2: ");
    Serial.println(t2.tm_year);
    Serial.println(t2.tm_mon);
    Serial.println(t2.tm_mday);
    Serial.println(t2.tm_hour);
    Serial.println(t2.tm_min);
    Serial.println(t2.tm_sec);
    return mktime(&t1) < mktime(&t2);
  }
  inline tm parse(String timeString)
  {
    Serial.println(timeString);
      // 2017-06-20T07:25:00
    struct tm tm;
    char str[20];
    timeString.toCharArray(str,20);
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

    Serial.println("LE TIME:");
    Serial.println(tm.tm_year);
    Serial.println(tm.tm_mon);
    Serial.println(tm.tm_mday);
    Serial.println(tm.tm_hour);
    Serial.println(tm.tm_min);
    Serial.println(tm.tm_sec);
    return tm;
  }
};
