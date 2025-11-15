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

sDate DecreaseDateByOneDay(sDate date)
{
	if (date.day == 1)
	{
		

		if (date.month == 1)
		{
			date.month = 12;
			date.day = 31;
			date.year--;
		}
		else
		{
			date.month--;
			date.day = NumberOfDaysInMonth(date.year, date.month);
		}
	}
	else
		date.day--;

	return date;
}
sDate DecreaseDateByXDays(short number,sDate date)
{
	for (int i = 1; i <= number; i++)
	{
		date = DecreaseDateByOneDay(date);
	}

	return date;
}
sDate DecreaseDateByOneWeek(sDate date)
{
	for (int i = 1; i <= 7; i++)
	{
		date = DecreaseDateByOneDay(date);
	}

	return date;
}
sDate DecreaseDateByXWeeks(short number,sDate date)
{
	for (int i = 1; i <= number; i++)
	{
		date = DecreaseDateByOneWeek(date);
	}

	return date;
}
sDate DecreaseDateByOneMonth(sDate date)
{
	if (date.month == 1)
	{
		date.month = 12;
		date.year--;
	}
	else
		date.month--;

	short nmonths = NumberOfDaysInMonth(date.year, date.month);
	if (date.day > nmonths)
		date.day = nmonths;
	

	return date;
}
sDate DecreaseDateByXMonths(short number,sDate date)
{
	for (int i = 1; i <= number; i++)
	{
		date = DecreaseDateByOneMonth(date);
	}

	return date;
}
sDate DecreaseDateByOneYear(sDate date)
{
	date.year--;
	return date;
}
sDate DecreaseDateByXYears(short number, sDate date)
{
	for (int i = 1; i <= number; i++)
	{
		date = DecreaseDateByOneYear(date);
	}

	return date;
}
sDate DecreaseDateByXYearsFaster(short number,sDate date)
{
	date.year -= number;

	return date;
}
sDate DecreaseDateByOneDecade(sDate date)
{
	date.year -= 10;

	return date;
}
sDate DecreaseDateByXDecades(short number,sDate date)
{
	for (int i = 1; i <= number; i++)
	{
		date = DecreaseDateByOneDecade(date);
	}

	return date;
}
sDate DecreaseDateByXDecadesFaster(short number, sDate date)
{
	date.year -= 10 * number;

	return date;
}
sDate DecreaseDateByOneCentery(sDate date)
{
	date.year -= 100;

	return date;
}
sDate DecreaseDateByOneMillenium(sDate date)
{
	date.year -= 1000;

	return date;
}

int main()
{
	sDate date = ReadFullData();

	cout << "Date After : \n\n";
	date = DecreaseDateByOneDay(date);
	cout << "01-Subtracting one day is  : " << date.day << "/" << date.month << "/" << date.year << endl;
	date = DecreaseDateByXDays(10, date);
	cout << "02-Subtracting 10 Days is  : " << date.day << "/" << date.month << "/" << date.year << endl;
	date = DecreaseDateByOneWeek(date);
	cout << "03-Subtracting 1 week is   : " << date.day << "/" << date.month << "/" << date.year << endl;
	date = DecreaseDateByXWeeks(10, date);
	cout << "04-Subtracting 10 week is  : " << date.day << "/" << date.month << "/" << date.year << endl;
	date = DecreaseDateByOneMonth(date);
	cout << "05-Subtracting 1 month is  : " << date.day << "/" << date.month << "/" << date.year << endl;
	date = DecreaseDateByXMonths(5, date);
	cout << "06-Subtracting 5 months is : " << date.day << "/" << date.month << "/" << date.year << endl;
	date = DecreaseDateByOneYear(date);
	cout << "07-Subtracting 1 year is   : " << date.day << "/" << date.month << "/" << date.year << endl;
	date = DecreaseDateByXYears(10, date);
	cout << "08-Subtracting 10 years is : " << date.day << "/" << date.month << "/" << date.year << endl;
	date = DecreaseDateByXYearsFaster(10, date);
	cout << "09-Subtracting 10 years is : " << date.day << "/" << date.month << "/" << date.year << endl;
	date = DecreaseDateByOneDecade(date);
	cout << "10-Subtracting 1 decade is : " << date.day << "/" << date.month << "/" << date.year << endl;
	date = DecreaseDateByXDecades(10, date);
	cout << "11-Subtracting 10 decade is: " << date.day << "/" << date.month << "/" << date.year << endl;
	date = DecreaseDateByXDecadesFaster(10, date);
	cout << "12-Subtracting 10 decade is: " << date.day << "/" << date.month << "/" << date.year << endl;
	date = DecreaseDateByOneCentery(date);
	cout << "13-Subtracting 1 centery is: " << date.day << "/" << date.month << "/" << date.year << endl;
	date = DecreaseDateByOneMillenium(date);
	cout << "14-Subtracting 1 millen is : " << date.day << "/" << date.month << "/" << date.year << endl;
