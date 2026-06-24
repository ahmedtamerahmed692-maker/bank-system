#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTransferScreen.h"
#include "clsTransactionLogscreen.h"
#include "clsBankClient.h"
#include "clsTotalBalancesScreen.h"
#include <iomanip>

using namespace std;

class clsTransactionsScreen :protected clsScreen
{


private:
    enum enTransactionsMenueOptions {
        eDeposit = 1, eWithdraw = 2, eTransfer = 3,
        eShowTotalBalance = 4, eShowTransactionLog = 5,
        eShowMyTransactions = 6, eShowMainMenue = 7
    };

    static short ReadTransactionsMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 7]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 7, "Enter Number between 1 to 7? ");
        return Choice;
    }


    static void _ShowDepositScreen()
    {
        clsDepositScreen::ShowDepositScreen();
    }

    static void _ShowWithdrawScreen()
    {
        clsWithdrawScreen::ShowWithdrawScreen();
    }
    static void _ShowTransferScreen()
    {
        clsTransferScreen::ShowTransferScreen();
    }

    static void _ShowTotalBalancesScreen()
    {
        clsTotalBalancesScreen::ShowTotalBalances();
    }

    static void _ShowTransactionLogScreen()
    {
        clsTransactionLogScreen::ShowAllTransactions();
    }

    static void _ShowMyTransactionsScreen()
    {
        _DrawScreenHeader("\t  My Transactions");
        cout << "\nEnter Account Number: ";
        string AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number not found! Enter again: ";
            AccountNumber = clsInputValidate::ReadString();
            
        }
        system("cls");

        clsTransactionLogScreen::ShowAccountTransactions(AccountNumber);
    }

    static void _GoBackToTransactionsMenue()
    {
        cout << "\n\nPress any key to go back to Transactions Menue...";
        system("pause>0");
        ShowTransactionsMenue();

    }
    static void _PerformTransactionsMenueOption(enTransactionsMenueOptions TransactionsMenueOption)
    {
        system("cls");
        switch (TransactionsMenueOption)
        {
        case enTransactionsMenueOptions::eDeposit:
            _ShowDepositScreen();
            break;
        case enTransactionsMenueOptions::eWithdraw:
            _ShowWithdrawScreen();
            break;
        case enTransactionsMenueOptions::eTransfer:
            _ShowTransferScreen();
            break;
        case enTransactionsMenueOptions::eShowTotalBalance:
            _ShowTotalBalancesScreen();
            break;
        case enTransactionsMenueOptions::eShowTransactionLog:
            _ShowTransactionLogScreen();
            break;
        case enTransactionsMenueOptions::eShowMyTransactions:
            _ShowMyTransactionsScreen();
            break;
        case enTransactionsMenueOptions::eShowMainMenue:
            break;
        }

        if (TransactionsMenueOption != enTransactionsMenueOptions::eShowMainMenue)
            _GoBackToTransactionsMenue();
    }



public:


    static void ShowTransactionsMenue()
    {

        if (!CheckAccessRights(clsUser::enPermissions::pTranactions))
        {
            return;// this will exit the function and it will not continue
        }
        system("cls");
        _DrawScreenHeader("\t  Transactions Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Transactions Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit.\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
        cout << setw(37) << left << "" << "\t[3] Transfer Money(Client to Client).\n";
        cout << setw(37) << left << "" << "\t[4] Total Balances.\n";
        cout << setw(37) << left << "" << "\t[5] Transaction Log.\n";
        cout << setw(37) << left << "" << "\t[6] My Transactions.\n";
        cout << setw(37) << left << "" << "\t[7] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformTransactionsMenueOption((enTransactionsMenueOptions)ReadTransactionsMenueOption());
    }

};
