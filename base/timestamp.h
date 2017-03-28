
#ifndef U4C_BASE_TIMESTAMP_H
#define U4C_BASE_TIMESTAMP_H

#include <time.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>


#ifdef __cplusplus
extern "C" {
#endif

#define Size32B 32
#define MicroSecondsPerSecond 1000000
#define newUTime(microSec) { microSec }

///
/// UTC microseconds timestamp in epoch
///
///
typedef struct
{
    int64_t microSec;
} UTime;

///
/// Get UTC time in micro seconds.
///
/// @param
///
/// @return UTime
///
UTime uTimeNow();

///
/// Get UTC time after N micro seconds in micro seconds.
///
/// @param t, microseconds
///
/// @return UTime
///
UTime uTimeAfterUnixTime(time_t t, int microseconds);

///
/// Parse UTime into string.
///
/// @param uTime, outBuf
///
/// @return
///
void uTime2String(UTime *uTime, char outBuf[Size32B]);

///
/// Parse UTime into formated string.
///
/// @param uTime, outBuf
///
/// @return
///
void uTime2FormattedString(UTime *uTime, char outBuf[Size32B], bool showMicroseconds);

inline bool isUTimeLt(UTime lUTime, UTime rUTime)
{
    return lUTime.microSec < rUTime.microSec;
}

inline bool isUTimeEq(UTime lhs, UTime rhs)
{
    return lhs.microSec == rhs.microSec;
}

///
/// Gets time difference of two uTimes in seconds.
///
/// @param high, low
/// @return (t1 - t2) in seconds
/// @c double has 52-bit precision, enough for one-microsecond
/// resolution for next 100 years.
inline double uTimeDiff(UTime t1, UTime t2)
{
    return ((double)(t1.microSec - t2.microSec)) / MicroSecondsPerSecond;
}

///
/// add @c seconds to the given uTime.
///
/// @return non
///
inline void uTimeAddTime(UTime *uTime, double seconds)
{
    if (uTime == NULL)
        return;
    uTime->microSec += (int64_t)(seconds * MicroSecondsPerSecond);
}

#ifdef __cplusplus
}
#endif

#endif
