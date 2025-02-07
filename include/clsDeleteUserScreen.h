#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsDeleteUserScreen :protected clsScreen  {
private:
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

public:
    /**
     * @brief Displays the screen for deleting a user.
     *
     * This function allows an administrator to delete a user from the system. It prompts the administrator
     * to enter the username of the user they wish to delete. It checks if the user exists, then displays
     * the user's details and asks for confirmation before proceeding with the deletion.
     */
    static void ShowDeleteUserScreen() {

        _DrawScreenHeader("\tDelete User Screen");

        string UserName = "";

        cout << "\nPlease Enter UserName: ";
        UserName = clsInputValidate::ReadString();
        while (!clsUser::IsUserExist(UserName)) {
            cout << "\nUser is not found, choose another one: ";
            UserName = clsInputValidate::ReadString(); 
        }

        clsUser User1 = clsUser::Find(UserName);

        _PrintUser(User1);

        cout << "\nAre you sure you want to delete this User y/n? ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            // Attempt to delete the user and provide feedback
            if (User1.Delete())  // If the deletion is successful
            {
                cout << "\nUser Deleted Successfully :-)\n";
                _PrintUser(User1);
            }
            else
            {
                cout << "\nError: User Was not Deleted\n";
            }
        }
    }


};

