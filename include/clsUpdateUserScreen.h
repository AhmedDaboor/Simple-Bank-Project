#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsUpdateUserScreen :protected clsScreen {
private:
    static void _ReadUserInfo(clsUser& User) {
        cout << "\nEnter FirstName: ";
        User.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        User.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        User.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        User.Phone = clsInputValidate::ReadString();

        cout << "\nEnter Password: ";
        User.Password = clsInputValidate::ReadString();

        cout << "\nEnter Permission: ";
        User.Permissions = _ReadPermissionsToSet();
    }

    static void _PrintUser(clsUser User) {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.FirstName;
        cout << "\nLastName    : " << User.LastName;
        cout << "\nFull Name   : " << User.FullName();
        cout << "\nEmail       : " << User.Email;
        cout << "\nPhone       : " << User.Phone;
        cout << "\nUser Name   : " << User.UserName;
        cout << "\nPassword    : " << User.Password;
        cout << "\nPermissions : " << User.Permissions;
        cout << "\n___________________\n";

    }

    static int _ReadPermissionsToSet() {
        int Permissions = 0;
        char Answer = 'n';

        cout << "\nDo you want to give full access? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
            return -1;

        cout << "\nDo you want to give access to : \n ";

        cout << "\nShow Client List? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
            Permissions += clsUser::enPermissions::pListClients;

        cout << "\nAdd New Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
            Permissions += clsUser::enPermissions::pAddNewClient;

        cout << "\nDelete Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
            Permissions += clsUser::enPermissions::pDeleteClient;

        cout << "\nUpdate Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
            Permissions += clsUser::enPermissions::pUpdateClients;

        cout << "\nFind Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
            Permissions += clsUser::enPermissions::pFindClient;

        cout << "\nTransactions? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
            Permissions += clsUser::enPermissions::pTranactions;

        cout << "\nManage Users? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
            Permissions += clsUser::enPermissions::pManageUsers;

        return Permissions;

    }

public:

    /**
    * @brief Displays the screen for updating an existing user's information.
    *
    * This function provides an interface to update user information in the system.
    * It first prompts the administrator to enter the username of the user whose information
    * needs to be updated. The user is validated to ensure that they exist, after which the
    * user details are displayed. The administrator is then asked for confirmation to proceed with
    * the update, and the new user information is saved if confirmed.
    */
    static void ShowUpdateUserScreen() {

        _DrawScreenHeader("\tUpdate User Screen");

        string UserName = "";

        cout << "\nPlease Enter User UserName: ";
        UserName = clsInputValidate::ReadString();

        while (!clsUser::IsUserExist(UserName)) {
            cout << "\nAccount number is not found, choose another one: ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser User1 = clsUser::Find(UserName);

        _PrintUser(User1);

        cout << "\nAre you sure you want to update this User y/n? ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y') {

            cout << "\n\nUpdate User Info:";
            cout << "\n____________________\n";

            _ReadUserInfo(User1);

            // Attempt to save the updated user information
            clsUser::enSaveResults SaveResult;
            SaveResult = User1.Save();

            // Handle different save results
            switch (SaveResult) {
            case clsUser::enSaveResults::svSucceeded: {
                cout << "\nUser Updated Successfully :-)\n";
                _PrintUser(User1);
                break;
            }
            case clsUser::enSaveResults::svFaildEmptyObject: {
                cout << "\nError: User was not saved because it's empty";  // Error if user info is incomplete
                break;
            }
            }
        }
    }

};

