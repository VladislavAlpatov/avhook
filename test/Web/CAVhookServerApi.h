#pragma once
#include "httplib.h"
#include <nlohmann/json.hpp>
#include "../Globals/GlobalVars.h"
#include <Windows.h>

class CUserInfo
{
public:
	CUserInfo() {};

	CUserInfo(nlohmann::json jsn);
	bool operator!=(const CUserInfo& info)
	{
		return memcmp((void*)this, (void*)&info, sizeof(CUserInfo)) != 0;
	}
	char m_sName[128]   = { 0 };
	char m_sStatus[256] = { 0 };
	int m_iAccountType  = -1;
	int m_iUid = 0;
	bool m_bIsPremium;
	const char* AccountTypeIdToString();
	enum AccountType : int
	{
		Standart = 0,
		BetaTester,
		Developer,
	};
};

class CAVHookServerApi
{
public:
	CAVHookServerApi();
	~CAVHookServerApi();
	CUserInfo GetUserInfo();
	void ChangeUserNameAndStatus(const char* name, const char* status);
	bool AuthByToken(const char* authToken);

	std::string GetRawAvatarDataByUserId(int iUserId);

private:
	httplib::Client* m_pClient;
};

