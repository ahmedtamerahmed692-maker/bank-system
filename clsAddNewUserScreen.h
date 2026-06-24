#pragma once
#include <iostream>
#include <cmath>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include <iomanip>
class clsAddNewUserScreen : protected clsScreen
{
private:
    static void _ReadUserInfo(clsUser& User)
    {
        cout << "\nEnter FirstName: ";
        User.FirstName = clsInputValidate::ReadString();
        cout << "\nEnter LastName: ";
        User.LastName = clsInputValidate::ReadString();
        cout << "\nEnter Email: ";
        User.Email = clsInputValidate::ReadString();
        cout << "\nEnter Phone: ";
        User.Phone = clsInputValidate::ReadString();
        cout << "\nEnter Password: ";
        User.Password = clsInputValidate::ReadString();
        cout << "\nEnter Permission: ";
        User.Permissions = _ReadPermissionsToSet();
    }
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
        cout << "\nUser Name   : " << User.UserName;
        cout << "\nPassword    : " << User.Password;
        _PrintUserPermissionsAsText(User);
        cout << "\n___________________\n";
    }
    static short _ReadPermissionsToSet()
    {
        short Permissions = 0;
        if (clsInputValidate::YesOrNo("Do you want to give Full Access? [Y/N]: "))
        {
            return static_cast<short>(clsUser::enPermissions::eAll);
        }
        string PermArr[] = { "Show Client List", "Add New Client",
                              "Delete Client", "Update Client",
                              "Find Client", "Transactions", "Manage Users", "Show Login Register", "Currency Exchange" };
        for (short i = 0; i < 9; i++)
        {
            if (clsInputValidate::YesOrNo(PermArr[i] + "? [Y/N]: "))
            {
                Permissions |= static_cast<short>(pow(2, i));
            }
        }
        if (Permissions == 511)// انا عنا عملت كده عشان لو في المستقبل ضيفت فيوتشر جديده ومش عاوز اليوزر يكون واصلها فلو عملت -1 هيوصلها 
        {
            Permissions = 511;
        }
        return Permissions;
    }
public:
    static void ShowAddNewUserScreen()
    {
        _DrawScreenHeader("\t  Add New User Screen");
        string UserName = "";
        cout << "\nPlease Enter UserName: ";
        UserName = clsInputValidate::ReadString();
        while (clsUser::IsUserExist(UserName))
        {
            cout << "\nUserName Is Already Used, Choose another one: ";
            UserName = clsInputValidate::ReadString();
        }
        clsUser NewUser = clsUser::GetAddNewUserObject(UserName);
        _ReadUserInfo(NewUser);
        clsUser::enSaveResults SaveResult;
        SaveResult = NewUser.Save();
        switch (SaveResult)
        {
        case  clsUser::enSaveResults::svSucceeded:
        {
            cout << "\nUser Addeded Successfully :-)\n";
            _PrintUser(NewUser);
            break;
        }
        case clsUser::enSaveResults::svFaildEmptyObject:
        {
            cout << "\nError User was not saved because it's Empty";
            break;
        }
        case clsUser::enSaveResults::svFaildUserExists:
        {
            cout << "\nError User was not saved because UserName is used!\n";
            break;
        }
        }
    }
};