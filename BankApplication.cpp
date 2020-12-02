#include <fstream>
#include <iostream>
#include <iomanip>
#include "Banking.h"

using namespace std;

int main()
{
	Bank b = Bank();
	char choice;	
	do 
	{
		choice = b.GetUserChoice();
		switch (choice)
		{
		case '1':
			system("cls");
			b.UserToCreateAccount();
			system("cls");
			break;
		case '2':
			system("cls");
			b.UserToUpdateAccountInfo();
			system("cls");
			break;
		case '3':
			system("cls");
			b.UserToPerformTransaction();
			system("cls");
			break;
		case '4':
			system("cls");
			b.UserToCheckAccountInfo();
			system("cls");
			break;
		case '5':
			system("cls");
			b.UserToRemoveAccount();
			system("cls");
			break;
		case '6':
			system("cls");
			b.UserToSeeCustomersList();
			system("cls");
			break;
		case'7':
			system("cls");
			cout << "You've exited the application!";
			break;
		default:
			system("cls");
			cout << "Please choose from the options below\n";
		}
	} 
	while (choice != '7');
}

