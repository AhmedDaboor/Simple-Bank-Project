#pragma once

#include <iostream>
#include <fstream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "Global.h"
#include "clsDate.h"
#include "clsUtil.h"

class clsLoginScreen :protected clsScreen {
private:

    static  bool _Login() {
        bool LoginFaild = false;
        short count = 0;
        string Username, Password;
        do  {

            if (LoginFaild) {
                count++;
                cout << "\nInvlaid Username/Password!\n\n";
            }
            
            if (count == 3)
                return false;

            cout << "Enter Username? ";
            cin >> Username;

            cout << "Enter Password? ";
            cin >> Password;

            // If the username and password are correct, an object containing the corresponding data is returned, 
            // otherwise, an empty object is returned.
            CurrentUser = clsUser::Find(Username, Password);

            // Returns true if the object is empty, otherwise returns false.
            LoginFaild = CurrentUser.IsEmpty();

            
        } while (LoginFaild && count < 3);
        
        CurrentUser.RegisterLogIn();
        
        clsMainScreen::ShowMainMenue();
        return true;
    }
    
public:

    static bool ShowLoginScreen() {
        system("cls");
        _DrawScreenHeader("\t  Login Screen");
        
        return _Login();
    }

};