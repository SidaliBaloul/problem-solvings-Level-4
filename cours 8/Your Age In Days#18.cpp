#pragma warning(disable : 4996)

#include <iostream>
#include <string>
#include <iomanip>


using namespace std;

struct sDate
{
	int year;
	int month;
	int day;
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
	do
	{
		cout << "Please enter a day ? ";
		cin >> day;
	} while (day < 1 || day > 31);

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
bool IsLeapYear(int year)
{
	return ((year % 400 == 0) || ((year % 100 != 0) && (year % 4 == 0)));
}

int NumberOfDaysInMonth(int year, int month)
{

	short arr[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

	return ((month == 2) ? (IsLeapYear(year) ? 29 : 28) : arr[month - 1]);

}

int NumberOfDaysFromTheBeginingOfTheYear(int year,int month,int day)
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
sDate GetSystemDate()
{
	sDate date2;

	time_t t = time(0);
	tm* now = localtime(&t);

	date2.day = now->tm_mday;
	date2.month = now->tm_mon + 1;
	date2.year = now->tm_year + 1900;

	return date2;
}

int GetDifferenceDays(sDate date,sDate date2,bool lastday = false)
{
	int Days = 0;
	
	while (CheckLess(date, date2))
	{
			date = IncreaseDateByOneDay(date);
			Days++;
	}

	return (lastday) ? ++Days : Days;
}

int main()
{
	cout << "Please enter your date of birth : \n\n";
	sDate date = ReadFullData();
	sDate date2 = GetSystemDate();
	

	cout << "Your Age is : " << GetDifferenceDays(date, date2) << " Days \n";
