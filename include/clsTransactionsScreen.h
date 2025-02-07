#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTrnsferScreen.h"
#include "clsTransferLogScreen.h"

using namespace std;

// The clsTransactionsScreen class is responsible for managing the transactions screen, 
// allowing users to deposit, withdraw, and view total balances. 
// It also handles navigation to the main menu and ensures proper access rights are checked before performing any transaction-related actions.
class clsTransactionsScreen :protected clsScreen {
private:
    enum enTransactionsMenueOptions {
        eDeposit = 1, eWithdraw = 2,
        eShowTotalBalance = 3, eTransfer = 4 , eTransferLog = 5 ,eShowMainMenue = 6
    };

    static short ReadTransactionsMenueOption() {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number between 1 to 6? ");
        return Choice;
    }

    static void _ShowDepositScreen() {
        // Deposit Screen will be here...
        clsDepositScreen::ShowDepositScreen();
    }

    static void _ShowWithdrawScreen() {
        // Withdraw Screen will be here...
        clsWithdrawScreen::ShowWithdrawScreen();
    }

    static void _ShowTotalBalancesScreen() {
        // Balances Screen will be here...
        clsTotalBalancesScreen::ShowTotalBalances();

    }

    static void _ShowTransferScreen() {
        // Transfer Screen will be here...
        clsTrnsferScreen::ShowTrnsferScreen();
    }

    static void _ShowTransferLogScreen() {
        // Transfer log Screen will be here...
        clsTransferLogScreen::ShowTransferLogScreen();
    }

    static void _GoBackToTransactionsMenue() {
        cout << "\n\nPress any key to go back to Transactions Menue...";
        system("pause>0");
        ShowTransactionsMenue();

    }

    static void _PerformTransactionsMenueOption(enTransactionsMenueOptions TransactionsMenueOption) {

        switch (TransactionsMenueOption) {
        case enTransactionsMenueOptions::eDeposit: {
            system("cls");
            _ShowDepositScreen();
            _GoBackToTransactionsMenue();
            break;
        }

        case enTransactionsMenueOptions::eWithdraw: {
            system("cls");
            _ShowWithdrawScreen();
            _GoBackToTransactionsMenue();
            break;
        }


        case enTransactionsMenueOptions::eShowTotalBalance: {
            system("cls");
            _ShowTotalBalancesScreen();
            _GoBackToTransactionsMenue();
            break;
        }

        case enTransactionsMenueOptions::eTransfer: {
            system("cls");
            _ShowTransferScreen();
            _GoBackToTransactionsMenue();
            break;
        }

        case enTransactionsMenueOptions::eTransferLog: {
            system("cls");
            _ShowTransferLogScreen();
            _GoBackToTransactionsMenue();
            break;
        }

        case enTransactionsMenueOptions::eShowMainMenue: {

            //do nothing here the main screen will handle it :-) ;
        }
        }
    }


public:

    static void ShowTransactionsMenue() {

        // Verify if the user has the necessary permissions to access transaction-related actions.
        if (!CheckAccessRights(clsUser::enPermissions::pTranactions))
            return;// this will exit the function and it will not continue

        system("cls");
        _DrawScreenHeader("\tTransactions Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Transactions Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit.\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
        cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
        cout << setw(37) << left << "" << "\t[4] Transfer.\n";
        cout << setw(37) << left << "" << "\t[5] Transfer log.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menue.\n"; 
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformTransactionsMenueOption((enTransactionsMenueOptions)ReadTransactionsMenueOption());
    }

};

