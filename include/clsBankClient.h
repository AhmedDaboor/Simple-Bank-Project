#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>
#include "Global.h"
#include "clsDate.h"
#include "clsUtil.h"

using namespace std;
class clsBankClient : public clsPerson {
private:

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode _Mode;

    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;
    bool _MarkedForDelete = false;

    struct stTrnsferLogRecord;
    static stTrnsferLogRecord _ConvertTransferLogLineToRecord(string Line, string Seperator = "#//#") {

        stTrnsferLogRecord TransferLog;

        vector <string> LoginRegisterDataLine = clsString::Split(Line, Seperator);
        TransferLog.DateTime = LoginRegisterDataLine[0];
        TransferLog.SourceAccountNumber = LoginRegisterDataLine[1];
        TransferLog.DestinationAccountNumber = LoginRegisterDataLine[2];
        TransferLog.Amount = stod(LoginRegisterDataLine[3]);
        TransferLog.srcBalanceAfter = stod(LoginRegisterDataLine[4]);
        TransferLog.destBalanceAfter = stod(LoginRegisterDataLine[5]);


        return TransferLog;
    }

    static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#") {
        vector<string> vClientData;
        vClientData = clsString::Split(Line, Seperator);

        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
            vClientData[3], vClientData[4], clsUtil::Decrypt(vClientData[5]), stod(vClientData[6]));

    }

    static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#") {

        string stClientRecord = "";
        stClientRecord += Client.FirstName + Seperator;
        stClientRecord += Client.LastName + Seperator;
        stClientRecord += Client.Email + Seperator;
        stClientRecord += Client.Phone + Seperator;
        stClientRecord += Client.AccountNumber() + Seperator;
        stClientRecord += clsUtil::Encrypt(Client.PinCode) + Seperator;
        stClientRecord += to_string(Client.AccountBalance);

        return stClientRecord;

    }

    static  vector <clsBankClient> _LoadClientsDataFromFile() {

        vector <clsBankClient> vClients;

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open()) {

            string Line;

            while (getline(MyFile, Line)) {

                clsBankClient Client = _ConvertLinetoClientObject(Line);

                vClients.push_back(Client);
            }

            MyFile.close();
        }

        return vClients;
    }

    static void _SaveCleintsDataToFile(vector <clsBankClient> vClients) {

        fstream MyFile;
        MyFile.open("Clients.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open()) {

            for (clsBankClient& C : vClients) {
                if (C.MarkedForDeleted() == false) {
                    //we only write records that are not marked for delete.  
                    DataLine = _ConverClientObjectToLine(C);
                    MyFile << DataLine << endl;

                }

            }

            MyFile.close();

        }

    }

    void _Update() {
        vector <clsBankClient> _vClients;
        _vClients = _LoadClientsDataFromFile();

        for (clsBankClient& C : _vClients) {
            if (C.AccountNumber() == AccountNumber()) {
                C = *this;
                break;
            }

        }

        _SaveCleintsDataToFile(_vClients);

    }

    void _AddNew() {

        _AddDataLineToFile(_ConverClientObjectToLine(*this));
    }

    void _AddDataLineToFile(string  stDataLine) {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out | ios::app);

        if (MyFile.is_open()) {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    static clsBankClient _GetEmptyClientObject() {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    string _PrepareTransferLogRecord(clsBankClient DestinationClient, double Amount, string Seperator = "#//#") {
        string LoginRecord = "";
        LoginRecord += clsDate::DateToString(clsDate());
        LoginRecord += " - " + clsDate::TimeToString(clsDate()) + Seperator;
        LoginRecord += AccountNumber() + Seperator;
        LoginRecord += DestinationClient.AccountNumber() + Seperator;
        LoginRecord += to_string(Amount) + Seperator;
        LoginRecord += to_string(AccountBalance) + Seperator;
        LoginRecord += to_string(DestinationClient.AccountBalance) + Seperator;
        LoginRecord += CurrentUser.UserName;
        return LoginRecord;
    }

    void _RegisterTransferLog(clsBankClient DestinationClient, double Amount) {

        string stDataLine = _PrepareTransferLogRecord(DestinationClient, Amount);

        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::out | ios::app);

        if (MyFile.is_open()) {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

public:

    struct stTrnsferLogRecord {
        string DateTime;
        string SourceAccountNumber;
        string DestinationAccountNumber;
        double Amount;
        double srcBalanceAfter;
        double destBalanceAfter;
    };


    clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, float AccountBalance) :
        clsPerson(FirstName, LastName, Email, Phone) {

        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;

    }

    bool IsEmpty() {
        return (_Mode == enMode::EmptyMode);
    }

    bool MarkedForDeleted() {
        return _MarkedForDelete;
    }

    string AccountNumber() {
        return _AccountNumber;
    }

    void SetPinCode(string PinCode) {
        _PinCode = PinCode;
    }

    string GetPinCode() {
        return _PinCode;
    }
   
    __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;
    void SetAccountBalance(float AccountBalance) {
        _AccountBalance = AccountBalance;
    }

    float GetAccountBalance() {
        return _AccountBalance;
    }
    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

    static clsBankClient Find(string AccountNumber)  {

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open()) {
            string Line;
            while (getline(MyFile, Line)) {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber) {
                    MyFile.close();
                    return Client;
                }

            }

            MyFile.close();
        }

        return _GetEmptyClientObject();
    }

    static clsBankClient Find(string AccountNumber, string PinCode) {

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open()) {
            string Line;
            while (getline(MyFile, Line)) {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode) {
                    MyFile.close();
                    return Client;
                }

            }

            MyFile.close();
        }
        return _GetEmptyClientObject();
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };
    enSaveResults Save() {

        switch (_Mode) {
        case enMode::EmptyMode: {
            if (IsEmpty()) {

                return enSaveResults::svFaildEmptyObject;
            }
        }

        case enMode::UpdateMode: {

            _Update();

            return enSaveResults::svSucceeded;

            break;
        }

        case enMode::AddNewMode: {
            //This will add new record to file or database
            if (clsBankClient::IsClientExist(_AccountNumber)) {
                return enSaveResults::svFaildAccountNumberExists;
            }
            else {
                _AddNew();

                //We need to set the mode to update after add new
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }

            break;
        }
        }
    }

    static bool IsClientExist(string AccountNumber) {

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        return (!Client1.IsEmpty());
    }

    bool Delete() {
        vector <clsBankClient> _vClients;
        _vClients = _LoadClientsDataFromFile();

        for (clsBankClient& C : _vClients) {
            if (C.AccountNumber() == _AccountNumber) {
                C._MarkedForDelete = true;
                break;
            }

        }

        _SaveCleintsDataToFile(_vClients);

        *this = _GetEmptyClientObject();

        return true;

    }

    static clsBankClient GetAddNewClientObject(string AccountNumber) {
        return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
    }

    static vector <clsBankClient> GetClientsList() {
        return _LoadClientsDataFromFile();
    }

    void Deposit(double Amount) {
        _AccountBalance += Amount;
        Save();
    }

    bool Withdraw(double Amount) {
        if (Amount <= AccountBalance) {
            _AccountBalance -= Amount;
            Save();
            return true;
        }
        else {
            return false;
        }
    }

    bool Transfer(double Amount, clsBankClient& DestinationClient) {

        if (Amount > AccountBalance) {
            return false;
        }
        Withdraw(Amount);
        DestinationClient.Deposit(Amount);
        _RegisterTransferLog(DestinationClient, Amount);
        return true;
    
    }

    static double GetTotalBalances() {
        vector <clsBankClient> vClients = clsBankClient::GetClientsList();

        double TotalBalances = 0;

        for (clsBankClient &Client : vClients) {
            TotalBalances += Client.AccountBalance;
        }

        return TotalBalances;
    }

    static  vector <stTrnsferLogRecord> GetTransfersLogList() {
        vector <stTrnsferLogRecord> vTransferLogRecord;

        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::in);//read Mode

        if (MyFile.is_open()) {

            string Line;
            stTrnsferLogRecord TransferRecord;
            while (getline(MyFile, Line)) {

                TransferRecord = _ConvertTransferLogLineToRecord(Line);

                vTransferLogRecord.push_back(TransferRecord);
            }

            MyFile.close();
        }

        return vTransferLogRecord;
    }

};

