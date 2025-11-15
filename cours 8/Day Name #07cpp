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

bool IsLeapYear(int year)
{
	return ((year % 400 == 0) || ((year % 100 != 0) && (year % 4 == 0)));
}

int Calculate(int month,int year,int day)
{
	int a, y, m, d;

	a = (14 - month) / 12;
	y = year - a;
	m = month + 12 * a - 2;
	d = (day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;

	return d;
}

string DayShortName(int dayorder)
{
	string arr[7] = { "sunday","monday","tuesday","wednesday","thursday","friday","saturday" };

	return arr[dayorder];
}

int main()
{
	

	int year = ReadYear();
	int month = ReadMonth();
	int day = ReadDay();
	
	cout << "\nDate      : " << day << "/" << month << "/" << year << endl;
	cout << "Day order : " << Calculate(month, year, day) << endl;
	cout << "Day name  : " << DayShortName(Calculate(month, year, day)) << endl;
