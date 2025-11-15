

#include <iostream>
#include <string>
#include <iomanip>
#include<vector>
#include<fstream>


using namespace std;

string filename = "clients.txt";

void ATMMainMenuScreen();
void LoginScreen();

int ReadAmount()
{
	int num;
	cout << "Enter amount to deeposit ? ";
	cin >> num;

	return num;
}

int ReadWithdrawAmount()
{
	int amount;
	do
	{
		cout << "Enter an amount of 5's ? ";
		cin >> amount;

	} while (amount % 5 != 0);

	return amount;
}

int ReadDepositAmount()
{
	int amount;
	do
	{
		cout << "enter a positive amount : ";
		cin >> amount;

	} while (amount <= 0);

	return amount;
}

void GoBackToAtmMainMenu()
{
	cout << "Presse any key to go back ! ";
	system("pause>0");
	ATMMainMenuScreen();
}

enum eMainMenueOptions
{
	quickwithdraw = 1, normalwithdraw = 2, deposit = 3, checkbalance = 4, logout = 5
};

enum eQuickWithdraw
{
	twenty = 1, fyfty = 2 , onehundred = 3, twohundreds = 4, fourhundred = 5, sixhendreds = 6, eighthundreds = 7,
	onethousand = 8
};

struct stInfo
{
	string accountnumber;
	string pincode;
	string name;
	string phone;
	double accountbalance;
};

stInfo currentuser;

int ReadChoice(string msg, int from , int to )
{
	int num;
	do
	{
		cout << msg;
		cin >> num;
	} while (num < from || num > to);

	return num;
}

vector <string> Split(string line , string delim)
{
	vector <string> vInf;
	short pos = 0;
	string word = "";
	

	while ((pos = line.find(delim)) != std::string::npos)
	{
		word = line.substr(0, pos);

		if (word != " ")
		{
			vInf.push_back(word);
		}

		line = line.erase(0, pos + delim.length());

	}
	if (word != " ")
	{
		vInf.push_back(line);
	}

	return vInf;
}

stInfo ConvertStringToStruct(string line)
{
	vector <string> vInf;
	stInfo inf;

	vInf = Split(line, "//");

	inf.accountnumber = vInf[0];
	inf.pincode = vInf[1];
	inf.name = vInf[2];
	inf.phone = vInf[3];
	inf.accountbalance = stod(vInf[4]);

	return inf;
}

vector <stInfo> GetInfos(string filename)
{
	fstream file;
	vector <stInfo> vInf;
	stInfo inf;
	file.open(filename, ios::in);

	if (file.is_open())
	{
		string line;

		while (getline(file,line))
		{
			inf = ConvertStringToStruct(line);
			vInf.push_back(inf);
		}

		file.close();
	}
	return vInf;

}

string ConvertStructToString(stInfo inf,string delim = "//")
{
	string word = "";

	word += inf.accountnumber + delim;
	word += inf.pincode + delim;
	word += inf.name + delim;
	word += inf.phone + delim;
	word += to_string(inf.accountbalance);

	return word;
}

void SaveUpdateClientToFile(string filename,vector <stInfo> vInf)
{
	fstream file;
	file.open(filename, ios::out);

	if (file.is_open())
	{
		string line;

		for (stInfo& n : vInf)
		{
			line = ConvertStructToString(n);
			file << line + "\n";
		}
		file.close();
	}
}

bool CheckAccountnumberAndPincode(string accountnumber, string pincode , stInfo& currentuser)
{
	vector <stInfo> vInf = GetInfos(filename);

	for (stInfo& n : vInf)
	{
		if (n.accountnumber == accountnumber && n.pincode == pincode)
		{
			currentuser = n;
			return true;
		}
	}
	return false;
}

bool LoadUserInfo(string accountnumber, string pincode)
{
	if (CheckAccountnumberAndPincode(accountnumber, pincode, currentuser))
		return true;
	else
		return false;

}

bool DepositAmount(string accountnumber, double amount, vector <stInfo>& vinf)
{
	char yesno = 'n';

	cout << "are you sure you want perform this transaction ? Y/N : ";
	cin >> yesno;

	if (yesno == 'y' || yesno == 'Y')
	{
		for (stInfo& n : vinf)
		{
			if (n.accountnumber == accountnumber)
			{
				n.accountbalance += amount;
				SaveUpdateClientToFile(filename, vinf);
				cout << "Done succefully . New balance is : " << n.accountbalance;

				return true;
			}
		}

		return false;
	}

}

int EnterToQuickWithdrawOptions(int eoptionn)
{
	switch (eoptionn)
	{
	case 1:
		return 20;
	case 2:
		return 50;
	case 3:
		return 100;
	case 4:
		return 200;
	case 5:
		return 400;
	case 6:
		return 600;
	case 7:
		return 800;
	case 8:
		return 1000;

	}
}

void QuickWithdrawUperations(int choice)
{
	
	char yesno = 'Y';
	
	if (choice == 9)
		return;

	int amount = EnterToQuickWithdrawOptions(choice);

	if (currentuser.accountbalance < amount)
	{
		cout << "The amount exceeds ur balance, make another choice ! ";
		return;
	}
	
	vector <stInfo> vInf = GetInfos(filename);
	DepositAmount(currentuser.accountnumber, amount * -1, vInf);
	currentuser.accountbalance -= amount;

}

void NormalWithdrawOperations()
{
	int amount = ReadWithdrawAmount();
	
	if (currentuser.accountbalance < amount)
	{
		cout << "The amount exceeds ur balance, make another choice ! ";
		return;
	}

	vector <stInfo> vInf = GetInfos(filename);
	DepositAmount(currentuser.accountnumber, amount * -1, vInf);
	currentuser.accountbalance -= amount;
}

void DepositOperations()
{
	int amount = ReadDepositAmount();

	vector <stInfo> vInf = GetInfos(filename);
	DepositAmount(currentuser.accountnumber, amount , vInf);
	currentuser.accountbalance += amount;
	
}

void DepositScreen()
{
	system("cls");
	cout << "---------------------------------------------------\n";
	cout << "                 DEPOSIT SCREEN            \n";
	cout << "---------------------------------------------------\n";

	DepositOperations();
}

void NormalWithdrawScreen()
{
	system("cls");
	cout << "---------------------------------------------------\n";
	cout << "               NORMAL Withdraw SCREEN        \n";
	cout << "---------------------------------------------------\n";

	NormalWithdrawOperations();
}

void QuickWithdrawScreen()
{
	system("cls");
	cout << "---------------------------------------------------\n";
	cout << "               Quick Withdraw SCREEN        \n";
	cout << "---------------------------------------------------\n";
	cout << "       [1] 20                  [2] 50              \n";
	cout << "       [3] 100                 [4] 200             \n";
	cout << "       [5] 400                 [6] 600             \n";
	cout << "       [7] 800                 [8] 1000            \n";
	cout << "       [9] Exit                                    \n";
	cout << "---------------------------------------------------\n";
	cout << "Your Balance is : " << currentuser.accountbalance << endl;

	QuickWithdrawUperations(ReadChoice("Choose what do u want to withdraw [ 1 to 8 ] ?", 1, 9));

}

void CheckBalanceScreen()
{
	system("cls");
	cout << "---------------------------------------------------\n";
	cout << "               CHECK BALANCE SCREEN        \n";
	cout << "---------------------------------------------------\n";

	cout << "Your Balance is : " << currentuser.accountbalance << endl << endl;
}

void EnterToFunctions(eMainMenueOptions eoption)
{
	switch (eoption)
	{
	case eMainMenueOptions::quickwithdraw:
		system("cls");
		QuickWithdrawScreen();
		GoBackToAtmMainMenu();
		break;
	case eMainMenueOptions::normalwithdraw:
		system("cls");
		NormalWithdrawScreen();
		GoBackToAtmMainMenu();
		break;
	case eMainMenueOptions::deposit:
		system("cls");
		DepositScreen();
		GoBackToAtmMainMenu();
		break;
	case eMainMenueOptions::checkbalance:
		system("cls");
		CheckBalanceScreen();
		GoBackToAtmMainMenu();
		break;
	case eMainMenueOptions::logout:
		system("cls");
		LoginScreen();
		break;
	}
}

void ATMMainMenuScreen()
{
	system("cls");
	cout << "---------------------------------------------------\n";
	cout << "               ATM MAIN MENU SCREEN        \n";
	cout << "---------------------------------------------------\n";
	cout << "                [1] Quick Withdraw                 \n";
	cout << "                [2] Normal Withdraw                \n";
	cout << "                [3] Deposit                        \n";
	cout << "                [4] Check Balance                  \n";
	cout << "                [5] Logout                         \n";
	cout << "---------------------------------------------------\n";

	EnterToFunctions((eMainMenueOptions)ReadChoice("Choose what do u want to do ? [1 to 5 ] ?", 1, 5));
}

void LoginScreen()
{
	string accountnumber, pincode;
	bool key = false;

	do
	{
		system("cls");
		cout << "---------------------------------------------------\n";
		cout << "                LOGIN SCREEN             \n";
		cout << "---------------------------------------------------\n";

		if (key)
			cout << "Invalid accountnumber/pincode \n";

		cout << "Enter account number : ";
		cin >> accountnumber;

		cout << "Enter pincode : ";
		cin >> pincode;

		key = !LoadUserInfo(accountnumber, pincode);
		
	} while (key);

	ATMMainMenuScreen();
}

int main()
{
	LoginScreen();
