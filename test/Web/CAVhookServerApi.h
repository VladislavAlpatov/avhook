#pragma once
#include "httplib.h"
#include <nlohmann/json.hpp>
#include "../Globals/GlobalVars.h"
#include <Windows.h>
namespace WebApi
{
	using namespace nlohmann;
	class CUserInfo
	{
	public:
		CUserInfo() {};

		CUserInfo(nlohmann::json jsn);
		bool operator!=(const CUserInfo& info)
		{
			return memcmp((void*)this, (void*)&info, sizeof(CUserInfo)) != 0;
		}
		char m_sName[128] = { 0 };
		char m_sStatus[256] = { 0 };
		int m_iAccountType = -1;
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

	struct AvatarUploadStatus
	{
		bool m_isSucced = false;
		std::string m_sErrorMessage = xorstr("Not uploaded");
	};

	class CAVHookServerApi
	{
	public:
		CAVHookServerApi();
		~CAVHookServerApi();
		CUserInfo GetUserInfo();
		void ChangeUserNameAndStatus(const char* name, const char* status) const;
		bool AuthByToken(const char* authToken) const;
		AvatarUploadStatus SetUserAvatar(const std::string& rawDatas) const;
		std::string GetRawAvatarData();

	private:
		httplib::Client* m_pClient;
	};

}

