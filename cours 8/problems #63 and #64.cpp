warning(disable : 4996)

#include <iostream>
#include <string>
#include <iomanip>
#include<vector>


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

int PeriodeLengthInDays(sPeriode periode1, bool day = false)
{
	int Days = 0;


	while (Compare(periode1.startdate, periode1.enddate) == eOptions::Before)
	{
		periode1.startdate = IncreaseDateByOneDay(periode1.startdate);
		Days++;
	}

	return (day) ? ++Days : Days;

}

int PeriodeLength(sPeriode periode1,sPeriode periode2, bool day = false)
{
	return GetDifferenceDays(periode2.startdate, periode1.enddate, day);
}
bool IsWithinPeriode(sPeriode periode1,sDate date1)
{
	return !(Compare(date1, periode1.startdate) == eOptions::Before || Compare(date1, periode1.enddate) == eOptions::After);
		
}

int CountOverlapsDays(sPeriode periode1, sPeriode periode2)
{
	int periode1length = PeriodeLength(periode1, periode1, true);
	int periode2length = PeriodeLength(periode2, periode2, true);
	int days = 0;

	if (!IsOverlap(periode1, periode2))
		return 0;

	if (periode1length < periode2length)
	{
		while (CheckLess(periode1.startdate, periode1.enddate))
		{
			if (IsWithinPeriode(periode2, periode1.startdate))
				days++;

			periode1.startdate = IncreaseDateByOneDay(periode1.startdate);
		}
	}
	else
	{
		while (CheckLess(periode2.startdate, periode2.enddate))
		{
			if (IsWithinPeriode(periode1, periode2.startdate))
				days++;

			periode2.startdate = IncreaseDateByOneDay(periode2.startdate);
		}
	}
	

	return days;
}

bool IsValideDate(sDate date)
{
	if (date.month > 12 || date.month < 1)
		return false;

	if (date.day > NumberOfDaysInMonth(date.year, date.month))
			return false;

	return true;
}
bool IsValide(sDate date)
{

	if (date.day < 1 || date.day > 31)
		return false;

	if (date.month < 1 || date.month > 12)
		return false;

	if (date.month == 2)
	{
		if (IsLeapYear(date.year))
		{
			if (date.day > 29)
				return false;
			else
			{
				if (date.day > 28)
					return false;
			}
		}
	}

	short Daysinmonth = NumberOfDaysInMonth(date.year, date.month);

	if (date.day > Daysinmonth)
		return false;

	return true;
}

string ReadString(string msg)
{
	string num;
	cout << msg;

	getline(cin >> ws, num);

	return num;
}

vector <string> vFun(string sdate, string delim)
{
	vector <string> vWord;
	int pos = 0;
	string word = "";

	while ((pos = sdate.find(delim)) != std::string::npos)
	{
		word = sdate.substr(0, pos);
		if (word != " ")
		{
			vWord.push_back(word);
		}
		sdate = sdate.erase(0, pos + delim.length());
	}
	if (sdate != " ")
	{
		vWord.push_back(sdate);
	}
	return vWord;
}

sDate ConvertToDateStruct(string sdate)
{
	sDate date;
	vector <string> vDate;

	vDate = vFun(sdate, "/");

	date.day = stoi(vDate[0]);
	date.month = stoi(vDate[1]);
	date.year = stoi(vDate[2]);
	

	return date;
}



string ConvertDateToString(sDate date)
{
	string sdate = to_string(date.day) + "/" + to_string(date.month) + "/" + to_string(date.year);

	return sdate;
}

int main()
{
	string m = "lll";
	string sdate = ReadString("Enter Date dd/mm/yyyy : ");

	sDate date = ConvertToDateStruct(sdate);

	cout << "Day : " << date.day << endl;
	cout << "Month : " << date.month << endl;
	cout << "Year : " << date.year << endl;

	cout << "\nYou entered : " << ConvertDateToString(date) << endl;
