#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"

class clsCurrencyExchangeScreen : protected clsScreen {

private:

	enum enCurrencyExchange { eListCurrencies = 1, eFindCurrency, eUpdateRate, eCurrencyCalculator, eExit };

	static short _ReadCurrencyMenueOption() {
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 5, "Enter Number between 1 to 5? ");
		return Choice;
	}

	static  void _GoBackToCurrencyExchangeMenue() {
		cout << setw(37) << left << "" << "\n\tPress any key to go back to currency Exchange Menue...";

		system("pause>0");
		ShowCurrencyExchangeMenu();
	}

	static void _ShowListCurrencyScreen() {
		// List currency will be here...
		clsCurrenciesListScreen::ShowCurrenciesListScreen();
	}

	static void _ShowFindCurrencyScreen() {
		// Find Currency Will be here...
		clsFindCurrencyScreen::ShowFindCurrencyScreen();
	}

	static void _ShowUpdateCurrencyScreen() {
		// Update currency screen will be here...
		clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
	}

	static void _ShowCurrencyCalculatorScreen() {
		// Currency Calculator Screen Will be here...
		clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
	}

	static void _PerfromCurrencyMenueOption(enCurrencyExchange CurrencyMenueOption){

		switch (CurrencyMenueOption) {

		case clsCurrencyExchangeScreen::eListCurrencies:
			system("cls");
			_ShowListCurrencyScreen();
			_GoBackToCurrencyExchangeMenue();
			break;
		case clsCurrencyExchangeScreen::eFindCurrency:
			system("cls");
			_ShowFindCurrencyScreen();
			_GoBackToCurrencyExchangeMenue();
			break;
		case clsCurrencyExchangeScreen::eUpdateRate:
			system("cls");
			_ShowUpdateCurrencyScreen();
			_GoBackToCurrencyExchangeMenue();
			break;
		case clsCurrencyExchangeScreen::eCurrencyCalculator:
			system("cls");
			_ShowCurrencyCalculatorScreen();
			_GoBackToCurrencyExchangeMenue();
			break;
		case clsCurrencyExchangeScreen::eExit:
			// do nothing here the main screen will handle it :-) 
			break;
		}
	}

public:

	static void ShowCurrencyExchangeMenu() {
		system("cls");
		_DrawScreenHeader("\t\tCurrency Screen");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t\tCurrency Menu\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
		cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
		cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
		cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
		cout << setw(37) << left << "" << "\t[5] Main Menu.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		_PerfromCurrencyMenueOption((enCurrencyExchange)_ReadCurrencyMenueOption());
	}


};

