#pragma once
#include "httplib.h"
#include <nlohmann/json.hpp>
#include "../Globals/GlobalVars.h"
#include <Windows.h>

class CUserInfo
{
public:
	CUserInfo() {};

	CUserInfo(nlohmann::json jsn)
	{
		std::string sUserName    = jsn[xorstr("Name")].get<std::string>();
		std::string sUserStatus  = jsn[xorstr("Status")].get<std::string>();
		// Copy data
		strcpy_s(m_sName,   sUserName.c_str());
		strcpy_s(m_sStatus, sUserStatus.c_str());

		m_iAccountType = jsn[xorstr("AccountType")].get<int>();
		m_bIsPremium   = jsn[xorstr("IsPremium")].get<bool>();
		m_iUid         = jsn[xorstr("Uid")].get<int>();


	}
	bool operator!=(const CUserInfo& info)
	{
		if (memcmp((void*)this, (void*)&info, sizeof(CUserInfo)) != 0)
			return true;
		return false;

	}
	char m_sName[128]   = { 0 };
	char m_sStatus[256] = { 0 };
	int m_iAccountType  = -1;
	int m_iUid = 0;
	bool m_bIsPremium;
	const char* AccountTypeIdToString()
	{
#ifndef _DEBUG
		switch (m_iAccountType)
		{
		case AccountType::Standart:
			return xorstr("Standart");

		case AccountType::BetaTester:
			return xorstr("Beta tester");

		case AccountType::Developer:
			return xorstr("Developer");
		default:
			return xorstr("Unknown");
		}
#else

		switch (m_iAccountType)
		{
		case AccountType::Standart:
			return "Standart";

		case AccountType::BetaTester:
			return "Beta tester";

		case AccountType::Developer:
			return "Developer";
		default:
			return "Unknown";
		}
#endif // !_DEBUG
	}
	enum AccountType
	{
		Standart,
		BetaTester,
		Developer,
	};
};

class CAVHookServerApi
{
public:
	CAVHookServerApi();
	~CAVHookServerApi();
	CUserInfo GetUserInfo(const char* sEmail);
	void SetUserNameAndStatus(const char* email, const char* name, const char* status);
	std::string GetRawAvatarDataByUserId(int iUserId);

private:
	httplib::Client* m_pClient;
};

