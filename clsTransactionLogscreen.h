#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsTransactionLog.h"

class clsTransactionLogScreen : protected clsScreen
{
private:
    static string _GetTypeName(clsTransactionLog::enTransactionType Type)
    {
        switch (Type)
        {
        case clsTransactionLog::eDeposit:   return "Deposit";
        case clsTransactionLog::eWithdraw:  return "Withdraw";
        case clsTransactionLog::eTransfer:  return "Transfer";
        default: return "Unknown";
        }
    }

    static void _PrintTransactionLine(clsTransactionLog& T)
    {
        cout << setw(8) << left << "" << "| " << setw(15) << left << T.FromAccount;
        cout << "| " << setw(15) << left << T.ToAccount;
        cout << "| " << setw(12) << left << T.Amount;
        cout << "| " << setw(12) << left << _GetTypeName(T.Type);
        cout << "| " << setw(20) << left << T.DateTime;
        cout << "| " << setw(12) << left << T.UserName;
    }

public:
    static void ShowAllTransactions()
    {
        vector<clsTransactionLog> vLogs = clsTransactionLog::GetTransactionsList();

        string Title = "\t  Transactions Log";
        string SubTitle = "\t    (" + to_string(vLogs.size()) + ") Transaction(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(15) << "From Account";
        cout << "| " << left << setw(15) << "To Account";
        cout << "| " << left << setw(12) << "Amount";
        cout << "| " << left << setw(12) << "Type";
        cout << "| " << left << setw(20) << "Date/Time";
        cout << "| " << left << setw(12) << "User";

        cout << setw(8) << left << "" << "\n\t_______________________________________________________________________________________\n" << endl;

        if (vLogs.size() == 0)
            cout << "\t\t\t\tNo Transactions Available!";
        else
        {
            for (clsTransactionLog& T : vLogs)
            {
                _PrintTransactionLine(T);
                cout << endl;
            }
        }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________________________________________\n" << endl;
    }

    static void ShowAccountTransactions(string AccountNumber)
    {
        vector<clsTransactionLog> vLogs = clsTransactionLog::GetTransactionsForAccount(AccountNumber);

        string Title = "\t  Account Transactions";
        string SubTitle = "\t    Account: " + AccountNumber;

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(15) << "From Account";
        cout << "| " << left << setw(15) << "To Account";
        cout << "| " << left << setw(12) << "Amount";
        cout << "| " << left << setw(12) << "Type";
        cout << "| " << left << setw(20) << "Date/Time";
        cout << "| " << left << setw(12) << "User";

        cout << setw(8) << left << "" << "\n\t_______________________________________________________________________________________\n" << endl;

        if (vLogs.size() == 0)
            cout << "\t\t\t\tNo Transactions for this Account!";
        else
        {
            for (clsTransactionLog& T : vLogs)
            {
                _PrintTransactionLine(T);
                cout << endl;
            }
        }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________________________________________\n" << endl;
    }
};