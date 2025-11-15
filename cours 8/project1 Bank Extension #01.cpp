

#include <iostream>
#include <string>
#include <iomanip>
#include<vector>
#include<fstream>


using namespace std;

string filename = "clients.txt";
string usersfile = "users.txt";

void LoginScreen();
void MainMenuScreen();
void TransactionsScreen();
void ManageUsersScreen();

struct stInfos
{
	string accountnumber;
	string pincode;
	string name;
	string phone;
	double accountbalance;
	bool deleteclient = false;
};

struct stUserInfos
{
	string username;
	string password;
	int access;
	bool deleteuser = false;
};

enum eoptions
{
	showlist = 1, addnew = 2, deleteclient = 3,
	update = 4, find = 5,
	transactions = 6, manageusers = 7 , logout = 8
};

enum etransaction
{
	deposit = 1, withdraw = 2, totalbalances = 3, mainmenu = 4
};

enum eUsers
{
	listusers = 1, addnewuser = 2, deleteuser = 3, updateuser = 4, finduser = 5, mmainmenu = 6
};

enum enMainMenuPermessions
{
	pall = -1, plistclient = 1, paddnewclient = 2, pdeleteclient = 4, pupdateclient = 8,
	pfindclient = 16, ptransactions = 32, pmanageusers = 64 
};

stUserInfos currentuser;

int ReadChoice(short from, short to, string msg)
{
	int num;
	do
	{
		cout << msg;
		cin >> num;
	} while (num < from || num > to);

	return num;
}

void RecordLine(stInfos n)
{
	cout << " | " << setw(15) << n.accountnumber << " | " << setw(25) << n.name << " | " << setw(15) << n.accountbalance << " | \n";
}

void RecordUsersLine(stUserInfos n)
{
	cout << " | " << setw(15) << n.username << " | " << setw(10) << n.password << " | " << setw(15) << n.access << " | \n";
}

string ReadUsername()
{
	string username;
	cout << "Enter username : ";
	getline(cin >> ws, username);

	return username;
}

string ReadPassword()
{
	string num;
	cout << "Enter password : ";
	getline(cin, num);

	return num;
}

void GoBackToMainMenu()
{

	cout << "press any key to go back : ";
	system("pause>0");
	MainMenuScreen();

}

void GoBackToTransactionsMenu()
{
	cout << "press any key to go back : ";
	system("pause>0");
	TransactionsScreen();
}

void GoBackToManageUsersMenu()
{
	cout << "Press any button to go back : ";
	system("pause>0");
	ManageUsersScreen();
}

string ReadAccountNumber()
{
	string Number;
	cout << "enter account number : ";
	cin >> Number;

	return Number;
}

vector <string> Split(string line, string delim)
{
	vector <string> vline;
	short pos = 0;
	string sword = "";

	while ((pos = line.find(delim)) != std::string::npos)
	{
		sword = line.substr(0, pos);
		if (sword != " ")
		{
			vline.push_back(sword);
		}
		line = line.erase(0, pos + delim.length());
	}
	if (line != " ")
	{
		vline.push_back(line);
	}

	return vline;
}

bool CheckAccessPermession(enMainMenuPermessions permession)
{
	if (currentuser.access == enMainMenuPermessions::pall)
	{
		return true;
	}

	if ((permession & currentuser.access) == permession)
		return true;
	else
		return false;
}

stInfos ConvertVectorToStruct(string line)
{

	vector <string> vInf;
	stInfos inf;

	vInf = Split(line, "//");

	inf.accountnumber = vInf[0];
	inf.pincode = vInf[1];
	inf.name = vInf[2];
	inf.phone = vInf[3];
	inf.accountbalance = stod(vInf[4]);

	return inf;
}

stUserInfos ConverteVectorToStruct(string line)
{
	vector <string> vUser;
	stUserInfos infu;

	vUser = Split(line, "//");

	infu.username = vUser[0];
	infu.password = vUser[1];
	infu.access = stoi(vUser[2]);

	return infu;
}

string ConvertStructToString(stInfos inf, string delim = "//")
{
	string line;

	line += inf.accountnumber + delim;
	line += inf.pincode + delim;
	line += inf.name + delim;
	line += inf.phone + delim;
	line += to_string(inf.accountbalance);

	return line;
}

string ConvertUsersStructToString(stUserInfos infu, string delim = "//")
{
	string word = "";

	word += infu.username + delim;
	word += infu.password + delim;
	word += to_string(infu.access);

	return word;
}

vector <stInfos> GetInfos(string filename)
{
	fstream file;

	vector <stInfos> vinff;
	stInfos inf;

	file.open(filename, ios::in);

	if (file.is_open())
	{
		string line;
		while (getline(file, line))
		{
			inf = ConvertVectorToStruct(line);
			vinff.push_back(inf);
		}

	}
	file.close();

	return vinff;
}

vector <stUserInfos> GetUserInfos(string usersfile)
{
	vector <stUserInfos> vUser;
	fstream file;
	stUserInfos infu;

	file.open(usersfile, ios::in);

	if (file.is_open())
	{
		string line;

		while (getline(file,line))
		{
			infu = ConverteVectorToStruct(line);
			vUser.push_back(infu);
		}
	}
	file.close();

	return vUser;
}

void AddClientToFile(string filename, string line)
{
	fstream file;

	file.open(filename, ios::app);

	if (file.is_open())
	{
		file << line + "\n";

	}
	file.close();
}

void AccessDenied()
{
	system("cls");
	cout << "---------------------------------------------------\n";
	cout << "Access Denied, \n";
	cout << "you don't have permission to do this,\n Please conact your admin ! \n";
	cout << "---------------------------------------------------\n";
}

void AddUserToFile(string usersfile,string line)
{
	fstream file;
	file.open(usersfile, ios::app);

	if (file.is_open())
	{
		file << line + "\n";
	}
	file.close();
}

void PrintClientList()
{
	vector <stInfos> vinf = GetInfos(filename);

	if (!CheckAccessPermession(enMainMenuPermessions::plistclient))
	{
		AccessDenied();
		return;
	}

	cout << "                               Client List (" << vinf.size() << ") Client(s).                             \n";
	cout << "----------------------------------------------------------------------------------------------\n";
	cout << " | " << setw(15) << "Account Number " << " | " << setw(10) << "Pin Code " << " | " << setw(25) << "Client Name " << " | " << setw(10) << "Phone" << " | " << setw(15) << "Balance" << " | \n";
	cout << "----------------------------------------------------------------------------------------------\n";

	for (stInfos& n : vinf)
	{
		cout << " | " << setw(15) << n.accountnumber << " | " << setw(10) << n.pincode << " | " << setw(25) << n.name << " | " << setw(10) << n.phone << " | " << setw(15) << n.accountbalance << " | \n";
	}
	cout << "----------------------------------------------------------------------------------------------\n";


}

bool CheckIfClientExist(vector <stInfos>& vinf, stInfos& client, string accountnum)
{
	for (stInfos& n : vinf)
	{
		if (n.accountnumber == accountnum)
		{
			n.deleteclient = true;
			client = n;
			return true;
		}
	}
	return false;
}

void PrintClientCard(stInfos inf)
{
	cout << "Account number  : " << inf.accountnumber << endl;
	cout << "Pin code        : " << inf.pincode << endl;
	cout << "Name            : " << inf.name << endl;
	cout << "Phone           : " << inf.phone << endl;
	cout << "Account Balance : " << inf.accountbalance << endl;
}

void PrintUserCard(stUserInfos infu)
{
	cout << "Username    : " << infu.username << endl;
	cout << "Password    : " << infu.password << endl;
	cout << "Permissions : " << infu.access << endl;

}

void ShowUsersList()
{
	vector <stUserInfos> vUser = GetUserInfos(usersfile);

	cout << "                               Users List (" << vUser.size() << ") User(s).                             \n";
	cout << "----------------------------------------------------------------------------------------------\n";
	cout << " | " << setw(15) << "User Name " << " | " << setw(10) << "Password " << " | " << setw(15) << "Permessions " << " | \n";
	cout << "----------------------------------------------------------------------------------------------\n";

	for (stUserInfos& n : vUser)
	{
		RecordUsersLine(n);
	}
	cout << "----------------------------------------------------------------------------------------------\n";

	
}

void DeleteClientFromFile(string filename, vector <stInfos> vinf)
{
	fstream file;
	string line;
	file.open(filename, ios::out);

	if (file.is_open())
	{
		for (stInfos& n : vinf)
		{
			if (n.deleteclient == false)
			{
				line = ConvertStructToString(n);
				file << line + "\n";
			}
		}

	}
	file.close();
}

bool DeleteClientByAccountNumber(string accountnumber, vector <stInfos>& vinf)
{
	stInfos client;
	char yesno = 'n';


	if (CheckIfClientExist(vinf, client, accountnumber))
	{

		PrintClientCard(client);

		cout << "are you sure you want to delete this client ? Y/N : ";
		cin >> yesno;

		if (yesno == 'y' || yesno == 'Y')
		{
			DeleteClientFromFile(filename, vinf);
			vinf = GetInfos(filename);
			cout << "client deleted succefully.";
			return true;
		}
	}
	else
	{
		cout << "client Not found ! ";
		return false;
	}

}

void DeleteCientScreen()
{
	if (!CheckAccessPermession(enMainMenuPermessions::pdeleteclient))
	{
		AccessDenied();
		return;
	}

	cout << "---------------------------------------------------------------\n";
	cout << "                      DELETE CLIENT SCREEN                     \n";
	cout << "----------------------------------------------------------------n\n";

	vector <stInfos> vinf = GetInfos(filename);
	string accountnumber = ReadAccountNumber();
	DeleteClientByAccountNumber(accountnumber, vinf);


}

bool ClientExistByAccountNumber(string accountnumber, string filename)
{
	vector <stInfos> vinf;
	fstream file;
	file.open(filename, ios::in);

	if (file.is_open())
	{
		string line;
		stInfos inf;

		while (getline(file, line))
		{
			inf = ConvertVectorToStruct(line);
			if (inf.accountnumber == accountnumber)
			{
				file.close();
				return true;
			}
			vinf.push_back(inf);
		}
		file.close();
	}

	return false;
}

stInfos ReadNewClientInfos()
{
	stInfos inf;
	cout << "enter account number : ";

	getline(cin >> ws, inf.accountnumber);

	while (ClientExistByAccountNumber(inf.accountnumber, filename))
	{
		cout << "client with [" << inf.accountnumber << "] already exist, enter another : ";
		getline(cin >> ws, inf.accountnumber);
	}

	cout << "enter PinCode : ";
	getline(cin, inf.pincode);

	cout << "enter name : ";
	getline(cin, inf.name);

	cout << "enter phone : ";
	getline(cin, inf.phone);

	cout << "enter account balance : ";
	cin >> inf.accountbalance;

	return inf;
}

void AddUpdatedClientToFile(string filename, vector <stInfos> vinf)
{
	fstream file;
	string line;
	file.open(filename, ios::out);

	if (file.is_open())
	{
		string line;
		for (stInfos& n : vinf)
		{
			line = ConvertStructToString(n);
			file << line + "\n";
		}


	}
	file.close();
}

void AddNewClient()
{
	stInfos info;
	info = ReadNewClientInfos();
	AddClientToFile(filename, ConvertStructToString(info));
}

void AddNewClients()
{

	stInfos info;
	char yesno = 'Y';
	do
	{
		cout << "Adding new client : " << endl;

		AddNewClient();
		cout << "client added succefully ,do you want to add another ? Y/N : ";
		cin >> yesno;

	} while (yesno == 'y' || yesno == 'Y');

}

void AddNewClientsScreen()
{

	if (!CheckAccessPermession(enMainMenuPermessions::paddnewclient))
	{
		AccessDenied();
		return;
	}

	cout << "-----------------------------------------------------------------\n";
	cout << "                        ADD NEW CLIENTS SCREEN                   \n";
	cout << "-----------------------------------------------------------------\n";

	AddNewClients();
}

bool CheckIfUserAlreadyExists(vector <stUserInfos>& vUser,string username,stUserInfos& user)
{
	for (stUserInfos& n : vUser)
	{
		if (n.username == username)
		{
			user = n;
			n.deleteuser = true;
			return true;
		}
	}
	return false;
}

int GiveAccess()
{
	char yesno = 'Y';
	int number = 0;

	cout << "Do u want to give full access ? Y/N ? ";
	cin >> yesno;

	if (yesno == 'Y' || yesno == 'y')
	{
		return -1;
	}

	cout << "Do u Want to give access to : \n";
	
	cout << "Show client list ? Y/N ? ";
	cin >> yesno;

	if (yesno == 'Y' || yesno == 'y')
	{
		number += enMainMenuPermessions::plistclient;
	}


	cout << "Add new client ? Y/N ? ";
	cin >> yesno;

	if (yesno == 'Y' || yesno == 'y')
	{
		number += enMainMenuPermessions::paddnewclient;
	}


	cout << "Delete client ? Y/N ? ";
	cin >> yesno;

	if (yesno == 'Y' || yesno == 'y')
	{
		number += enMainMenuPermessions::pdeleteclient;
	}

	cout << "Update client ? Y/N ? ";
	cin >> yesno;

	if (yesno == 'Y' || yesno == 'y')
	{
		number += enMainMenuPermessions::pupdateclient;
	}

	cout << "find client ? Y/N ? ";
	cin >> yesno;

	if (yesno == 'Y' || yesno == 'y')
	{
		number += enMainMenuPermessions::pfindclient;
	}

	cout << "Transactions ? Y/N ? ";
	cin >> yesno;

	if (yesno == 'Y' || yesno == 'y')
	{
		number += enMainMenuPermessions::ptransactions;
	}

	cout << "Manage users ? Y/N ? ";
	cin >> yesno;

	if (yesno == 'Y' || yesno == 'y')
	{
		number += enMainMenuPermessions::pmanageusers;
	}

	return number;
}

stUserInfos ReadNewUserInfo(stUserInfos infu)
{
	stUserInfos user;
	vector<stUserInfos> vUser = GetUserInfos(usersfile);

	cout << "Enter user name : ";
	cin >> infu.username;

	while (CheckIfUserAlreadyExists(vUser,infu.username,user))
	{
		cout << "User with username [" << infu.username << "] already exists, try another : ";
		cin >> infu.username;
	}

	cout << "Enter password : ";
	cin >> infu.password;

	infu.access = GiveAccess();

	return infu;

}

void AddNewUser()
{
	stUserInfos infu;
	infu = ReadNewUserInfo(infu);
	AddUserToFile(usersfile, ConvertUsersStructToString(infu));
}

void AddNewUsers()
{
	char yesno = 'Y';
	do
	{
		cout << "Adding new user : \n";
		AddNewUser();

		cout << "User added successfully , do u want to add more users ? Y/N ? ";
		cin >> yesno;
	} while (toupper(yesno) == 'Y');
}

void AddNewUserScreen()
{
	cout << "---------------------------------------------------\n";
	cout << "                ADD NEW USER SCREEN                \n";
	cout << "---------------------------------------------------\n";

	AddNewUsers();
	

}

stInfos ReadUpdatedClientInfos(string accountnumber)
{
	stInfos inf;

	inf.accountnumber = accountnumber;

	cout << "enter PinCode : ";
	getline(cin >> ws, inf.pincode);

	cout << "enter name : ";
	getline(cin, inf.name);

	cout << "enter phone : ";
	getline(cin, inf.phone);

	cout << "enter account balance : ";
	cin >> inf.accountbalance;

	return inf;
}

bool UpdateClientByAccountNumber(string accountnumber, vector <stInfos>& vinf)
{
	stInfos client;
	char yesno = 'n';

	if (CheckIfClientExist(vinf, client, accountnumber))
	{
		PrintClientCard(client);

		cout << "are you sure you want to update this client ? Y/N : ";
		cin >> yesno;

		if (yesno == 'Y' || yesno == 'y')
		{
			for (stInfos& n : vinf)
			{
				if (n.accountnumber == accountnumber)
				{
					n = ReadUpdatedClientInfos(accountnumber);
					break;
				}
			}
			AddUpdatedClientToFile(filename, vinf);

			vinf = GetInfos(filename);
			cout << "client updated succefully.";
			return true;
		}
	}
	else
	{
		cout << "client not found !";
	}
}

void UpdateClientInfos()
{
	if (!CheckAccessPermession(enMainMenuPermessions::pupdateclient))
	{
		AccessDenied();
		return;
	}

	cout << "---------------------------------------------------------------\n";
	cout << "                      UPDATE CLIENT SCREEN                     \n";
	cout << "----------------------------------------------------------------n\n";

	vector <stInfos> vinf = GetInfos(filename);
	string accountnumber = ReadAccountNumber();
	UpdateClientByAccountNumber(accountnumber, vinf);

}

void FindClient()
{
	if (!CheckAccessPermession(enMainMenuPermessions::pfindclient))
	{
		AccessDenied();
		return;
	}

	cout << "---------------------------------------------------------------\n";
	cout << "                      FIND CLIENT SCREEN                     \n";
	cout << "---------------------------------------------------------------\n";

	vector <stInfos> vinf = GetInfos(filename);
	string accountnumber = ReadAccountNumber();
	stInfos inf;

	if (CheckIfClientExist(vinf, inf, accountnumber))
	{
		PrintClientCard(inf);
	}
	else
		cout << "client with [" << accountnumber << "] is not found ! ";


}

bool DepositAmount(string accountnumber, double amount, vector <stInfos>& vinf)
{
	char yesno = 'n';

	cout << "are you sure you want perform this transaction ? Y/N : ";
	cin >> yesno;

	if (yesno == 'y' || yesno == 'Y')
	{
		for (stInfos& n : vinf)
		{
			if (n.accountnumber == accountnumber)
			{
				n.accountbalance += amount;
				AddUpdatedClientToFile(filename, vinf);
				cout << "Done succefully . New balance is : " << n.accountbalance;

				return true;
			}
		}

		return false;
	}

}

void CheckIfAmountIsBiggerThanBlance(double& amount, stInfos client)
{
	while (amount > client.accountbalance)
	{
		cout << "Amount exceeds the balance, you can withdraw up to : " << client.accountbalance << endl;
		cout << "Please enter another amount : ";
		cin >> amount;
	}

}

bool CheckUsernameAndPassword(string username,string password,stUserInfos& currentuser)
{
	vector <stUserInfos> vUser = GetUserInfos(usersfile);

	for (stUserInfos& n : vUser)
	{
		if (n.username == username && n.password == password)
		{
			currentuser = n;
			return true;
		}
	}
	return false;
}

bool LoadUserInfo(string username,string password)
{
	if (CheckUsernameAndPassword(username, password, currentuser))
	{
		return true;
	}
	else
		return false;
}

void DeleteUserFromFile(vector <stUserInfos> vUser,string usersfile)
{
	fstream file;
	string line;
	file.open(usersfile, ios::out);

	if (file.is_open())
	{
		for (stUserInfos& n : vUser)
		{
			if (n.deleteuser == false)
			{
				line = ConvertUsersStructToString(n);
				file << line + "\n";
			}
		}
	}
	file.close();
}

bool DeleteUsers(vector <stUserInfos>& vUser, string username)
{
	stUserInfos user;
	char yesno = 'Y';

	if (CheckIfUserAlreadyExists(vUser, username, user))
	{
		if (username == "Admin")
		{
			cout << "U can't delete the admin ! ";
			return false;
		}

		PrintUserCard(user);

		cout << "Are u sure u want to delete this User ? Y/N ? ";
		cin >> yesno;

		if (yesno == 'Y' || yesno == 'y')
		{
			DeleteUserFromFile(vUser, usersfile);
			vUser = GetUserInfos(usersfile);
			cout << "User deleted succefully ! \n";
			return true;
		}
	}
	else
	{
		cout << "User not found ! ";
		return false;
	}
	
}

void DeleteUsersScreen()
{

	cout << "---------------------------------------------------\n";
	cout << "                DELETE USERS SCREEN                \n";
	cout << "---------------------------------------------------\n";

	vector <stUserInfos> vUser = GetUserInfos(usersfile);
	string username = ReadUsername();
	DeleteUsers(vUser, username);
}

void UpdateUserFromFile(vector <stUserInfos> vUser,string usersfile)
{
	fstream file;
	string line;
	file.open(usersfile, ios::out);

	if (file.is_open())
	{
		for (stUserInfos& n : vUser)
		{
			line = ConvertUsersStructToString(n);
			file << line + "\n";
		}

	}
	file.close();
}

stUserInfos UpdateUserInfos(string username)
{
	stUserInfos infu;

	infu.username = username;

	cout << "Enter password : ";
	getline(cin >> ws, infu.password);

	infu.access = GiveAccess();

	return infu;
}

bool UpdateUsers(vector <stUserInfos>& vUser, string username)
{
	stUserInfos user;
	stUserInfos infu;
	char yesno = 'Y';

	if (CheckIfUserAlreadyExists(vUser,username,user))
	{
		if (username == "Admin")
		{
			cout << "U cant update the admin ! ";
			return false;
		}

		PrintUserCard(user);

		cout << "Are u sure u want to update this user ? Y/N ? ";
		cin >> yesno;

		if (yesno == 'Y' || yesno == 'y')
		{

			for (stUserInfos& n : vUser)
			{
				if (n.username == username)
				{
					n = UpdateUserInfos(username);
					
					break;
				}
			}
			UpdateUserFromFile(vUser, usersfile);
			vector <stUserInfos> vUser = GetUserInfos(usersfile);
			cout << "Client Updated succefully ! ";
		}
	}
	else
	{
		cout << "User not found ! ";
		return false;
	}
}

void UpdateUsersScreen()
{

	cout << "---------------------------------------------------\n";
	cout << "                UPDATE USERS SCREEN                \n";
	cout << "---------------------------------------------------\n";

	vector <stUserInfos> vUser = GetUserInfos(usersfile);
	string username = ReadUsername();
	UpdateUsers(vUser, username);
}

void FindUser(vector <stUserInfos> vUser,string username)
{
	stUserInfos user;
	if (CheckIfUserAlreadyExists(vUser, username, user))
		PrintUserCard(user);
	else
		cout << "User not found ! ";
}

void FindUsersScreen()
{
	cout << "---------------------------------------------------\n";
	cout << "                UPDATE USERS SCREEN                \n";
	cout << "---------------------------------------------------\n";

	vector <stUserInfos> vUser = GetUserInfos(usersfile);
	string username = ReadUsername();
	FindUser(vUser, username);
}

void WithdrawScreen()
{
	cout << "---------------------------------------------------\n";
	cout << "                WITHDRAW MENU SCREEN                \n";
	cout << "---------------------------------------------------\n";

	vector <stInfos> vinf = GetInfos(filename);
	string accountnumber = ReadAccountNumber();

	stInfos client;
	double amount = 0;


	while (!CheckIfClientExist(vinf, client, accountnumber))
	{
		cout << "Client with [" << accountnumber << "] not found ! \n";
		accountnumber = ReadAccountNumber();
	}

	PrintClientCard(client);

	cout << "please enter withdraw amount : ";
	cin >> amount;

	CheckIfAmountIsBiggerThanBlance(amount, client);

	DepositAmount(accountnumber, amount * -1, vinf);
}

void DepositScreen()
{
	cout << "---------------------------------------------------\n";
	cout << "                DEPOSIT MENU SCREEN                \n";
	cout << "---------------------------------------------------\n";

	vector <stInfos> vinf = GetInfos(filename);
	string accountnumber = ReadAccountNumber();

	stInfos client;
	double amount = 0;


	while (!CheckIfClientExist(vinf, client, accountnumber))
	{
		cout << "Client with [" << accountnumber << "] not found ! \n";
		accountnumber = ReadAccountNumber();
	}

	PrintClientCard(client);

	cout << "please enter deposit amount : ";
	cin >> amount;

	DepositAmount(accountnumber, amount, vinf);

}

void TotalBalancesSecreen()
{
	vector <stInfos> vinf = GetInfos(filename);
	double total = 0;

	cout << "                      Client List (" << vinf.size() << ") Client(s).                   \n";
	cout << "------------------------------------------------------------------------\n";
	cout << " | " << setw(15) << "Account Number " << " | " << setw(25) << "Client Name " << " | " << setw(15) << "Balance" << " | \n";
	cout << "------------------------------------------------------------------------\n";

	if (vinf.size() == 0)
	{
		cout << "no more clients ";
	}
	else
	{
		for (stInfos& n : vinf)
		{
			RecordLine(n);
			total += n.accountbalance;
		}
	}
	cout << "-----------------------------------------------------------------------\n";

	cout << "                             TOTAL BALANCES = " << total << endl;
}

void EnterToTransactios(etransaction option)
{
	switch (option)
	{
	case etransaction::deposit:
		system("cls");
		DepositScreen();
		GoBackToTransactionsMenu();

	case etransaction::withdraw:
		system("cls");
		WithdrawScreen();
		GoBackToTransactionsMenu();

	case etransaction::totalbalances:
		system("cls");
		TotalBalancesSecreen();
		GoBackToTransactionsMenu();

	case etransaction::mainmenu:
		system("cls");
		MainMenuScreen();
	}
}

void TransactionsScreen()
{
	if (!CheckAccessPermession(enMainMenuPermessions::ptransactions))
	{
		AccessDenied();
		return;
	}
	system("cls");
	cout << "---------------------------------------------------\n";
	cout << "                TRANSACTIONS  MENU SCREEN          \n";
	cout << "---------------------------------------------------\n";
	cout << "                [1] Deposit                        \n";
	cout << "                [2] Withdraw                       \n";
	cout << "                [3] Total Balance                  \n";
	cout << "                [4] Main Menu                      \n";
	cout << "---------------------------------------------------\n";

	EnterToTransactios((etransaction)ReadChoice(1, 4, "Choose what do you want to do [1 to 4] : "));
}

void EnterManageUsers(eUsers optionn)
{
	switch (optionn)
	{
	case eUsers::listusers:
		system("cls");
		ShowUsersList();
		GoBackToManageUsersMenu();
		break;
	case eUsers::addnewuser:
		system("cls");
		AddNewUserScreen();
		GoBackToManageUsersMenu();
		break;
	case eUsers::deleteuser:
		system("cls");
		DeleteUsersScreen();
		GoBackToManageUsersMenu();
		break;
	case eUsers::updateuser:
		system("cls");
		UpdateUsersScreen();
		GoBackToManageUsersMenu();
		break;
	case eUsers::finduser:
		system("cls");
		FindUsersScreen();
		GoBackToManageUsersMenu();
		break;
	case eUsers::mmainmenu:
		system("cls");
		MainMenuScreen();
		break;
	}
}

void ManageUsersScreen()
{
	if (!CheckAccessPermession(enMainMenuPermessions::pmanageusers))
	{
		AccessDenied();
		GoBackToMainMenu();
		return;
	}

	system("cls");
	cout << "---------------------------------------------------\n";
	cout << "                MANAGE USERS MENU SCREEN           \n";
	cout << "---------------------------------------------------\n";
	cout << "                [1] List Users                     \n";
	cout << "                [2] Add New User                   \n";
	cout << "                [3] Delete User                    \n";
	cout << "                [4] Update User                    \n";
	cout << "                [5] Find User                      \n";
	cout << "                [6] Main Menue                     \n";
	cout << "---------------------------------------------------\n";

	EnterManageUsers((eUsers)ReadChoice(1, 6, "Choose what do u want to do ? [1 to 6] ? "));
}

void EnterToFunctions(eoptions option)
{
	switch (option)
	{
	case eoptions::showlist:
		system("cls");
		PrintClientList();
		GoBackToMainMenu();
		break;
	case eoptions::addnew:
		system("cls");
		AddNewClientsScreen();
		GoBackToMainMenu();
		break;
	case eoptions::deleteclient:
		system("cls");
		DeleteCientScreen();
		GoBackToMainMenu();
		break;
	case eoptions::update:
		system("cls");
		UpdateClientInfos();
		GoBackToMainMenu();
		break;
	case eoptions::find:
		system("cls");
		FindClient();
		GoBackToMainMenu();
		break;
	case eoptions::transactions:
		system("cls");
		TransactionsScreen();
		break;

	case eoptions::manageusers:
		system("cls");
		ManageUsersScreen();
		break;
	case eoptions::logout:
		system("cls");
		LoginScreen();
		break;
	}
}

void MainMenuScreen()
{
	system("cls");
	cout << "---------------------------------------------------\n";
	cout << "                MAIN MENU SCREEN          \n";
	cout << "---------------------------------------------------\n";
	cout << "                [1] Show Client List               \n";
	cout << "                [2] Add New Client                 \n";
	cout << "                [3] Delete Client                  \n";
	cout << "                [4] Update Client Info             \n";
	cout << "                [5] Find Client                    \n";
	cout << "                [6] Tranasactions                  \n";
	cout << "                [7] Manage users                   \n";
	cout << "                [8] Logout                         \n";
	cout << "---------------------------------------------------\n";

	EnterToFunctions((eoptions)ReadChoice(1, 8, "Choose what do you want to do [1 to 8] : "));
}

void LoginScreen()
{
	string username, password;
	int accesse;
	bool key = false;

	do
	{
		system("cls");
		cout << "---------------------------------------------------\n";
		cout << "                 LOGIN SCREEN                \n";
		cout << "---------------------------------------------------\n";

		if (key)
			cout << "Invalid Username/Password !\n";

		cout << "Enter username : ";
		cin >> username;

		cout << "Enter password : ";
		cin >> password;

		key = !LoadUserInfo(username, password);

	} while (key);

	
	MainMenuScreen();

}

int main()
{
	stInfos inf;
	LoginScreen();
