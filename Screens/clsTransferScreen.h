#pragma once

#include <iostream>
#include "clsScreen.h"
#include "../Core/clsBankClient.h"
#include "../Utils/clsInputValidate.h"

class clsTransferScreen : protected clsScreen
{
private:

    static string _ReadAccountNumber()
    {
        string AccountNumber;
        cout << "\nEnter Account Number: ";
        cin >> AccountNumber;
        return AccountNumber;
    }

    static void _PrintClient( clsBankClient& Client)
    {
        cout << "\nClient Info:";
        cout << "\n------------------";
        cout << "\nName: " << Client.FullName();
        cout << "\nAccount: " << Client.AccountNumber();
        cout << "\nBalance: " << Client.AccountBalance;
        cout << "\n------------------\n";
    }

public:
    
    static void ShowTransferScreen()
    {
        _DrawScreenHeader("\t Transfer Screen");

        cout << "\nSender Account";
        string SenderAcc = _ReadAccountNumber();

        while (!clsBankClient::IsClientExist(SenderAcc)) 
        {
            cout << "\nSender account not found!\n";
            SenderAcc = _ReadAccountNumber();
        }

        clsBankClient Sender = clsBankClient::Find(SenderAcc);
        _PrintClient(Sender);

        if (Sender.AccountBalance <= 0)
        {
            cout << "\nTransfer not allowed. Sender balance is zero.";
            return;
        }
       
        cout << "\nReceiver Account";
        string ReceiverAcc = _ReadAccountNumber();

        while (!clsBankClient::IsClientExist(ReceiverAcc))
        {
            cout << "\nReceiver account not found!\n";
            ReceiverAcc = _ReadAccountNumber();
        }

        if (SenderAcc == ReceiverAcc)
        {
            cout << "\nCannot transfer to the same account!";
            return;
        }

        clsBankClient Receiver = clsBankClient::Find(ReceiverAcc);
        cout << "\nTransfer will be sent to: " << Receiver.FullName();

        cout << "\nEnter transfer amount: ";
        double Amount = clsInputValidate::ReadDblNumberBetween(  0.01, Sender.AccountBalance, "Invalid amount! Must be <= sender balance.");

        cout << "\nConfirm transfer? [y/n]: ";
        char Answer;
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            clsBankClient::enSaveResults Result = Sender.Transfer(ReceiverAcc, Amount, CurrentUser.UserName);

            if (Result == clsBankClient::svSucceeded)
            {
                cout << "\nTransfer completed successfully ✅";
                Sender = clsBankClient::Find(SenderAcc);
                Receiver = clsBankClient::Find(ReceiverAcc);
                cout << "\nSender New Balance: " << Sender.AccountBalance;
                cout << "\nReceiver New Balance: " << Receiver.AccountBalance;
            }
            else
            {
                cout << "\nTransfer failed ❌";
            }
        }
        else
        {
            cout << "\nTransfer cancelled.";
        }
    }
};
