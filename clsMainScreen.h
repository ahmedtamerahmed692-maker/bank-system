#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeletClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsers.h"
#include "clsLoginRegisterScreen.h"
#include "clsCurrencyExchangeMainScreen.h"
#include "Global.h"





using namespace std;

class clsMainScreen :protected clsScreen
{


private:
    enum enMainMenueOptions {
        eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
        eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6,
        eManageUsers = 7, eLoginRegister = 8, eCurrencyExchange = 9, eExit = 10
    };
private:
    static string _GetPermissionSymbol(clsUser::enPermissions Permission)
    {
        if (CurrentUser.CheckAccessPermission(Permission))
            return "\033[1;32m[✓]\033[0m   "; 
        else
            return "\033[1;31m[x]\033[0m   "; 
    }
    
    static short _ReadMainMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 10]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 10, "Enter Number between 1 to 10? ");
        return Choice;
    }

    static  void _GoBackToMainMenue()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";

        system("pause>0");
        ShowMainMenue();
    }

    static void _ShowAllClientsScreen()
    {
        clsClientListScreen::ShowClientsList();


    }

    static void _ShowAddNewClientsScreen()
    {
        clsAddNewClientScreen::ShowAddNewClientScreen();
    }

    static void _ShowDeleteClientScreen()
    {
        clsDeleteClientScreen::ShowDeleteClientScreen();
    }

    static void _ShowUpdateClientScreen()
    {
        clsUpdateClientScreen::ShowUpdateClientScreen();
    }

    static void _ShowFindClientScreen()
    {
        clsFindClientScreen::ShowFindClientScreen();
    }

    static void _ShowTransactionsMenue()
    {
        clsTransactionsScreen::ShowTransactionsMenue();
    }

    static void _ShowManageUsersMenue()
    {
        clsManageUsersScreen::ShowManageUsersMenue();
    }

    static void _ShowLoginRegisterScreen()
    {
        clsLoginRegisterScreen::ShowLoginRegisterScreen();

    }

    static void _ShowCurrencyExchangeMenue()
    {
        clsCurrencyExchangeMainScreen::ShowCurrenciesMenue();
    }

    static void _Logout()
    {

      clsUser CurrentUser = clsUser::GetEmptyUserObject();

    }
    static void _PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
    {
        system("cls");
        switch (MainMenueOption)
        {
        case enMainMenueOptions::eListClients:
            _ShowAllClientsScreen();
            break;
        case enMainMenueOptions::eAddNewClient:
            _ShowAddNewClientsScreen();
            break;
        case enMainMenueOptions::eDeleteClient:
            _ShowDeleteClientScreen();
            break;
        case enMainMenueOptions::eUpdateClient:
            _ShowUpdateClientScreen();
            break;
        case enMainMenueOptions::eFindClient:
            _ShowFindClientScreen();
            break;
        case enMainMenueOptions::eShowTransactionsMenue:
            _ShowTransactionsMenue();
            break;
        case enMainMenueOptions::eManageUsers:
            _ShowManageUsersMenue();
            break;
        case enMainMenueOptions::eLoginRegister:
            _ShowLoginRegisterScreen();
            break;
        case enMainMenueOptions::eCurrencyExchange:
            _ShowCurrencyExchangeMenue();
            break;

        case enMainMenueOptions::eExit:
            _Logout();
            break;
        }

        if (MainMenueOption != enMainMenueOptions::eExit)
            _GoBackToMainMenue();
    }



public:

    static void ShowMainMenue()
    {
        system("cls");
        _DrawScreenHeader("\t\tMain Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";

        cout << setw(37) << left << "" << _GetPermissionSymbol(clsUser::enPermissions::pListClients) << "[1] Show Client List.\n";
        cout << setw(37) << left << "" << _GetPermissionSymbol(clsUser::enPermissions::pAddNewClient) << "[2] Add New Client.\n";
        cout << setw(37) << left << "" << _GetPermissionSymbol(clsUser::enPermissions::pDeleteClient) << "[3] Delete Client.\n";
        cout << setw(37) << left << "" << _GetPermissionSymbol(clsUser::enPermissions::pUpdateClients) << "[4] Update Client Info.\n";
        cout << setw(37) << left << "" << _GetPermissionSymbol(clsUser::enPermissions::pFindClient) << "[5] Find Client.\n";
        cout << setw(37) << left << "" << _GetPermissionSymbol(clsUser::enPermissions::pTranactions) << "[6] Transactions.\n";
        cout << setw(37) << left << "" << _GetPermissionSymbol(clsUser::enPermissions::pManageUsers) << "[7] Manage Users.\n";
        cout << setw(37) << left << "" << _GetPermissionSymbol(clsUser::enPermissions::pLoginRegister) << "[8] Login Register.\n";
        cout << setw(37) << left << "" << _GetPermissionSymbol(clsUser::enPermissions::pCurrencyExchange) << "[9] Currency Exchange.\n";
        cout << setw(37) << left << "" << "      [10] Logout.\n";

        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromMainMenueOption((enMainMenueOptions)_ReadMainMenueOption());
    }
};
