#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsUpdateClientScreen : protected clsScreen
{
private:

    enum enUpdateFields
    {
        FIRSTNAME = 1,  // 000001
        LASTNAME = 2,  // 000010
        EMAIL = 4,  // 000100
        PHONE = 8,  // 001000
        PINCODE = 16, // 010000
        BALANCE = 32, // 100000
        ALL = 63  // 111111
    };

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

    static int _ReadUpdateChoice()
    {
        int flags = 0;
        int choice = 0;

        cout << "\nWhat do you want to update?\n";
        cout << "[1] FirstName\n";
        cout << "[2] LastName\n";
        cout << "[3] Email\n";
        cout << "[4] Phone\n";
        cout << "[5] PinCode\n";
        cout << "[6] Balance\n";
        cout << "[7] All\n";
        cout << "[0] Done\n";

        while (true)
        {
            cin >> choice;

            if (choice == 0) break;

            switch (choice)
            {
            case 1: flags |= FIRSTNAME; break;
            case 2: flags |= LASTNAME;  break;
            case 3: flags |= EMAIL;     break;
            case 4: flags |= PHONE;     break;
            case 5: flags |= PINCODE;   break;
            case 6: flags |= BALANCE;   break;
            case 7: flags = ALL;       break;
            }
        }

        return flags;
    }

    static void ReadClientInfo(clsBankClient& Client, int updateFlags = ALL)
    {
        if (updateFlags & FIRSTNAME)
        {
            cout << "\nEnter FirstName: ";
            Client.FirstName = clsInputValidate::ReadString();
        }
        if (updateFlags & LASTNAME)
        {
            cout << "\nEnter LastName: ";
            Client.LastName = clsInputValidate::ReadString();
        }
        if (updateFlags & EMAIL)
        {
            cout << "\nEnter Email: ";
            Client.Email = clsInputValidate::ReadString();
        }
        if (updateFlags & PHONE)
        {
            cout << "\nEnter Phone: ";
            Client.Phone = clsInputValidate::ReadString();
        }
        if (updateFlags & PINCODE)
        {
            cout << "\nEnter PinCode: ";
            Client.PinCode = clsInputValidate::ReadString();
        }
        if (updateFlags & BALANCE)
        {
            cout << "\nEnter Account Balance: ";
            Client.AccountBalance = clsInputValidate::ReadFloatNumber();
        }
    }

public:

    static void ShowUpdateClientScreen()
    {

        if (!CheckAccessRights(clsUser::enPermissions::pUpdateClients))
        {
            return;// this will exit the function and it will not continue
        }
        _DrawScreenHeader("\tUpdate Client Screen");

        string AccountNumber = "";
        cout << "\nPlease Enter client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _PrintClient(Client1);

        cout << "\nAre you sure you want to update this client y/n? ";
        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            int updateFlags = _ReadUpdateChoice();
            ReadClientInfo(Client1, updateFlags);

            clsBankClient::enSaveResults SaveResult;
            SaveResult = Client1.Save();

            switch (SaveResult)
            {
            case clsBankClient::enSaveResults::svSucceeded:
                cout << "\nAccount Updated Successfully :-)\n";
                _PrintClient(Client1);
                break;
            case clsBankClient::enSaveResults::svFaildEmptyObject:
                cout << "\nError account was not saved because it's Empty";
                break;
            }
        }
    }
};