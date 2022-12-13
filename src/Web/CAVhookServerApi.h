#pragma once
#include "httplib.h"
#include <nlohmann/json.hpp>
#include <windows.h>
#include <memory>
#include "IWebObject.h"
#include "../Menu/Settings.h"

namespace WebApi
{
	class CUserInfo
	{
	public:
		CUserInfo() {};

		CUserInfo(nlohmann::json jsn);
		bool operator!=(const CUserInfo& info) const
		{
			return memcmp(this, &info, sizeof(CUserInfo)) != 0;
		}
		char m_sName[128] = { 0 };
		char m_sStatus[256] = { 0 };
		int m_iAccountType = -1;
		int m_iUid = 0;
		bool m_bIsPremium;
		std::string AccountTypeIdToString() const;
		enum AccountType : int
		{
			Standart = 0,
			BetaTester,
			Developer,
		};
	};

	class CLoaderTheme final: public IWebObject
	{
	public:
		CLoaderTheme() = default;
		CLoaderTheme(const nlohmann::json& jsn);
		ImColor m_IconColor       = { 112, 112, 112, 255 };
		ImColor m_ActiveIconColor = { 255, 84, 84, 255 };
		ImColor m_LoadingColor    = { 255, 84, 84, 255 };
		ImColor m_InjectedColor   = { 108, 255, 94, 255 };

        nlohmann::json ToJson() const override;
	};

	struct AvatarUploadStatus
	{
		bool mIsSucced = false;
		std::string m_sErrorMessage = "Not uploaded";
	};
	class CConfig
	{
	public:
		CConfig(const nlohmann::json& jsn);
		int         m_iUid;
		Settings::CAllSettings m_Settings;
	};

	class CMenuThemeConfig
	{
	public:
		CMenuThemeConfig([[maybe_unused]] const nlohmann::json jsn)
		{

		}
		int m_iUID;

	};
	class CAVHookServerApi
	{
	public:
		CAVHookServerApi();
		CUserInfo GetUserInfo() const;
		void ChangeUserNameAndStatus(const char* name, const char* status) const;
		std::vector<CConfig> GetListOfConfigs() const;
		bool UpdateConfig(const int cfgIid,const nlohmann::json& data);

		bool AuthByToken(const char* authToken) const;
		AvatarUploadStatus SetUserAvatar(const std::string& rawDatas) const;
		std::string GetRawAvatarData() const;
		CLoaderTheme GetLoaderTheme() const;
		void UpdateLoaderTheme(const CLoaderTheme& theme) const;

	private:
		std::unique_ptr<httplib::Client> m_pClient;
	};

}

