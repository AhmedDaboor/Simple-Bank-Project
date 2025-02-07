#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsTrnsferScreen : protected clsScreen {

	static void PrintClientCard(clsBankClient Client) {

		cout << "\n" << "Client card: ";

		cout << "\n________________________________\n";
		cout << "Full name      : " << Client.FullName() << "\n";
		cout << "Account number : " << Client.AccountNumber() << "\n";
		cout << "Account balance: " << Client.AccountBalance;
		cout << "\n________________________________" << endl;

	}

	static string _ReadAccountNumber(string message = "") {
		string AccountNumber = "";
		cout << "\n" << message;
		cin >> AccountNumber;
		return AccountNumber;
	}

	static clsBankClient FindClientByAccountNumber(string message = "") {
		string AccountNumber = _ReadAccountNumber(message);

		while (!clsBankClient::IsClientExist(AccountNumber)) {
			cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
			AccountNumber = _ReadAccountNumber(message);
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		
		return Client;
	}

public:

	static void ShowTrnsferScreen() {

		_DrawScreenHeader("\t   Transfer Screen");

		clsBankClient SourceClient = FindClientByAccountNumber("Please enter accout number to transfer from: ");
		PrintClientCard(SourceClient);
			
		clsBankClient DestinationClient = FindClientByAccountNumber("Please enter accout number to transfer to: ");
		
		if (SourceClient.AccountNumber() != DestinationClient.AccountNumber())
			PrintClientCard(DestinationClient);
		else {
			DestinationClient = FindClientByAccountNumber("Error: You cannot transfer to your own account. Please enter a different account number: ");
		}

		double Amount;
		cout << "Enter transfer amount: ";
		Amount = clsInputValidate::ReadDblNumber();
		
		while (SourceClient.AccountBalance < Amount) {
			cout << "\nAmount exceed the available balance, Enter anouther Amount: ";
			Amount = clsInputValidate::ReadDblNumber();
		}

		char Answer;
		cout << "\nAre you sure you want to perform this operation?? (Y/N)? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y') {
			if (SourceClient.Transfer(Amount, DestinationClient)) {
				cout << "\nTranfer done successfully.";
			}
			else
				cout << "\nTransfer failed. Please check your balance or try again.";
		}
		else {
			cout << "\nOperation canceled. The amount has been deposited back.";
		}
		PrintClientCard(SourceClient); 
		PrintClientCard(DestinationClient);
		

	}

};

