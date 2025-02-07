#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include <iomanip>

class clsAddNewUserScreen : protected clsScreen {
private:

    static void _ReadUserInfo(clsUser& User)
    {
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

    static void _PrintUser(clsUser User)
    {
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

    /**
     * @brief Allows the user to set permissions for the new user.
     *
     * This function presents a series of prompts to the user, asking whether to grant specific permissions to
     * the newly added user. The permissions are stored as a bitfield in the integer `Permissions`.
     *
     * @return The combined permissions value as an integer.
     */
    static int _ReadPermissionsToSet() {
        int Permissions = 0;
        char Answer = 'n';

        cout << "\nDo you want to give full access? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
            return -1;  // Full access is granted by setting the value to -1

        cout << "\nDo you want to give access to : \n";

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

        cout << "\nLogin user screen? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
            Permissions += clsUser::enPermissions::pLoginRegister;

        cout << "\nManage Users? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
            Permissions += clsUser::enPermissions::pManageUsers;

        return Permissions; // Return the total permissions set for the new user
    }

public:

    /**
     * @brief Displays the screen for adding a new user.
     *
     * This function handles the process of adding a new user to the system. It collects user details,
     * checks if the username is available, and saves the user to the system. If the user is successfully added,
     * their details are displayed on the screen.
     */
    static void ShowAddNewUserScreen() {
        _DrawScreenHeader("\t  Add New User Screen");

        string UserName = "";

        cout << "\nPlease Enter UserName: ";
        UserName = clsInputValidate::ReadString();
        while (clsUser::IsUserExist(UserName)) {
            cout << "\nUserName Is Already Used, Choose another one: ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser NewUser = clsUser::GetAddNewUserObject(UserName);

        _ReadUserInfo(NewUser);

        clsUser::enSaveResults SaveResult;

        // Attempt to save the user to the system
        SaveResult = NewUser.Save();

        // Handle the result of the save operation
        switch (SaveResult) {
        case  clsUser::enSaveResults::svSucceeded:
            cout << "\nUser Added Successfully :-)\n";
            _PrintUser(NewUser);
            break;
        case clsUser::enSaveResults::svFaildEmptyObject:
            cout << "\nError: User was not saved because it's Empty";
            break;
        case clsUser::enSaveResults::svFaildUserExists:
            cout << "\nError: User was not saved because the UserName is already taken!";
            break;
        }
    }

};
