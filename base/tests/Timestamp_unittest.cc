#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <base/timestamp.h>
#include <gtest/gtest.h>

TEST(Base_Timestamp, now_UTime)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);

    UTime now = now_UTime();

    EXPECT_EQ(tv.tv_sec, static_cast<time_t>(now.microSec / MicroSecondsPerSecond));

}

TEST(Base_Timestamp, nowSec_UTime)
{
    struct timeval tv;

    UTime now = now_UTime();
    gettimeofday(&tv, NULL);

    EXPECT_LE(0,tv.tv_sec - static_cast<time_t>(now.microSec / MicroSecondsPerSecond));
    EXPECT_GE(1,tv.tv_sec - static_cast<time_t>(now.microSec / MicroSecondsPerSecond));

}

TEST(Base_Timestamp, afterUnixTime_UTime )
{
    struct timeval tv;

    gettimeofday(&tv, NULL);

    UTime after = afterUnixTime_UTime(tv.tv_sec , 123456);

    EXPECT_EQ(1, after.microSec / (static_cast<int64_t>(tv.tv_sec) * MicroSecondsPerSecond) );
    EXPECT_EQ(123456, after.microSec % (static_cast<int64_t>(tv.tv_sec) * MicroSecondsPerSecond) );

}

TEST(Base_Timestamp, toString_UTime)
{
    char buf[Size32B];
    time_t ret;
    struct tm tm_time;
    char buffer[80];

    memset(&tm_time,0x00,sizeof(tm_time));
    //Wed Jul 4 00:00:01 2001
    tm_time.tm_zone = "UTC";
    tm_time.tm_year = 2001 - 1900;
    tm_time.tm_mon = 7 - 1;
    tm_time.tm_mday = 4;
    tm_time.tm_hour = 0;
    tm_time.tm_min = 0;
    tm_time.tm_sec = 1;
    tm_time.tm_isdst = -1;

    ret = static_cast<time_t>(mktime(&tm_time));

    ASSERT_NE(-1,ret);
    sprintf(buffer,"%ld",ret);
    ASSERT_LT(0,static_cast<int>(strlen(buffer)));

    UTime now = afterUnixTime_UTime(ret,0);
    toString_UTime(&now, buf);
    ASSERT_LT(0,static_cast<int>(strlen(buf)));

    ASSERT_EQ(strlen(buffer),strlen(buf) - 7);
    ASSERT_EQ(0,strncmp(buffer,buf,strlen(buffer)));

    printf("time_t:%s uTime:%s\n", buffer, buf);
}

TEST(Base_Timestamp, toFormattedString_UTime_DoNotShowMicroseconds)
{
    char bufExp[Size32B] = {0};
    char buf[Size32B] = {0};
    struct tm tm_time;

    UTime now;
    struct timeval tv;

    gettimeofday(&tv, NULL);
    now = now_UTime();

    // expected string
    memset(bufExp,0x00,sizeof(bufExp));
    gmtime_r(&tv.tv_sec, &tm_time);
/*
    memset(&tm_time,0x00,sizeof(tm_time));
    //Wed Jul 4 00:00:01 2001
    tm_time.tm_zone = "UTC";
    tm_time.tm_year = 2001 - 1900;
    tm_time.tm_mon = 7 - 1;
    tm_time.tm_mday = 4;
    tm_time.tm_hour = 0;
    tm_time.tm_min = 0;
    tm_time.tm_sec = 1;
    tm_time.tm_isdst = -1;
    strftime(bufExp, sizeof(bufExp), "%c", &tm_time );
    */
    snprintf(bufExp, Size32B, "%4d%02d%02d %02d:%02d:%02d", 
                tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday, 
                tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec); 
    printf("=== Expected strlen:%d - string:%s\n",static_cast<int>(strlen(bufExp)),bufExp);
    ASSERT_LT(0,static_cast<int>(strlen(bufExp)));

    toFormattedString_UTime(&now, buf, false);
    printf("--- uTime strlen:%d - string:%s\n", static_cast<int>(strlen(buf)), buf);
    ASSERT_LT(0,static_cast<int>(strlen(buf)));

    ASSERT_EQ(0,strncmp(bufExp,buf,strlen(bufExp)));

}

TEST(Base_Timestamp, toFormattedString_UTime)
{
    char bufExp[Size32B] = {0};
    char buf[Size32B] = {0};
    struct tm tm_time;

    UTime now;
    struct timeval tv;

    gettimeofday(&tv, NULL);
    now = now_UTime();

    // expected string
    memset(bufExp,0x00,sizeof(bufExp));
    gmtime_r(&tv.tv_sec, &tm_time);
/*
    memset(&tm_time,0x00,sizeof(tm_time));
    //Wed Jul 4 00:00:01 2001
    tm_time.tm_zone = "UTC";
    tm_time.tm_year = 2001 - 1900;
    tm_time.tm_mon = 7 - 1;
    tm_time.tm_mday = 4;
    tm_time.tm_hour = 0;
    tm_time.tm_min = 0;
    tm_time.tm_sec = 1;
    tm_time.tm_isdst = -1;
    strftime(bufExp, sizeof(bufExp), "%c", &tm_time );
    */
    snprintf(bufExp, Size32B, "%4d%02d%02d %02d:%02d:%02d.%06d", 
            tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
            tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec,
            static_cast<int>(tv.tv_usec));
    printf("=== Expected strlen:%d - string:%s\n",static_cast<int>(strlen(bufExp)),bufExp);
    ASSERT_LT(0,static_cast<int>(strlen(bufExp)));

    toFormattedString_UTime(&now, buf, true);
    printf("--- uTime strlen:%d - string:%s\n", static_cast<int>(strlen(buf)), buf);
    ASSERT_LT(0,static_cast<int>(strlen(buf)));

    ASSERT_EQ(0,strncmp(bufExp,buf,strlen(bufExp) - 2));

}

TEST(Base_Timestamp, isLt_UTime)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);

    UTime now = newUTime( tv.tv_sec * MicroSecondsPerSecond );
    UTime now2 = newUTime( tv.tv_sec * MicroSecondsPerSecond );
    UTime after = afterUnixTime_UTime(tv.tv_sec , 1);

    EXPECT_TRUE(isLt_UTime(now, after) );
    EXPECT_FALSE(isLt_UTime(now, now2) );
    EXPECT_FALSE(isLt_UTime(after, now) );

}

TEST(Base_Timestamp, isEq_UTime )
{
    struct timeval tv;

    gettimeofday(&tv, NULL);

    UTime now = newUTime( tv.tv_sec * MicroSecondsPerSecond );
    UTime now2 = newUTime( tv.tv_sec * MicroSecondsPerSecond );
    UTime after = afterUnixTime_UTime(tv.tv_sec , 1);

    EXPECT_TRUE(isEq_UTime(now, now2) );
    EXPECT_FALSE(isEq_UTime(now, after) );
    EXPECT_FALSE(isEq_UTime(after, now) );

}

TEST(Base_Timestamp, diffTime_UTime)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);

    UTime now = now_UTime(); 
    UTime after = now;
    after.microSec += 123456;

    EXPECT_EQ(0.123456, diffTime_UTime(after, now));
    EXPECT_EQ(-0.123456, diffTime_UTime(now, after));

}

TEST(Base_Timestamp, addTime_UTime)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);

    UTime now = newUTime( tv.tv_sec * MicroSecondsPerSecond );
    UTime added = now;

    addTime_UTime(&added, 0.123456);
    EXPECT_EQ(123456, added.microSec - now.microSec);

    added = now;
    addTime_UTime(&added, -0.123456);
    EXPECT_EQ(-123456, added.microSec - now.microSec);

    added = now;
    addTime_UTime(&added, 0);
    EXPECT_EQ(added.microSec, now.microSec);
}

