#pragma once

#include <iostream>
#include "clsScreen.h"
#include "../Core/clsBankClient.h"
#include "../Utils/clsInputValidate.h"

class clsDepositScreen : protected clsScreen
{

private:

    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";

    }

    static string _ReadAccountNumber()
    {
        string AccountNumber = "";
        cout << "\nPlease enter AccountNumber? ";
        cin >> AccountNumber;
        return AccountNumber;
    }


public:

    static void ShowDepositScreen()
    {
        _DrawScreenHeader("\t   Deposit Screen");

        string AccountNumber = _ReadAccountNumber();


        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
            AccountNumber = _ReadAccountNumber();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _PrintClient(Client1);

        

        cout << "\nPlease enter deposit amount? ";
        double Amount = clsInputValidate::ReadDblNumberBetween(1, DBL_MAX,"Invalid amount! Please enter an amount greater than 0.");

        cout << "\nAre you sure you want to perform this transaction? [y/n]: ";
        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            clsBankClient::enSaveResults Result = Client1.Deposit(Amount, CurrentUser.UserName);
            switch (Result)
            {
            case clsBankClient::svSucceeded:
                cout << "\nDeposit Done ✅" << endl;
                cout << "New Balance: " << Client1.AccountBalance << endl;
                break;

            case clsBankClient::svFaildBalance:
                cout << "\nInsufficient Balance ❌" << endl;
                cout << "Available Balance: " << Client1.AccountBalance << endl;
                break;
            }
        }
        else
        {
            cout << "\nOperation was cancelled.\n";
        }
    }

};
