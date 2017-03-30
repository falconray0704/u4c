

#include <time.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>

#include <base/date.h>

bool valid_UDate(const UDate * uDate)
{
    return uDate != NULL && uDate->julianDayNumber > 0;
}

int getJulianDayNumber_UDate(int year, int month, int day)
{
    //(void) require_32_bit_integer_at_least; // no warning please
    int a = (14 - month) / 12;
    int y = year + 4800 - a;
    int m = month + 12 * a - 3;
    return day + (153*m + 2) / 5 + y*365 + y/4 - y/100 + y/400 - 32045;
}

YearMonthDay_UDate getYearMonthDayFromJulianDayNumber(int julianDayNumber)
{
    int a = julianDayNumber + 32044;
    int b = (4 * a + 3) / 146097;
    int c = a - ((b * 146097) / 4);
    int d = (4 * c + 3) / 1461;
    int e = c - ((1461 * d) / 4);
    int m = (5 * e + 2) / 153;
    YearMonthDay_UDate ymd;
    ymd.day = e - ((153 * m + 2) / 5) + 1;
    ymd.month = m + 3 - 12 * (m / 10);
    ymd.year = b * 100 + d - 4800 + (m / 10);
    return ymd;
}

YearMonthDay_UDate * yearMonthDayFromUDate(const UDate *uDate, YearMonthDay_UDate * outYearMonthDay_UDate )
{
    if(!valid_UDate(uDate) || outYearMonthDay_UDate == NULL)
        return NULL;

    (*outYearMonthDay_UDate) = getYearMonthDayFromJulianDayNumber(uDate->julianDayNumber);
    return outYearMonthDay_UDate;
}

///
/// Converts to yyyy-mm-dd format.
///
char * uDate2IsoString(const UDate *uDate, char outBuf[Size32B] )
{
    YearMonthDay_UDate ymd;

    if(!valid_UDate(uDate) || outBuf == NULL)
        return NULL;

    if(yearMonthDayFromUDate(uDate, &ymd) == NULL)
        return NULL;

    snprintf(outBuf, Size32B, "%4d-%02d-%02d", ymd.year, ymd.month, ymd.day);
    return outBuf;
}

// [0, 1, ..., 6] => [Sunday, Monday, ..., Saturday ]
int weekDay_UDate(const UDate *uDate)
{
    if(valid_UDate(uDate))
        return (uDate->julianDayNumber + 1) % kDaysPerWeek_UDate;
    else
        return -1;
}

int year_UDate(const UDate *uDate)
{
    if(valid_UDate(uDate))
        return getYearMonthDayFromJulianDayNumber(uDate->julianDayNumber).year;
    else
        return -1;
}

int month_UDate(const UDate *uDate)
{
    if(valid_UDate(uDate))
        return getYearMonthDayFromJulianDayNumber(uDate->julianDayNumber).month;
    else
        return -1;
}

int day_UDate(const UDate *uDate)
{
    if(valid_UDate(uDate))
        return getYearMonthDayFromJulianDayNumber(uDate->julianDayNumber).day;
    else
        return -1;
}

int isLeapYear_UDate(int year)
{
    if (year % 400 == 0)
        return 1;
    else if (year % 100 == 0)
        return 0;
    else if (year % 4 == 0)
        return 1;
    else
        return 0;
}

int daysOfMonth_UDate(int year, int month)
{
    static int days[2][kMonthsOfYear_UDate + 1] =
    {
        { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
        { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
    };
    return days[isLeapYear_UDate(year)][month];
}




