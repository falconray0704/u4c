
#ifndef U4C_BASE_TIMESTAMP_H
#define U4C_BASE_TIMESTAMP_H

#include <time.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>

#include <base/u4cGlobalDef.h>


#ifdef __cplusplus
extern "C" {
#endif

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
UTime now_UTime();

///
/// Get UTC time in seconds.
///
/// @param
///
/// @return time_t
///
time_t nowSec_UTime();

///
/// Get UTC time after N micro seconds in micro seconds.
///
/// @param t, microseconds
///
/// @return UTime
///
UTime afterUnixTime_UTime(time_t t, int microseconds);

///
/// Parse UTime into string.
///
/// @param uTime, outBuf
///
/// @return
///
char * toString_UTime(UTime const * const uTime, char outBuf[Size32B]);

///
/// Parse UTime into formated string.
///
/// @param uTime, outBuf
///
/// @return
///
char * toFormattedString_UTime(UTime const * const uTime, char outBuf[Size32B], bool const showMicroseconds);

inline bool isLt_UTime(UTime lUTime, UTime rUTime)
{
    return lUTime.microSec < rUTime.microSec;
}

inline bool isEq_UTime(UTime lhs, UTime rhs)
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
inline double diffTime_UTime(UTime t1, UTime t2)
{
    return ((double)(t1.microSec - t2.microSec)) / MicroSecondsPerSecond;
}

///
/// add @c seconds to the given uTime.
///
/// @return non
///
inline UTime * addTime_UTime(UTime * const uTime, double seconds)
{
    if (uTime == NULL)
        return NULL;

    uTime->microSec += (int64_t)(seconds * MicroSecondsPerSecond);

    return uTime;
}

#ifdef __cplusplus
}
#endif

#endif
