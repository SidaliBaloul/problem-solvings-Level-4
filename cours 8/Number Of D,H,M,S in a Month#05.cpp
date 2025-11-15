using namespace std;
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

bool IsLeapYear(int year)
{
	return ((year % 400 == 0) || ((year % 100 != 0) && (year % 4 == 0)));
}

int NumberOfDaysInMonth(int year,int month)
{

	if (month == 2)
		return (IsLeapYear(year) ? 29 : 28);

	short arr[7] = { 1,3,5,7,8,10,12 };

		for (int i = 0; i < 7; i++)
		{
			if (arr[i] == month)
			{
				return 31;
			}
		}
		return 30;
	
}
int NumberOfHoursInMonth(int year, int month)
{
	return NumberOfDaysInMonth(year,month) * 24;
}
int NumberOfMinutesInMonth(int year, int month)
{
	return NumberOfHoursInMonth(year, month) * 60;
}
int NumberOfSecondesInMonth(int year, int month)
{
	return NumberOfMinutesInMonth(year, month) * 60;
}


int main()
{

	int year = ReadYear();
	int month = ReadMonth();

	cout << "number of days     in month [" << month << "] is : ";
	cout << NumberOfDaysInMonth(year,month) << endl;

	cout << "number of hours    in month [" << month << "] is : ";
	cout << NumberOfHoursInMonth(year, month) << endl;

	cout << "number of minutes  in month [" << month << "] is : ";
	cout << NumberOfMinutesInMonth(year, month) << endl;

	cout << "number of secondes in month [" << month << "] is : ";
	cout << NumberOfSecondesInMonth(year, month) << endl;
