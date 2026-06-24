#pragma once
#include <iostream>
#include "clsScreen.h"
#include "../Core/clsPerson.h"
#include "../Core/clsUser.h"
#include "../Utils/clsInputValidate.h"

class clsUpdateUserScreen :protected clsScreen

{
private:

    enum enUpdateFields
    {
        FIRSTNAME = 1,  // 0000001
        LASTNAME = 2,  // 0000010
        EMAIL = 4,  // 0000100
        PHONE = 8,  // 0001000
        PASSWORD = 16, // 0010000
        PERMISSIONS = 32, // 0100000
        ALL_EXCEPT_PERMISSIONS = 31, // 0011111 (FIRSTNAME+LASTNAME+EMAIL+PHONE+PASSWORD)
        ALL = 63  // 0111111
    };

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

    static int _ReadUpdateChoice()
    {
        int flags = 0;
        int choice = 0;

        cout << "\nWhat do you want to update?\n";
        cout << "[1] FirstName\n";
        cout << "[2] LastName\n";
        cout << "[3] Email\n";
        cout << "[4] Phone\n";
        cout << "[5] Password\n";
        cout << "[6] Permissions\n";
        cout << "[7] All Except Permissions\n";
        cout << "[8] All (Including Permissions)\n";
        cout << "[0] Done\n";

        while (true)
        {
            cin >> choice;

            if (choice == 0) break;

            switch (choice)
            {
            case 1: flags |= FIRSTNAME;               break;
            case 2: flags |= LASTNAME;                break;
            case 3: flags |= EMAIL;                   break;
            case 4: flags |= PHONE;                   break;
            case 5: flags |= PASSWORD;                break;
            case 6: flags |= PERMISSIONS;             break;
            case 7: flags = ALL_EXCEPT_PERMISSIONS;   break;
            case 8: flags = ALL;                      break;
            }
        }

        return flags;
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

    static void ReadUserInfo(clsUser& User, int updateFlags = ALL)
    {
        if (updateFlags & FIRSTNAME)
        {
            cout << "\nEnter FirstName: ";
            User.FirstName = clsInputValidate::ReadString();
        }
        if (updateFlags & LASTNAME)
        {
            cout << "\nEnter LastName: ";
            User.LastName = clsInputValidate::ReadString();
        }
        if (updateFlags & EMAIL)
        {
            cout << "\nEnter Email: ";
            User.Email = clsInputValidate::ReadString();
        }
        if (updateFlags & PHONE)
        {
            cout << "\nEnter Phone: ";
            User.Phone = clsInputValidate::ReadString();
        }
        if (updateFlags & PASSWORD)
        {
            cout << "\nEnter Password: ";
            User.Password = clsInputValidate::ReadString();
        }
        if (updateFlags & PERMISSIONS)
        {
            cout << "\nEnter Permission: ";
            User.Permissions = _ReadPermissionsToSet();
        }
    }

public:

    static void ShowUpdateUserScreen()
    {

        _DrawScreenHeader("\tUpdate User Screen");

        string UserName = "";

        cout << "\nPlease Enter User UserName: ";
        UserName = clsInputValidate::ReadString();

        while (!clsUser::IsUserExist(UserName))
        {
            cout << "\nAccount number is not found, choose another one: ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser User1 = clsUser::Find(UserName);

        _PrintUser(User1);

        cout << "\nAre you sure you want to update this User y/n? ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {

            cout << "\n\nUpdate User Info:";
            cout << "\n____________________\n";

            int updateFlags = _ReadUpdateChoice();
            ReadUserInfo(User1, updateFlags);

            clsUser::enSaveResults SaveResult;

            SaveResult = User1.Save();

            switch (SaveResult)
            {
            case  clsUser::enSaveResults::svSucceeded:
            {
                cout << "\nUser Updated Successfully :-)\n";

                _PrintUser(User1);
                break;
            }
            case clsUser::enSaveResults::svFaildEmptyObject:
            {
                cout << "\nError User was not saved because it's Empty";
                break;

            }

            }

        }

    }
};