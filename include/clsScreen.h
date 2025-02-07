#pragma once
#include <iostream>
#include "clsUser.h"
#include "Global.h"
#include "clsDate.h"

using namespace std;

class clsScreen {
protected:

     static void _DrawScreenHeader(string Title, string SubTitle = "") {

        cout << clsDate::DateToString(clsDate()) << "\t\t\t\t______________________________________\t\t\t\t" << CurrentUser.UserName;
        cout << "\n\n\t\t\t\t\t  " << Title;
        if (SubTitle != "") {
            cout << "\n\t\t\t\t\t  " << SubTitle;
        }
        cout << "\n\t\t\t\t\t______________________________________\n\n";
     }

    /**
     * @brief Checks the user's access rights and shows a denial message if needed
     * @param Permission The required permission type from the clsUser::enPermissions enumeration
     * @return true if the permission is available, false with an error message if not
     */
    static bool CheckAccessRights(clsUser::enPermissions Permission) {
        if (!CurrentUser.CheckAccessPermission(Permission)) {
            // Access Denied: User lacks sufficient permissions
            cout << "\n\t\t\t\t\t______________________________________"
                << "\n\n\t\t\t\t\t   Access Denied! Please contact the admin."
                << "\n\t\t\t\t\t______________________________________\n\n";
            return false; // Permission is not available
        }
        return true; // Permission granted successfully
    }


};

