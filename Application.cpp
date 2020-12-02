#include "json.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "Application.h"
using namespace std;
using json = nlohmann::json;


	string Application::GetUserInput()
	{
		string userInput;
		string consoleGarbage;
		getline(cin, consoleGarbage);
		getline(cin, userInput);
		return userInput;
	}
	json Application::GetAndReturnUserInfo()
	{
		cout << "You want to create a new account.\nPlease, enter your personal info.\n";
		string fName, lName, password, address, amount;
		CollectConsoleGarbage();
		cout << "First Name: ";
		getline(cin, fName);
		cout << "Last Name: ";
		cout << skipws;
		getline(cin, lName);
		cout << "Please, provide additional data on your address: ";
		cout << skipws;
		getline(cin, address);
		cout << "Create password (max 8 chars): ";
		cin >> password;
		cout << "You must put at list 1$ on your account to fully activate it!\nEnter your amount: ";
		cin >> amount;
		json newUser;
		newUser = 
		{
			{"first name",fName},
			{"last name",lName},
			{"password",password},
			{"customer address",address},
			{"current amount",stod(amount)}
		};
		return newUser;
	}
	char Application::GetUserChoice()
	{
		cout << "1. Create new account\n2. Update info on existing account\n3. Perform a transaction\n4. Check the details of existing account\n5. Remove existing account\n6. See the customers list\n7. Exit\n";
		char userChoice;
		cin >> userChoice;
		return userChoice;
	}
	void Application::ReturnToMenu()
	{
		string key;
		cout << "Press any key to return back to the main menu!";
		getline(cin, key);
	}
	void Application::PressToContinue()
	{
		string key;
		cout << "Press any key to continue!";
		getline(cin, key);
	}
	void Application::CollectConsoleGarbage()
	{
		string consoleGarbage;
		getline(cin, consoleGarbage);
	}

