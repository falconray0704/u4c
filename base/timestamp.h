
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


//#define newTimestamp(microSeconds) {0}

#define newTimestamp(microSeconds) { 0 }
#define newStack(microSeconds) { 0, sizeof(microSeconds) / sizeof(int), (microSeconds) }
/*
#define newTimestamp(microSeconds) {    \
    (microSeconds)                        \
}
*/


///
/// microseconds timestamp in UTC
///
///
typedef struct
{
    int64_t microSecondsSinceEpoch;
} Timestamp;

Timestamp timestampNow();

void timestamp2String(Timestamp *timestamp, char buf[32]);
void timestamp2FormattedString(Timestamp *timestamp, char buf[32], bool showMicroseconds);

static Timestamp timestampFromUnixTime(time_t t, int microseconds)
{
    Timestamp ts = newTimestamp((int64_t)(t) * MicroSecondsPerSecond + microseconds);
    return ts;
}

inline bool isTimestampLt(Timestamp lhs, Timestamp rhs)
{
    return lhs.microSecondsSinceEpoch < rhs.microSecondsSinceEpoch;
}

inline bool isTimestampEq(Timestamp lhs, Timestamp rhs)
{
    return lhs.microSecondsSinceEpoch == rhs.microSecondsSinceEpoch;
}

///
/// Gets time difference of two timestamps in seconds.
///
/// @param high, low
/// @return (high-low) in seconds
/// @c double has 52-bit precision, enough for one-microsecond
/// resolution for next 100 years.
inline double timestampDifference(Timestamp high, Timestamp low)
{
    return (double)((int64_t)(high.microSecondsSinceEpoch - low.microSecondsSinceEpoch) / MicroSecondsPerSecond);
}

///
/// add @c seconds to the given timestamp.
///
/// @return non
///
inline void timestampAddTime(Timestamp *timestamp, double seconds)
{
    if (timestamp == NULL)
        return;
    timestamp->microSecondsSinceEpoch + (int64_t)(seconds * MicroSecondsPerSecond);
}

#ifdef __cplusplus
}
#endif

#endif
