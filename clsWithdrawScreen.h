#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
class clsWithdrawScreen: protected clsScreen

{
    private:

        static void _PrintClient( clsBankClient Client)
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

        static void ShowWithdrawScreen()
        {
            _DrawScreenHeader("\t   Withdraw Screen");

            string AccountNumber = _ReadAccountNumber();


            while (!clsBankClient::IsClientExist(AccountNumber))
            {
                cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
                AccountNumber = _ReadAccountNumber();
            }

            clsBankClient Client1 = clsBankClient::Find(AccountNumber);
            _PrintClient(Client1);

            if (Client1.AccountBalance <= 0)
            {
                cout << "\nNo balance available for withdrawal.";
                return;
            }

            cout << "\nPlease enter Withdraw amount? ";
            double Amount = clsInputValidate::ReadDblNumberBetween(0.01, Client1.AccountBalance,  "Sorry Sir, the amount you are trying to withdraw exceeds your available account balance.");

            cout << "\nAre you sure you want to perform this transaction? [y/n]: ";
            char Answer = 'n';
            cin >> Answer;

            if (Answer == 'Y' || Answer == 'y')
            {
                clsBankClient::enSaveResults Result = Client1.Withdraw(Amount, CurrentUser.UserName);
                switch (Result)
                {
                case clsBankClient::svSucceeded:
                    cout << "\nWithdrawal completed successfully." << endl;
                    cout << "New Balance: " << Client1.AccountBalance << endl;
                    break;

                case clsBankClient::svFaildEmptyObject:
                    cout << "\nError! Empty Client " << endl;
                    break;
                }
            }
            else
            {
                cout << "\nOperation was cancelled.\n";
            }
        }

    };



