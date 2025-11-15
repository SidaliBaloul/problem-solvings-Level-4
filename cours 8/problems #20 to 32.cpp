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
sDate IncreaseDateByXDays(short number,sDate date)
{
	for (int i = 1; i <= number; i++)
	{
		date = IncreaseDateByOneDay(date);
	}

	return date;
}
sDate IncreaseDateByOneWeek(sDate date)
{
	for (int i = 1; i <= 7; i++)
	{
		date = IncreaseDateByOneDay(date);
	}

	return date;
}
sDate IncreaseDateByXWeeks(short number,sDate date)
{
	for (int i = 1; i <= number; i++)
	{
		date = IncreaseDateByOneWeek(date);
	}

	return date;
}
sDate IncreaseDateByOneMonth(sDate date)
{
	if (IsLastMonthInYear(date))
	{
		date.month = 1;
		date.year++;
	}
	else
		date.month++;

	short nmonths = NumberOfDaysInMonth(date.year, date.month);
	if (IsLastDayInMonth(date))
		date.day = nmonths;
	

	return date;
}
sDate IncreaseDateByXMonths(short number,sDate date)
{
	for (int i = 1; i <= number; i++)
	{
		date = IncreaseDateByOneMonth(date);
	}

	return date;
}
sDate IncreaseDateByOneYear(sDate date)
{
	date.year++;
	return date;
}
sDate IncreaseDateByXYears(short number, sDate date)
{
	for (int i = 1; i <= number; i++)
	{
		date = IncreaseDateByOneYear(date);
	}

	return date;
}
sDate IncreaseDateByXYearsFaster(short number,sDate date)
{
	date.year += number;

	return date;
}
sDate IncreaseDateByOneDecade(sDate date)
{
	date.year += 10;

	return date;
}
sDate IncreaseDateByXDecades(short number,sDate date)
{
	for (int i = 1; i <= number; i++)
	{
		date = IncreaseDateByOneDecade(date);
	}

	return date;
}
sDate IncreaseDateByXDecadesFaster(short number, sDate date)
{
	date.year += 10 * number;

	return date;
}
sDate IncreaseDateByOneCentery(sDate date)
{
	date.year += 100;

	return date;
}
sDate IncreaseDateByOneMillenium(sDate date)
{
	date.year += 1000;

	return date;
}

int main()
{
	sDate date = ReadFullData();

	cout << "Date After : \n\n";
	date = IncreaseDateByOneDay(date);
	cout << "01-Adding one day is  : " << date.day << "/" << date.month << "/" << date.year << endl;
	date = IncreaseDateByXDays(10, date);
	cout << "02-Adding 10 Days is  : " << date.day << "/" << date.month << "/" << date.year << endl;
	date = IncreaseDateByOneWeek(date);
	cout << "03-Adding 1 week is   : " << date.day << "/" << date.month << "/" << date.year << endl;
	date = IncreaseDateByXWeeks(10, date);
	cout << "04-Adding 10 week is  : " << date.day << "/" << date.month << "/" << date.year << endl;
	date = IncreaseDateByOneMonth(date);
	cout << "05-Adding 1 month is  : " << date.day << "/" << date.month << "/" << date.year << endl;
	date = IncreaseDateByXMonths(5, date);
	cout << "06-Adding 5 months is : " << date.day << "/" << date.month << "/" << date.year << endl;
	date = IncreaseDateByOneYear(date);
	cout << "07-Adding 1 year is   : " << date.day << "/" << date.month << "/" << date.year << endl;
	date = IncreaseDateByXYears(10, date);
	cout << "08-Adding 10 years is : " << date.day << "/" << date.month << "/" << date.year << endl;
	date = IncreaseDateByXYearsFaster(10, date);
	cout << "09-Adding 10 years is : " << date.day << "/" << date.month << "/" << date.year << endl;
	date = IncreaseDateByOneDecade(date);
	cout << "10-Adding 1 decade is : " << date.day << "/" << date.month << "/" << date.year << endl;
	date = IncreaseDateByXDecades(10, date);
	cout << "11-Adding 10 decade is: " << date.day << "/" << date.month << "/" << date.year << endl;
	date = IncreaseDateByXDecadesFaster(10, date);
	cout << "12-Adding 10 decade is: " << date.day << "/" << date.month << "/" << date.year << endl;
	date = IncreaseDateByOneCentery(date);
	cout << "13-Adding 1 centery is: " << date.day << "/" << date.month << "/" << date.year << endl;
	date = IncreaseDateByOneMillenium(date);
	cout << "14-Adding 1 millen is : " << date.day << "/" << date.month << "/" << date.year << endl;
