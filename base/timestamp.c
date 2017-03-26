
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>
//#include <u4c/base/timestamp.h>
#include "timestamp.h"

Timestamp timestampNow()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    Timestamp ts = newTimestamp(tv.tv_sec * MicroSecondsPerSecond + tv.tv_usec);

    return ts;
}

void timestamp2String(Timestamp *timestamp, char buf[Size32B]) 
{
    memset(buf,Size32B,0x00);
    int64_t seconds = timestamp->microSecondsSinceEpoch / MicroSecondsPerSecond;
    int64_t microseconds = timestamp->microSecondsSinceEpoch % MicroSecondsPerSecond;
    snprintf(buf, Size32B - 1, "%" PRId64 ".%06" PRId64 "", seconds, microseconds);
}

void timestamp2FormattedString(Timestamp *timestamp, char buf[Size32B], bool showMicroseconds) 
{
    time_t seconds = (time_t)(timestamp->microSecondsSinceEpoch / MicroSecondsPerSecond);
    struct tm tm_time;

    memset(buf, Size32B, 0x00);
    gmtime_r(&seconds, &tm_time);

    if (showMicroseconds)
    {
        int microseconds = (int)(timestamp->microSecondsSinceEpoch % MicroSecondsPerSecond);
        snprintf(buf, Size32B, "%4d%02d%02d %02d:%02d:%02d.%06d", 
                tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
                tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec,
                microseconds);
    }
    else
    {
        snprintf(buf, Size32B, "%4d%02d%02d %02d:%02d:%02d", 
                tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday, 
                tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec); 
    }
}


