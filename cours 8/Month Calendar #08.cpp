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
int NumberOfDaysInMonth(int year, int month)
{

	short arr[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

	return ((month == 2) ? (IsLeapYear(year) ? 29 : 28) : arr[month - 1]);



}
string MonthShortName(int month)
{
	string arr[12] = { "jan","feb","march","apr","mai","jun","jull","aug","sep","oct","nov","dec" };

	return arr[month - 1];
}

void PrintMonthCalendar(int month,int year)
{
	int days = NumberOfDaysInMonth(year, month);
	int cal = Calculate(month, year, 1);

	printf("\n______________%s________________\n\n", MonthShortName(month).c_str());
	printf("  Sun  Mon  Tue  Wed  Thu  Fri  sat \n\n");

	
	
	for (int i = 0; i < cal; i++)
		printf("     ");

	int count = cal;
	for (int i = 1; i <= days;i++)
	{
		printf("%5d", i);
		

		if (++count == 7)
		{
			printf("\n");
			count = 0;
		}
		
		
	}

}

int main()
{
	

	int year = ReadYear();
	int month = ReadMonth();
	
	PrintMonthCalendar(month, year);
