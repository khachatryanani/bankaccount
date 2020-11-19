#include "json.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;
using json = nlohmann::json;


class BankAccount
{
public:
	BankAccount(){};
	BankAccount(json &outerJSON)
	{
		customerJ = outerJSON;
	}
	void AddAmount()
	{
		string add;
		cout << "Type in the amount you want to add to your account: ";
		cin >> add;
		customerJ["current amount"] = customerJ["current amount"].get<double>() + stod(add);
		cout << "Transaction completed successfully!\nCurrent amount = "<< customerJ["current amount"]<<endl;
	}
	void WithdrawAmount()
	{
		string withdraw;
		cout << "Type in the amount you want to withdraw from your account: ";
		cin >> withdraw;
		if (stod(withdraw) <  customerJ["current amount"])
		{
			customerJ["current amount"] = customerJ["current amount"].get<double>() - stod(withdraw);
			cout << "Transaction completed successfully!\nCurrent amount = " << customerJ["current amount"] << endl;
		}
		else
		{
			cout << "Unable to complete the transaction: no enough amount\n";
		}
	}
	void CheckCurrentAmount()
	{
		cout << "The current amount of your account: " << customerJ["current amount"] << endl;
	}
	void DisplayAccountInfo() 
	{
		cout << "Full Name: " << customerJ["first name"].get<string>()<< " "<<customerJ["last name"].get<string>() << endl;
		cout << "Address: " << customerJ["customer address"].get<string>() << endl;
		cout << "Current amount available to dispose: $" << customerJ["current amount"] << endl;
	}
	void UpdateAccountInfo( char userChoice, string UserUpdate) 
	{
			switch (userChoice)
			{
			case '1':
				customerJ["first name"] = UserUpdate;
				break;
			case '2':
				customerJ["last name"] = UserUpdate;
				break;
			case '3':
				customerJ["customer address"] = UserUpdate;
				break;
			default:
				break;
			}
			cout << "Data successfully updated!\n";
			DisplayAccountInfo();
	}
	json GetCustomerJSON()
	{
		return customerJ;
	}
private:
	json customerJ;
};


