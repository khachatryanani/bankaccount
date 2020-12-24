#include "json.hpp"
#include "Banking.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;
using json = nlohmann::json;

Bank::Bank()
	{
		CreateBankInfo();
		CreateBankDB();
	};
Bank::~Bank(){}
void Bank::UserToCreateAccount()
	{
		BankAccount bkAccount = CreateBankAccount(GetAndReturnUserInfo());
		CollectConsoleGarbage();
		ReturnToMenu();
	}
void Bank::UserToRemoveAccount()
	{
		json CustomerFromDB = FindCustomer();
		BankAccount bkAccount = BankAccount(CustomerFromDB[0]);
		system("cls");
		cout << "See below your account.\n";
		bkAccount.DisplayAccountInfo();
		cout << "Are your sure you want to remove this account? Y/n: ";
		if (GetUserInput() == "Y") 
		{
			for (unsigned int i = 0; i < _bankDB["customers"].size(); i++)
			{
				if (_bankDB["customers"][i][1]["customer ID"]==CustomerFromDB[1]["customer ID"])
				{
					_bankDB["customers"][i] = nullptr;
				}
			}
			cout << "Account is successfully removed.\n";
		};
		ReturnToMenu();
		ArchiveBank();
	}
void Bank::UserToPerformTransaction()
	{
		json CustomerFromDB = FindCustomer();
		BankAccount bkAccount = BankAccount(CustomerFromDB[0]);
		system("cls");
		cout << "You are in the system.\n";
		char transactionChoice;
		do {
			cout << "You want to perform a transaction.\nPlease choose one of the option below.\n1. Add amount to my account.\n2. Withdraw amount from my account.\n3.Exit option\n";
			cin >> transactionChoice;
			switch (transactionChoice) 
			{
			case '1':
				system("cls");
				bkAccount.AddAmount();
				CollectConsoleGarbage();
				PressToContinue();
				system("cls");
				break;
			case '2':
				system("cls");
				bkAccount.WithdrawAmount();
				CollectConsoleGarbage();
				PressToContinue();
				system("cls");
				break;
			default:
				system("cls");
			}
		} while (transactionChoice != '3');
		CustomerFromDB[0] = bkAccount.GetCustomerJSON();
		UpdateCustomerAccountInDB(CustomerFromDB);
		//ReturnToMenu();
	}
void Bank::UserToCheckAccountInfo()
	{
		BankAccount bkAccount = BankAccount(FindCustomer()[0]);
		system("cls");
		cout << "You are in the system.\nSee below the information related to your bank account.\n";
		bkAccount.DisplayAccountInfo();
		CollectConsoleGarbage();
		ReturnToMenu();
	}
void Bank::UserToUpdateAccountInfo()
	{
		json CustomerFromDB = FindCustomer();
		BankAccount bkAccount = BankAccount(CustomerFromDB[0]);
		system("cls");
		char userChoice;
		string userUpdate;
		do
		{
			cout << "See below your account info.\n";
			bkAccount.DisplayAccountInfo();
			cout << "Please choose what data you want to update.\n1. First name\n2. Last name\n3. Address\n4.Exit Option\n";
			cin >> userChoice;
			switch (userChoice) 
			{
			case '1':
			case '2':
			case '3':
				system("cls");
				cout << "Type in the updated version: ";
				userUpdate = GetUserInput();
				bkAccount.UpdateAccountInfo(userChoice, userUpdate);
				PressToContinue();
				system("cls");
				break;
			default:
				system("cls");
				break;
			}
		} while (userChoice != '4');
		CustomerFromDB[0] = bkAccount.GetCustomerJSON();
		UpdateCustomerAccountInDB(CustomerFromDB);
		CollectConsoleGarbage();
		//ReturnToMenu();
	}
void Bank::UserToSeeCustomersList()
	{
		cout << "See below the list of current customers:\n";
		bool shown = false;
		for (unsigned int i = 0; i < _bankDB["customers"].size(); i++)
		{
			if (_bankDB["customers"][i]!=nullptr)
			{
				cout<<_bankDB["customers"][i][0]["first name"].get<string>()<<" "<< _bankDB["customers"][i][0]["last name"].get<string>()<<endl;
				shown = true;
			}
		}
		if (!shown) 
		{
			cout << "No customers to show.\n";
		}
		CollectConsoleGarbage();
		ReturnToMenu();
	}
BankAccount Bank::CreateBankAccount(json newUser)
	{
		BankAccount bkAccount = BankAccount(newUser);
		cout << "New Account is created with the following data:\n";
		bkAccount.DisplayAccountInfo();
		customerIDs++;
		AddCustomerAccountToDB(bkAccount.GetCustomerJSON());
		return bkAccount;
	}
json Bank::GetCustomerAccount(string fName, string lName, string password)
	{
		bool found = false;
		for (unsigned int i = 0; i < _bankDB["customers"].size(); i++)
		{
			if (_bankDB["customers"][i][0]["first name"] == fName &&
				_bankDB["customers"][i][0]["last name"] == lName &&
				_bankDB["customers"][i][0]["password"] == password)
			{
				found = true;
				return _bankDB["customers"][i];
			}
		}
		if (!found)
		{
			cout << "Not found:";
		}
	}
void Bank::UpdateCustomerAccountInDB(json account)
	{
		for (unsigned int i = 0; i < _bankDB["customers"].size(); i++)
		{
			if (account[1]["customer ID"] == _bankDB["customers"][i][1]["customer ID"])
			{
				_bankDB["customers"][i][0] = account[0];
			}
		}
		ArchiveBank();
	}
void Bank::AddCustomerAccountToDB(json j)
	{
		json customerID;
		customerID["customer ID"] = customerIDGenerator(customerIDs);
		_bankDB["customers"].push_back({ j, customerID });
		ArchiveBank();
	}
void Bank::ArchiveBank()
	{
		ofstream bankDB("bankDB.txt");
		bankDB << _bankDB.dump(4);
		bankDB.close();
		ofstream bankInfo("bankInfo.txt");
		json bnkInfo;
		bnkInfo["customer count"] = customerIDs;
		bankInfo << bnkInfo;
		bankInfo.close();
	}
json Bank::FindCustomer()
	{
		cout << "Please, enter your credentials.\n";
		CollectConsoleGarbage();
		string fName, lName, password;
		cout << "First Name: ";
		getline(cin, fName);
		cout << "Last Name: ";
		cout << skipws;
		getline(cin, lName);
		cout << "Password: ";
		cin >> password;
		return GetCustomerAccount(fName, lName, password);
	}
void Bank::CreateBankDB()
	{
		ifstream bankDB("bankDB.txt");
		if (bankDB.is_open())
		{
			bankDB >> _bankDB;
			bankDB.close();
		}
		else
		{
			_bankDB["customers"] = {};
			ofstream bankDB("bankDB.txt");
			bankDB << _bankDB;
			bankDB.close();
		}
	}
void Bank::CreateBankInfo()
	{
		ifstream bankInfo("bankInfo.txt");
		if (bankInfo.is_open())
		{
			json bnkInfo;
			bankInfo >> bnkInfo;
			customerIDs = bnkInfo["customer count"];
			bankInfo.close();
		}
		else
		{
			ofstream bankInfo("bankInfo.txt");
			json bnkInfo;
			bnkInfo["all customer count"] = customerIDs;
			bankInfo << bnkInfo;
			bankInfo.close();
		}
	}
string Bank::customerIDGenerator(int count)
	{
		int i = 8;
		string ID = to_string(count);
		while (ID.length() < 8)
		{
			ID = "0" + ID;
		}
		return ID;
	}
	


