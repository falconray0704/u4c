#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <gtest/gtest.h>
#include <base/date.h>

TEST(Base_UDate, isLeapYear_UDate)
{
    /*当我们遇到这个问题时，大家都知道该怎么计算，那就是所谓的：四年一闰，百年不闰，四百年再闰。
    根据这个写出的程序的核心算法就是：
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

/*
void passByConstReference(const Date& x)
{
  printf("%s\n", x.toIsoString().c_str());
}

void passByValue(Date x)
{
  printf("%s\n", x.toIsoString().c_str());
}

int main()
{
  time_t now = time(NULL);
  struct tm t1 = *gmtime(&now);
  struct tm t2 = *localtime(&now);
  Date someDay(2008, 9, 10);
  printf("%s\n", someDay.toIsoString().c_str());
  passByValue(someDay);
  passByConstReference(someDay);
  Date todayUtc(t1);
  printf("%s\n", todayUtc.toIsoString().c_str());
  Date todayLocal(t2);
  printf("%s\n", todayLocal.toIsoString().c_str());

  int julianDayNumber = 2415021;
  int weekDay = 1; // Monday

  for (int year = 1900; year < 2500; ++year)
  {
    assert(Date(year, 3, 1).julianDayNumber() - Date(year, 2, 29).julianDayNumber()
           == isLeapYear(year));
    for (int month = 1; month <= kMonthsOfYear; ++month)
    {
      for (int day = 1; day <= daysOfMonth(year, month); ++day)
      {
        Date d(year, month, day);
        // printf("%s %d\n", d.toString().c_str(), d.weekDay());
        assert(year == d.year());
        assert(month == d.month());
        assert(day == d.day());
        assert(weekDay == d.weekDay());
        assert(julianDayNumber == d.julianDayNumber());

        Date d2(julianDayNumber);
        assert(year == d2.year());
        assert(month == d2.month());
        assert(day == d2.day());
        assert(weekDay == d2.weekDay());
        assert(julianDayNumber == d2.julianDayNumber());

        ++julianDayNumber;
        weekDay = (weekDay+1) % 7;
      }
    }
  }
  printf("All passed.\n");
}
*/
