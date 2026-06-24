#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "clsString.h"
#include "clsDate.h"

using namespace std;

class clsTransactionLog
{
public:
    enum enTransactionType { eDeposit = 0, eWithdraw = 1, eTransfer = 2 };

private:
    string _FromAccount;
    string _ToAccount;
    double _Amount;
    enTransactionType _Type;
    string _DateTime;
    string _UserName;

    static clsTransactionLog _ConvertLineToTransaction(string Line, string Seperator = "#//#")
    {
        vector<string> vData;
        vData = clsString::Split(Line, Seperator);

        string UserName = (vData.size() >= 6) ? vData[5] : "N/A";

        return clsTransactionLog(vData[0], vData[1],
            stod(vData[2]), (enTransactionType)stoi(vData[3]), vData[4], UserName);
    }

    static string _ConvertTransactionToLine(clsTransactionLog T, string Seperator = "#//#")
    {
        string Record = "";
        Record += T._FromAccount + Seperator;
        Record += T._ToAccount + Seperator;
        Record += to_string(T._Amount) + Seperator;
        Record += to_string(T._Type) + Seperator;
        Record += T._DateTime + Seperator;
        Record += T._UserName;
        return Record;
    }

    static vector<clsTransactionLog> _LoadDataFromFile()
    {
        vector<clsTransactionLog> vLogs;
        fstream MyFile;
        MyFile.open("Transactions.txt", ios::in);

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                if (Line == "")
                    continue;

                clsTransactionLog Log = _ConvertLineToTransaction(Line);
                vLogs.push_back(Log);
            }
            MyFile.close();
        }
        return vLogs;
    }

    static void _AddToFile(string Line)
    {
        fstream MyFile;
        MyFile.open("Transactions.txt", ios::out | ios::app);
        if (MyFile.is_open())
        {
            MyFile << Line << endl;
            MyFile.close();
        }
    }

public:
    clsTransactionLog(string FromAccount, string ToAccount,
        double Amount, enTransactionType Type, string UserName)
    {
        _FromAccount = FromAccount;
        _ToAccount = ToAccount;
        _Amount = Amount;
        _Type = Type;
        _UserName = UserName;
        _DateTime = clsDate::GetSystemDateTimeString();
    }

    clsTransactionLog(string FromAccount, string ToAccount,
        double Amount, enTransactionType Type, string DateTime, string UserName)
    {
        _FromAccount = FromAccount;
        _ToAccount = ToAccount;
        _Amount = Amount;
        _Type = Type;
        _DateTime = DateTime;
        _UserName = UserName;
    }

    string GetFromAccount() { return _FromAccount; }
    __declspec(property(get = GetFromAccount)) string FromAccount;

    string GetToAccount() { return _ToAccount; }
    __declspec(property(get = GetToAccount)) string ToAccount;

    double GetAmount() { return _Amount; }
    __declspec(property(get = GetAmount)) double Amount;

    enTransactionType GetType() { return _Type; }
    __declspec(property(get = GetType)) enTransactionType Type;

    string GetDateTime() { return _DateTime; }
    __declspec(property(get = GetDateTime)) string DateTime;

    string GetUserName() { return _UserName; }
    __declspec(property(get = GetUserName)) string UserName;

    void Save()
    {
        _AddToFile(_ConvertTransactionToLine(*this));
    }

    static vector<clsTransactionLog> GetTransactionsList()
    {
        return _LoadDataFromFile();
    }

    static vector<clsTransactionLog> GetTransactionsForAccount(string AccountNumber)
    {
        vector<clsTransactionLog> vAll = GetTransactionsList();
        vector<clsTransactionLog> vResult;

        for (clsTransactionLog& T : vAll)
        {
            if (T.FromAccount == AccountNumber || T.ToAccount == AccountNumber)
                vResult.push_back(T);
        }
        return vResult;
    }
};