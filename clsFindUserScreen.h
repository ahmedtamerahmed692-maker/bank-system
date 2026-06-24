#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "clsInputValidate.h"
class clsFindUserScreen :protected clsScreen
{
private:
    static void _PrintUserPermissionsAsText(clsUser User)
    {
        if (User.Permissions == clsUser::enPermissions::eAll)
        {
            cout << "\nPermissions : Full Access";
            return;
        }

        if (User.Permissions == 0)
        {
            cout << "\nPermissions : No Access";
            return;
        }

        cout << "\nPermissions :";

        if (User.CheckAccessPermission(clsUser::enPermissions::pListClients))
            cout << "\n   - Show Clients List";

        if (User.CheckAccessPermission(clsUser::enPermissions::pAddNewClient))
            cout << "\n   - Add New Client";

        if (User.CheckAccessPermission(clsUser::enPermissions::pDeleteClient))
            cout << "\n   - Delete Client";

        if (User.CheckAccessPermission(clsUser::enPermissions::pUpdateClients))
            cout << "\n   - Update Client";

        if (User.CheckAccessPermission(clsUser::enPermissions::pFindClient))
            cout << "\n   - Find Client";

        if (User.CheckAccessPermission(clsUser::enPermissions::pTranactions))
            cout << "\n   - Transactions";

        if (User.CheckAccessPermission(clsUser::enPermissions::pManageUsers))
            cout << "\n   - Manage Users";

        if (User.CheckAccessPermission(clsUser::enPermissions::pLoginRegister))
            cout << "\n   - Show Login Register";

        if (User.CheckAccessPermission(clsUser::enPermissions::pCurrencyExchange))
            cout << "\n   - Currency Exchange";
    }
    static void _PrintUser(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.FirstName;
        cout << "\nLastName    : " << User.LastName;
        cout << "\nFull Name   : " << User.FullName();
        cout << "\nEmail       : " << User.Email;
        cout << "\nPhone       : " << User.Phone;
        cout << "\nUserName    : " << User.UserName;
        cout << "\nPassword    : " << User.Password;
        _PrintUserPermissionsAsText(User);
        cout << "\n___________________\n";
    }
public:

    static void ShowFindUserScreen()
    {
        _DrawScreenHeader("\t  Find User Screen");
        string UserName;
        cout << "\nPlease Enter UserName: ";
        UserName = clsInputValidate::ReadString();
        while (!clsUser::IsUserExist(UserName))
        {
            cout << "\nUser is not found, choose another one: ";
            UserName = clsInputValidate::ReadString();
        }
        clsUser User1 = clsUser::Find(UserName);
        if (!User1.IsEmpty())
        {
            cout << "\nUser Found :-)\n";
        }
        else
        {
            cout << "\nUser Was not Found :-(\n";
        }
        _PrintUser(User1);
    }
};