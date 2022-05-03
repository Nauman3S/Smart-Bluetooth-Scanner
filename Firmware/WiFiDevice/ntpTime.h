#include "time.h"

const char *ntpServer = "pool.ntp.org";

// struct tm timeinfo;
// struct tm

// {
// int    tm_sec;   //   Seconds [0,60].
// int    tm_min;   //   Minutes [0,59].
// int    tm_hour;  //   Hour [0,23].
// int    tm_mday;  //   Day of month [1,31].
// int    tm_mon;   //   Month of year [0,11].
// int    tm_year;  //   Years since 1900.
// int    tm_wday;  //   Day of week [0,6] (Sunday =0).
// int    tm_yday;  //   Day of year [0,365].
// int    tm_isdst; //   Daylight Savings flag.
// }
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;

void setupNTP()
{
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

void printLocalTime()
{
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        Serial.println("Failed to obtain time");
        return;
    }
    // Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

String getTimestamp()
{
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        Serial.println("Failed to obtain time");
        return String("0");
    }

    // printLocalTime();
    // char ts_char[50] = {0};
    // strftime(ts_char,sizeof(ts_char),"%H:%M:%S %d-%B-%Y", &timeinfo);
    Serial.println(&timeinfo, "NTP=%H:%M:%S %d-%B-%Y*");
    // strftime(ts_char,sizeof(ts_char),"%A, %B %d %Y %H:%M:%S", &tm);

    // Serial.println("strftime output is " + String(ts_char));
    int second = timeinfo.tm_sec;
    int minute = timeinfo.tm_min;
    int hour = timeinfo.tm_hour;
    int day = timeinfo.tm_mday;
    int month = timeinfo.tm_mon + 1;
    int year = timeinfo.tm_year + 1900;
    String ts = "";
    // ts = String(hour) + String(":") + String(minute) + String(":") + String(second) + String(" ") + String(day) + String("-") + String(month) + String("-") + String(year);
    return ts;
}