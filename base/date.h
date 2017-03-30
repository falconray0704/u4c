
#ifndef U4C_BASE_DATE_H
#define U4C_BASE_DATE_H


#include <time.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>

#include <base/u4cGlobalDef.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct
{
    int julianDayNumber;
} UDate;

typedef struct
{
    int year; // [1900..2500]
    int month;  // [1..12]
    int day;  // [1..31]
}YearMonthDay_UDate;


#define a_UDate ((14 - month) / 12)
#define y_UDate (year + 4800 - a_UDate)
#define m_UDate (month + 12 * a_UDate - 3)
#define GetJulianDayNumber_UDate(year,month,day) (day + (153 * m_UDate + 2) / 5 + y_UDate * 365 + y_UDate / 4 - y_UDate / 100 + y_UDate / 400 - 32045)
#undef a_UDate
#undef y_UDate
#undef m_UDate
/*
#define GetJulianDayNumber_UDate(year,month,day) (day + (153 * (month + 12 * ((14 - month) / 12) - 3) + 2) / 5 + (year + 4800 - ((14 - month) / 12)) * 365 + (year + 4800 - ((14 - month) / 12)) / 4 - (year + 4800 - ((14 - month) / 12)) / 100 + (year + 4800 - ((14 - month) / 12)) / 400 - 32045)

*/
#define kDaysPerWeek_UDate 7
#define kJulianDayOf1970_01_01_UDate (GetJulianDayNumber_UDate(1970,1,1))
#define newUDateFrom_YearMonthDay(year,month,day) { GetJulianDayNumber_UDate(year,month,day) }
#define newUDateFrom_tm(tm) newUDateFrom_YearMonthDay(tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday)


#define newUDate(julianDayNumber) { julianDayNumber }

bool valid_UDate(const UDate * uDate);

int getJulianDayNumber_UDate(int year, int month, int day);
YearMonthDay_UDate getYearMonthDayFromJulianDayNumber(int julianDayNumber);
YearMonthDay_UDate * yearMonthDayFromUDate(const UDate *uDate , YearMonthDay_UDate * outYearMonthDay_UDate );
///
/// Converts to yyyy-mm-dd format.
///
char * uDate2IsoString(const UDate *uDate, char outBuf[Size32B] );

// [0, 1, ..., 6] => [Sunday, Monday, ..., Saturday ]
int weekDay_UDate(const UDate *uDate);
int year_UDate(const UDate *uDate);
int month_UDate(const UDate *uDate);
int day_UDate(const UDate *uDate);

inline bool isLt_UDate(const UDate *l, const UDate *r)
{
  return l->julianDayNumber < r->julianDayNumber;
}

inline bool isEq_UDate(const UDate *l, const UDate *r)
{
  return l->julianDayNumber == r->julianDayNumber;
}

#ifdef __cplusplus
}
#endif

#endif
