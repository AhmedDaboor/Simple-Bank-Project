#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"


// Class to handle the functionality of deleting a client in the system.
class clsDeleteClientScreen :protected clsScreen {
private:
    static void _PrintClient(clsBankClient Client) {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";
    }

public: 

    static void ShowDeleteClientScreen() {

        // Check if the user has the necessary permissions to delete a client. 
        if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient))
            return;// this will exit the function and it will not continue

        _DrawScreenHeader("\tDelete Client Screen");

        string AccountNumber = "";

        cout << "\nPlease Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExist(AccountNumber)) {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _PrintClient(Client1);
        
        char Answer = 'n';
        cout << "\nAre you sure you want to delete this client y/n? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y') {
            if (Client1.Delete()) {
                cout << "\nClient Deleted Successfully :-)\n";
                _PrintClient(Client1);
            }
            else {
                cout << "\nError Client Was not Deleted\n";
            }
        }
    }

};

