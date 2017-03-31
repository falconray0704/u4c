#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <gtest/gtest.h>
#include <base/date.h>

TEST(Base_UDate, isLeapYear_UDate)
{
    /*
        if（(n%4 == 0 && n%100 != 0) || n %400 == 0）{}
    */

    for (int year = 1900; year < 2500; ++year)
    {
        int isLeapExpect = 0;
        if(( year % 4 == 0 && year % 100 != 0) || year %400 == 0)
        {
            isLeapExpect = 1;
        }

        EXPECT_EQ(isLeapExpect, isLeapYear_UDate(year));
    }
}

int daysEpochDiffSum(int y,int m,int d)
{
    unsigned char x[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    int i,s=0;
    for(i=1;i<y;i++)
        if((i%4 == 0 && i%100 != 0) || i%400 == 0)
            s+=366;//闰年
        else
            s+=365;//平年

    if((y%4 == 0 && y%100 != 0) || y%400 == 0)
        x[2]=29;

    for(i=1;i<m;i++)
        s+=x[i];//整月的天数

    s+=d;//日的天数

    return s;//返回总天数,相对公元1年
}

TEST(Base_UDate, daysOfMonth_UDate)
{
    for (int year = 1900; year < 2500; ++year)
    {
        for (int month = 1; month <= kMonthsOfYear_UDate; ++month)
        {
            int ds1 = daysEpochDiffSum(year,month,1);
            int ds2 = daysEpochDiffSum(month + 1 >= 13 ? year + 1 : year, month + 1 >= 13 ? 1 : month + 1, 1);
            int daysExpected = ds2 - ds1;

            EXPECT_EQ(daysExpected , daysOfMonth_UDate(year,month));
        }
    }
}

TEST(Base_UDate, newUDate)
{

    int julianDayNumber = 2415021;

    for (int year = 1900; year < 2500; ++year)
    {
        for (int month = 1; month <= kMonthsOfYear_UDate; ++month)
        {
            for (int day = 1; day <= daysOfMonth_UDate(year, month); ++day)
            {
                UDate d = newUDate(julianDayNumber);
                EXPECT_EQ(julianDayNumber, d.julianDayNumber);
                ++julianDayNumber;
            }
        }
    }

}

TEST(Base_UDate, GetJulianDayNumber_UDate)
{

    int julianDayNumber = 2415021;

    for (int year = 1900; year < 2500; ++year)
    {
        for (int month = 1; month <= kMonthsOfYear_UDate; ++month)
        {
            for (int day = 1; day <= daysOfMonth_UDate(year, month); ++day)
            {
                EXPECT_EQ(julianDayNumber, GetJulianDayNumber_UDate(year,month,day));
                ++julianDayNumber;
            }
        }
    }

}

TEST(Base_UDate, newUDateFrom_YearMonthDay)
{

    int julianDayNumber = 2415021;

    for (int year = 1900; year < 2500; ++year)
    {
        for (int month = 1; month <= kMonthsOfYear_UDate; ++month)
        {
            for (int day = 1; day <= daysOfMonth_UDate(year, month); ++day)
            {
                UDate d = newUDateFrom_YearMonthDay(year,month,day);
                EXPECT_EQ(julianDayNumber, d.julianDayNumber);
                ++julianDayNumber;
            }
        }
    }

}

TEST(Base_UDate, valid_UDate)
{
    EXPECT_FALSE(valid_UDate(NULL));

    UDate d1 = newUDate(-1);
    EXPECT_FALSE(valid_UDate(&d1));

    UDate d2 = newUDate(0);
    EXPECT_FALSE(valid_UDate(&d2));

    UDate d3 = newUDate(2017);
    EXPECT_TRUE(valid_UDate(&d3));
}

TEST(Base_UDate, getJulianDayNumber_UDate)
{

    int julianDayNumber = 2415021;

    for (int year = 1900; year < 2500; ++year)
    {
        for (int month = 1; month <= kMonthsOfYear_UDate; ++month)
        {
            for (int day = 1; day <= daysOfMonth_UDate(year, month); ++day)
            {
                EXPECT_EQ(julianDayNumber, getJulianDayNumber_UDate(year,month,day));
                ++julianDayNumber;
            }
        }
    }

}

TEST(Base_UDate, getYearMonthDayFromJulianDayNumber)
{

    int julianDayNumber = 2415021;

    for (int year = 1900; year < 2500; ++year)
    {
        for (int month = 1; month <= kMonthsOfYear_UDate; ++month)
        {
            for (int day = 1; day <= daysOfMonth_UDate(year, month); ++day)
            {
                YearMonthDay_UDate ymd = getYearMonthDayFromJulianDayNumber(julianDayNumber);
                EXPECT_EQ(year, ymd.year);
                EXPECT_EQ(month, ymd.month);
                EXPECT_EQ(day, ymd.day);

                ++julianDayNumber;
            }
        }
    }

}

TEST(Base_UDate, yearMonthDayFromUDate_null_args)
{

    UDate d;
    YearMonthDay_UDate ymd;

    EXPECT_EQ(static_cast<YearMonthDay_UDate *>(NULL),yearMonthDayFromUDate(NULL,&ymd));
    EXPECT_EQ(static_cast<YearMonthDay_UDate *>(NULL),yearMonthDayFromUDate(&d, NULL));
    EXPECT_EQ(static_cast<YearMonthDay_UDate *>(NULL),yearMonthDayFromUDate(NULL, NULL));

}

TEST(Base_UDate, yearMonthDayFromUDate)
{

    int julianDayNumber = 2415021;

    for (int year = 1900; year < 2500; ++year)
    {
        for (int month = 1; month <= kMonthsOfYear_UDate; ++month)
        {
            for (int day = 1; day <= daysOfMonth_UDate(year, month); ++day)
            {
                UDate d = newUDateFrom_YearMonthDay(year,month,day);
                YearMonthDay_UDate ymd = {0,0,0};

                EXPECT_EQ(julianDayNumber, d.julianDayNumber);

                EXPECT_NE(static_cast<YearMonthDay_UDate *>(NULL),yearMonthDayFromUDate(&d,&ymd));
                EXPECT_EQ(year, ymd.year);
                EXPECT_EQ(month, ymd.month);
                EXPECT_EQ(day, ymd.day);

                ++julianDayNumber;
            }
        }
    }

}

TEST(Base_UDate, toIsoString_UDate )
{

    int julianDayNumber = 2415021;

    for (int year = 1900; year < 2500; ++year)
    {
        for (int month = 1; month <= kMonthsOfYear_UDate; ++month)
        {
            for (int day = 1; day <= daysOfMonth_UDate(year, month); ++day)
            {
                char outBuf[Size32B] = {0};
                char expectedBuf[Size32B] = {0};

                UDate d = newUDateFrom_YearMonthDay(year,month,day);
                EXPECT_EQ(julianDayNumber, d.julianDayNumber);

                sprintf(expectedBuf,"%4d-%02d-%02d",year,month,day);
                EXPECT_NE(static_cast<char*>(NULL),toIsoString_UDate(&d,outBuf));
                EXPECT_EQ(0,strncmp(outBuf, expectedBuf, strlen(expectedBuf)));

                ++julianDayNumber;
            }
        }
    }

}

TEST(Base_UDate, day_UDate_month_UDate_year_UDate_weekDay_UDate)
{

    int julianDayNumber = 2415021;
    int weekDay = 1; // Monday

    for (int year = 1900; year < 2500; ++year)
    {
        for (int month = 1; month <= kMonthsOfYear_UDate; ++month)
        {
            for (int day = 1; day <= daysOfMonth_UDate(year, month); ++day)
            {
                UDate d = newUDate(julianDayNumber);

                EXPECT_EQ(year, year_UDate(&d) );
                EXPECT_EQ(month, month_UDate(&d) );
                EXPECT_EQ(day, day_UDate(&d) );
                EXPECT_EQ(weekDay, weekDay_UDate(&d) );

                weekDay = (weekDay+1) % 7;
                ++julianDayNumber;
            }
        }
    }

}

TEST(Base_UDate, isLt_UDate)
{
    UDate d1 = newUDateFrom_YearMonthDay(2016,02,01);
    UDate d2 = newUDateFrom_YearMonthDay(2017,01,03);
    UDate d3 = newUDateFrom_YearMonthDay(2017,01,03);

    EXPECT_TRUE(isLt_UDate(&d1,&d2));
    EXPECT_FALSE(isLt_UDate(&d2,&d1));
    EXPECT_FALSE(isLt_UDate(&d2,&d3));

    EXPECT_FALSE(isLt_UDate(NULL, &d1));
    EXPECT_FALSE(isLt_UDate(&d2, NULL));
    EXPECT_FALSE(isLt_UDate(NULL, NULL));
}

TEST(Base_UDate, isEq_UDate)
{
    UDate d1 = newUDateFrom_YearMonthDay(2016,02,01);
    UDate d2 = newUDateFrom_YearMonthDay(2017,01,03);
    UDate d3 = newUDateFrom_YearMonthDay(2017,01,03);

    EXPECT_FALSE(isEq_UDate(&d2,&d1));
    EXPECT_FALSE(isEq_UDate(&d1,&d2));

    EXPECT_TRUE(isEq_UDate(&d2,&d3));

    EXPECT_FALSE(isEq_UDate(NULL, &d1));
    EXPECT_FALSE(isEq_UDate(&d2, NULL));
    EXPECT_FALSE(isEq_UDate(NULL, NULL));
}

