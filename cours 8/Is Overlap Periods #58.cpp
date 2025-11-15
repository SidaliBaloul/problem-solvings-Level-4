#pragma warning(disable : 4996)

#include <iostream>
#include <string>
#include <iomanip>


using namespace std;

enum eOptions {Before = -1,Equal = 0, After = 1};

struct sDate
{
	int year;
	int month;
	int day;
};
struct sPeriode
{
	sDate startdate;
	sDate enddate;
};


int ReadYear()
{
	int num;
	cout << "please enter the year : ";
	cin >> num;

	return num;
}
int ReadMonth()
{
	int num;
	do
	{
		cout << "please enter a month : ";
		cin >> num;

	} while (num < 1 || num > 12);

	return num;
}
int ReadDay()
{
	int day;
	cout << "enter day : ";
	cin >> day;

	return day;
}
int ReadVacationDays()
{
	int day;
	cout << "please enter vacation days : ";
	cin >> day;

	return day;
}
int AddDay()
{
	int day;
	cout << "how many days to add : ";
	cin >> day;

	return day;
}
sDate ReadFullData()
{
	sDate date;
	date.year = ReadYear();
	date.month = ReadMonth();
	date.day = ReadDay();

	return date;
}
sPeriode ReadPeriode()
{
	sPeriode periode;
	cout << "Enter start date : \n\n";
	periode.startdate = ReadFullData();
	cout << "Enter end date : \n\n";
	periode.enddate = ReadFullData();

	return periode;
}

bool IsLeapYear(int year)
{
	return ((year % 400 == 0) || ((year % 100 != 0) && (year % 4 == 0)));
}
int NumberOfDaysInMonth(int year, int month)
{

	short arr[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

	return ((month == 2) ? (IsLeapYear(year) ? 29 : 28) : arr[month - 1]);

}
int NumberOfDaysFromTheBeginingOfTheYear(int year, int month, int day)
{
	int totaldays = 0;

	for (int i = 1; i < month; i++)
	{
		totaldays += NumberOfDaysInMonth(year, i);
	}

	totaldays += day;

	return totaldays;
}
bool IsLastDayInMonth(sDate date)
{
	return (date.day == NumberOfDaysInMonth(date.year, date.month));
}
bool IsLastMonthInYear(sDate date)
{
	return (date.month == 12);

}
int DayOfWeekOrder(int month, int year, int day)
{
	int a, y, m, d;

	a = (14 - month) / 12;
	y = year - a;
	m = month + 12 * a - 2;
	d = (day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;

	return d;
}
int DayOfWeekOrder(sDate date)
{
	return DayOfWeekOrder(date.month, date.year, date.day);
}
string DayShortName(int dayorder)
{
	string arr[7] = { "sunday","monday","tuesday","wednesday","thursday","friday","saturday" };

	return arr[dayorder];
}
sDate IncreaseDateByOneDay(sDate date)
{
	if (IsLastDayInMonth(date))
	{
		date.day = 1;

		if (IsLastMonthInYear(date))
		{
			date.month = 1;
			date.year++;
		}
		else
			date.month++;
	}
	else
		date.day++;

	return date;
}

bool CheckLess(sDate date, sDate date2)
{
	return (date2.year > date.year) ? true : ((date2.year == date.year) ? (date2.month > date.month ? true : (date2.month == date.month ? date2.day > date.day : false)) : false);
}
bool CheckEqual(sDate date, sDate date2)
{
	return (date.year == date2.year ? ((date.month == date2.month) ? ((date.day == date2.day) ? true : false) : false) : false);
}
bool CheckAfter(sDate date, sDate date2)
{
	return ((!CheckEqual(date, date2)) && (!CheckLess(date, date2)));
}

void SwapDates(sDate& date, sDate& date2)
{
	sDate swap;
	swap.year = date.year;
	swap.month = date.month;
	swap.day = date.day;

	date.year = date2.year;
	date.month = date2.month;
	date.day = date2.day;

	date2.year = swap.year;
	date2.month = swap.month;
	date2.day = swap.day;

}
int GetDifferenceDays(sDate date1, sDate date2, bool day = false)
{
	int Days = 0;
	short sawp = 1;

	if (!CheckLess(date1, date2))
	{
		SwapDates(date1, date2);
		sawp = -1;
	}

	while (CheckLess(date1, date2))
	{
		date1 = IncreaseDateByOneDay(date1);
		Days++;
	}

	return (day) ? ++Days * sawp : Days * sawp;

}
bool IsEndOfWeek(sDate date)
{
	return (DayOfWeekOrder(date) == 6);
}
bool IsWeekEnd(sDate date)
{
	int day = DayOfWeekOrder(date);
	return (day == 5 || day == 6);
}
bool IsBusinessDay(sDate date)
{
	return (!IsWeekEnd(date));
}

int CalculateVacationDays(sDate date1, sDate date2)
{
	int Days = 0;

	while (CheckLess(date1, date2))
	{
		if (!IsWeekEnd(date1))
			Days++;

		date1 = IncreaseDateByOneDay(date1);
	}

	return Days;

}
sDate CalculateReturnDate(sDate date,int vac)
{
	
	int weekendcounter = 0;

	while (IsWeekEnd(date))
	{
		date = IncreaseDateByOneDay(date);
	}

	for (int i = 1;i <= vac + weekendcounter;i++)
	{
		if (IsWeekEnd(date))
			weekendcounter++;

		date = IncreaseDateByOneDay(date);
	}

	while (IsWeekEnd(date))
	{
		date = IncreaseDateByOneDay(date);
	}

	return date;
}

eOptions Compare(sDate date1, sDate date2)
{
	if (CheckLess(date1, date2))
		return eOptions::Before;

    if (CheckEqual(date1, date2))
		return eOptions::Equal;
	
		return eOptions::After;
}

bool IsOverlap(sPeriode periode1, sPeriode periode2)
{
	if (Compare(periode2.enddate, periode1.startdate) == eOptions::Before
		||
		Compare(periode2.startdate, periode1.enddate) == eOptions::After)
	return false;
	else
		return true;
 
	
}

int main()
{
	cout << "Enter periode 1 :\n";
	sPeriode periode1 = ReadPeriode();

	cout << endl;

	cout << "Enter periode 2 : \n";
	sPeriode periode2 = ReadPeriode();
	
	if (IsOverlap(periode1, periode2))
		cout << "\nYes, periods overlap ";
	else
		cout << "\nNo, periods are not overlap ";
