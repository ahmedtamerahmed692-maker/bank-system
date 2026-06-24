#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "clsPerson.h"
#include "clsString.h"
#include "clsTransactionLog.h"
#include "clsUtil.h"

using namespace std;


class clsBankClient : public clsPerson
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;

	static const string FileName;

	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkedForDelete = false;


	static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
	{
		vector<string> vClientData;
		vClientData = clsString::Split(Line, Seperator); 
		vClientData[5] = clsUtil::DecryptText(vClientData[5], 5);

		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1],
			vClientData[2], vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
	}

	static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
	{
		string stClientRecord = "";
		stClientRecord += Client.FirstName + Seperator;
		stClientRecord += Client.LastName + Seperator;
		stClientRecord += Client.Email + Seperator;
		stClientRecord += Client.Phone + Seperator;
		stClientRecord += Client.AccountNumber() + Seperator;
		Client.PinCode = clsUtil::EncryptText(Client.PinCode, 5);
		stClientRecord += Client.PinCode + Seperator;
		stClientRecord += to_string(Client.AccountBalance);
		return stClientRecord;
	}

	static vector<clsBankClient> _LoadClientsDataFromFile()
	{
		vector<clsBankClient> vClients;
		fstream MyFile;
		MyFile.open(FileName, ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				if (Line == "")
					continue;

				clsBankClient Client = _ConvertLinetoClientObject(Line);
				vClients.push_back(Client);
			}
			MyFile.close();
		}
		return vClients;
	}

	static void _SaveCleintsDataToFile(vector<clsBankClient> vClients)
	{
		fstream MyFile;
		MyFile.open(FileName, ios::out);

		if (MyFile.is_open())
		{
			for (clsBankClient& C : vClients)
			{
				if (!C.IsEmpty() && !C._MarkedForDelete)
				{
					MyFile << _ConverClientObjectToLine(C) << endl;
				}
			}
			MyFile.close();
		}
	}

	//////////////التعديل ///////////////////////////////////
	void _Update()
	{
		vector<clsBankClient> _vClients = _LoadClientsDataFromFile();
		for (clsBankClient& C : _vClients)
		{
			if (C.AccountNumber() == AccountNumber())
			{
				C = *this;
				break;
			}
		}
		_SaveCleintsDataToFile(_vClients);
	}
	//////////////////////////////////////////////////////////
	/////////////////اضافه عميل /////////////////////////////////////
	void _AddNew()
	{

		_AddDataLineToFile(_ConverClientObjectToLine(*this));
	}
	void _AddDataLineToFile(string  stDataLine)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}
	///////////////////////////////////////////////////////////
	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

public:

	clsBankClient(enMode Mode, string FirstName, string LastName,
		string Email, string Phone, string AccountNumber,
		string PinCode, float AccountBalance) :
		clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}


	string AccountNumber()
	{
		return _AccountNumber;
	}

	void SetPinCode(string PinCode) { _PinCode = PinCode; }
	string GetPinCode() { return _PinCode; }
	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void SetAccountBalance(float AccountBalance) { _AccountBalance = AccountBalance; }
	float GetAccountBalance() { return _AccountBalance; }
	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

	
	/////////////////////////////بحث//////////////////////////////////////////////
	static clsBankClient Find(string AccountNumber)
	{
		fstream MyFile;
		MyFile.open(FileName, ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLinetoClientObject(Line);
				if (Client.AccountNumber() == AccountNumber)
				{
					MyFile.close();
					return Client;
				}
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}
	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		fstream MyFile;
		MyFile.open(FileName, ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLinetoClientObject(Line);
				if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
				{
					MyFile.close();
					return Client;
				}
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}
	/////////////////////////////////////////////////////////////////////////
	///////////////////////////الحزف ////////////////////////////////////////////
	bool Delete()
	{
		if (_Mode == enMode::EmptyMode || _Mode == enMode::AddNewMode)
			return false;

		bool Found = false;
		vector<clsBankClient> _vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClients)
		{
			if (C.AccountNumber() == _AccountNumber)
			{
				C._MarkedForDelete = true;
				Found = true;
				break;
			}
		}

		if (!Found) return false;

		_SaveCleintsDataToFile(_vClients);
		*this = _GetEmptyClientObject();
		return true;
	}
	////////////////////////////////////////////////////////////////
	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2, svFaildBalance = 3 };

	enSaveResults Save()
	{


		switch (_Mode)
		{
		case enMode::EmptyMode:
		{
			if (IsEmpty())
			{

				return enSaveResults::svFaildEmptyObject;

			}

			break;
		}

		case enMode::UpdateMode:
		{


			_Update();

			return enSaveResults::svSucceeded;

			break;
		}

		case enMode::AddNewMode:
		{
			if (clsBankClient::IsClientExist(_AccountNumber))
			{
				return enSaveResults::svFaildAccountNumberExists;
			}
			else
			{
				_AddNew();

				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}

			break;
		}
		}

		return enSaveResults::svFaildEmptyObject;
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}
	static bool IsClientExist(string AccountNumber)//هل العميل موجود؟//
	{

		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		return (!Client1.IsEmpty());
	}


	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}
	static vector <clsBankClient> GetClientsList()
	{
		return _LoadClientsDataFromFile();
	} 

	static float GetTotalBalances()
	{
		vector <clsBankClient> vClients = clsBankClient::GetClientsList();

		double TotalBalances = 0;

		for (clsBankClient Client : vClients)
		{

			TotalBalances += Client.AccountBalance;
		}

		return TotalBalances;

	}
	
	///////////التحويل //////////////////////

	// Deposit: بتزود الرصيد بالمبلغ المحدد
	// بترجع enSaveResults عشان المبرمج يعرف
	// هل العملية نجحت ولا فشلت
	// لو الأوبجيكت فاضي (EmptyMode) هترجع svFaildEmptyObject
	enSaveResults Deposit(double Amount, string UserName, bool RegisterLog = true)
	{
		_AccountBalance += Amount;
		enSaveResults Result = Save();
		if (Result == svSucceeded && RegisterLog)
		{
			clsTransactionLog(_AccountNumber, "", Amount, clsTransactionLog::eDeposit, UserName).Save();
		}
		return Result;
	}

	enSaveResults Withdraw(double Amount, string UserName, bool RegisterLog = true)
	{
		if (Amount > _AccountBalance) 
			return svFaildBalance;   

		_AccountBalance -= Amount;
		enSaveResults Result = Save();
		if (Result == svSucceeded && RegisterLog)
		{
			clsTransactionLog(_AccountNumber, "", Amount, clsTransactionLog::eWithdraw, UserName).Save();
		}
		return Result;      
	}

	enSaveResults Transfer(string ToAccountNumber, double Amount, string UserName)

	{
		enSaveResults Result = Withdraw(Amount, UserName, false);
		if (Result != svSucceeded)
			return Result;

		clsBankClient ToClient = clsBankClient::Find(ToAccountNumber);
		ToClient.Deposit(Amount, UserName, false);

		clsTransactionLog T(_AccountNumber, ToAccountNumber, Amount, clsTransactionLog::eTransfer, UserName);
		T.Save();
		
		return svSucceeded;
	}

};


