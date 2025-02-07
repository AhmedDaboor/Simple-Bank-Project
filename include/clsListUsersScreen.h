#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>

/**
 * @class clsListUsersScreen
 * @brief Represents the screen used to list users in the system.
 *
 * This class is responsible for displaying a list of users with their details such as username, full name,
 * phone number, email, password, and permissions. It interacts with the clsUser class to retrieve the list
 * of users and display it on the screen.
 */
class clsListUsersScreen : protected clsScreen {
private:

    static void _PrintUserRecordLine(clsUser User) {
        // Format and display each user's data in a tabular format for better readability
        cout << setw(8) << left << "" << "| " << setw(12) << left << User.UserName;
        cout << "| " << setw(25) << left << User.FullName();
        cout << "| " << setw(12) << left << User.Phone;
        cout << "| " << setw(20) << left << User.Email;
        cout << "| " << setw(10) << left << User.Password;
        cout << "| " << setw(12) << left << User.Permissions;
    }

public:

    /**
     * @brief Displays the list of all users in the system.
     *
     * This method retrieves the list of users using the clsUser class and displays each user's information
     * in a well-formatted table. If no users are found, a message indicating this is displayed to the user.
     *
     * @note This method assumes that the user has the appropriate permissions to view the list of users.
     */
    static void ShowUsersList() {

        // Retrieve the list of users from the clsUser class.
        vector<clsUser> vUsers = clsUser::GetUsersList();

        string Title = "\t  User List Screen";
        string SubTitle = "\t    (" + to_string(vUsers.size()) + ") User(s).";

        _DrawScreenHeader(Title, SubTitle);

        // Output the header row for the user table.
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(12) << "UserName";
        cout << "| " << left << setw(25) << "Full Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(12) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        // Check if there are any users to display.
        if (vUsers.size() == 0)
            cout << "\t\t\t\tNo Users Available In the System!";
        else
            // Loop through each user and print their information.
            for (clsUser User : vUsers) {
                _PrintUserRecordLine(User);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;
    }

};
