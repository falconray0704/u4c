
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>
#include <base/timestamp.h>


///
/// Get UTC time in micro seconds.
///
/// @param
///
/// @return UTime
///
UTime now_UTime()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    UTime ts = newUTime(tv.tv_sec * MicroSecondsPerSecond + tv.tv_usec);
    return ts;
}

///
/// Get UTC time in seconds.
///
/// @param
///
/// @return time_t
///
time_t nowSec_UTime()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec;
}


///
/// Get UTC time after N micro seconds in micro seconds.
///
/// @param t, microseconds
///
/// @return UTime
///
UTime afterUnixTime_UTime(time_t t, int microseconds)
{
    UTime ts = newUTime((int64_t)(t) * MicroSecondsPerSecond + microseconds);
    return ts;
}

///
/// Parse UTime into string.
///
/// @param uTime, outBuf
///
/// @return
///
char * toString_UTime(UTime const * const uTime, char outBuf[Size32B])
{
    if( uTime == NULL || outBuf == NULL )
        return NULL;

    memset(outBuf,Size32B,0x00);
    int64_t seconds = uTime->microSec / MicroSecondsPerSecond;
    int64_t microseconds = uTime->microSec % MicroSecondsPerSecond;
    snprintf(outBuf, Size32B - 1, "%" PRId64 ".%06" PRId64 "", seconds, microseconds);

    return outBuf;
}

///
/// Parse UTime into formated string.
///
/// @param uTime, outBuf
///
/// @return
///
char * toFormattedString_UTime(UTime const * const uTime, char outBuf[Size32B], bool const showMicroseconds)
{
    if( uTime == NULL || outBuf == NULL )
        return NULL;

    time_t seconds = (time_t)(uTime->microSec / MicroSecondsPerSecond);
    struct tm tm_time;
    tm_time.tm_isdst = -1;

    memset(outBuf, Size32B, 0x00);
    gmtime_r(&seconds, &tm_time);
    //tm_time = *gmtime(&seconds);

    if (showMicroseconds)
    {
        int microseconds = (int)(uTime->microSec % MicroSecondsPerSecond);
        snprintf(outBuf, Size32B, "%4d%02d%02d %02d:%02d:%02d.%06d", 
                tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
                tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec,
                microseconds);
    }
    else
    {
        snprintf(outBuf, Size32B, "%4d%02d%02d %02d:%02d:%02d", 
                tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday, 
                tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec); 
    }

    return outBuf;
}


