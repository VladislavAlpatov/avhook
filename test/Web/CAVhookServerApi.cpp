#include "CAVhookServerApi.h"
using namespace WebApi;

#ifndef _DEBUG
#define AVHOOK_SERVER_URL xorstr("http://server.avhook.ru")
#else
#define AVHOOK_SERVER_URL xorstr("http://server.avhook.ru")
#endif // !_DEBUG


CAVHookServerApi::CAVHookServerApi()
{
	m_pClient = std::unique_ptr<httplib::Client>(new httplib::Client(AVHOOK_SERVER_URL));
}
CUserInfo CAVHookServerApi::GetUserInfo()
{
	// Download user data from server
	auto  jsonUserData = nlohmann::json::parse(m_pClient->Get(xorstr("/api/profile/get")).value().body);

	return CUserInfo(jsonUserData);
}
void CAVHookServerApi::ChangeUserNameAndStatus(const char* name, const char* status) const 
{
	nlohmann::json payloadJson;

	payloadJson[xorstr("name")]   = name;
	payloadJson[xorstr("status")] = status;

	m_pClient->Post(xorstr("/api/profile/set"), payloadJson.dump(), xorstr("application/json"));
}
std::vector<CConfig> WebApi::CAVHookServerApi::GetListOfConfigs()
{
	auto jsn = nlohmann::json::parse(m_pClient->Get(xorstr("/api/profile/configs/get/list")).value().body);
	auto cfgList = std::vector<CConfig>();
	for (auto& cfgJson : jsn[xorstr("configs")].get<std::list<nlohmann::json>>())
	{
		cfgList.push_back(CConfig(cfgJson));
	}
	return cfgList;
}
bool WebApi::CAVHookServerApi::UpdateConfig(const int cfgIid, const json& data)
{
	json postJsn;

	postJsn[xorstr("id")]   = cfgIid;
	postJsn[xorstr("data")] = data;

	auto respJsn = json::parse(m_pClient->Post(xorstr("/api/profile/configs/update"), postJsn.dump(), xorstr("application/json")).value().body);

	return respJsn[xorstr("Status")].get<bool>();
}
std::string CAVHookServerApi::GetRawAvatarData()
{
	return m_pClient->Get(xorstr("/api/profile/get_avatar")).value().body;
}
CLoaderTheme WebApi::CAVHookServerApi::GetLoaderTheme()
{
	const auto jsn = nlohmann::json::parse(m_pClient->Get(xorstr("/api/loader/get/theme")).value().body);

	return CLoaderTheme(jsn);
}
void WebApi::CAVHookServerApi::UpdateLoaderTheme(const CLoaderTheme& theme)
{
	m_pClient->Post(xorstr("/api/loader/update/theme"), theme.ToJson().dump(), xorstr("application/json"));
}
const char* CUserInfo::AccountTypeIdToString()
{
#ifndef _DEBUG
	switch (m_iAccountType)
	{
	case AccountType::Standart:
		return xorstr("Standard");

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

bool CAVHookServerApi::AuthByToken(const char* authToken) const
{
	auto payloadJsn = json();
	payloadJsn[xorstr("Token")] = authToken;

	json authStatus = json::parse(m_pClient->Post(xorstr("/api/oauth/token"), payloadJsn.dump(), xorstr("application/json")).value().body);
	
	return authStatus[xorstr("Authorized")].get<bool>();

}
AvatarUploadStatus CAVHookServerApi::SetUserAvatar(const std::string& rawData) const
{
	AvatarUploadStatus status;

	auto inputJsn = json::parse(m_pClient->Post(xorstr("/api/profile/avatar_set"), rawData, xorstr("text/plain")).value().body);
	status.m_isSucced = inputJsn[xorstr("Status")].get<bool>();
	
	if (status.m_isSucced)
		return status;

	status.m_sErrorMessage = inputJsn[xorstr("Reason")].get<std::string>();

	return status;

}
CUserInfo::CUserInfo(nlohmann::json jsn)
{
	std::string sUserName   = jsn[xorstr("name")].get<std::string>();
	std::string sUserStatus = jsn[xorstr("status")].get<std::string>();
	// Copy data
	strcpy_s(m_sName,   sUserName.c_str());
	strcpy_s(m_sStatus, sUserStatus.c_str());

	m_iAccountType = jsn[xorstr("type")].get<int>();
	m_bIsPremium   = jsn[xorstr("premium")].get<bool>();
	m_iUid         = jsn[xorstr("uid")].get<int>();

}

WebApi::CLoaderTheme::CLoaderTheme(const json& jsn)
{
	m_IconColor       = ImportImColorFromJson(jsn[xorstr("icon_color")].get<json>());
	m_ActiveIconColor = ImportImColorFromJson(jsn[xorstr("active_icon_color")].get<json>());
	m_LoadingColor    = ImportImColorFromJson(jsn[xorstr("loading_color")].get<json>());
	m_InjectedColor   = ImportImColorFromJson(jsn[xorstr("injected_color")].get<json>());

}

nlohmann::json WebApi::CLoaderTheme::ToJson() const
{
	json outJsn;
	
	outJsn[xorstr("icon_color")]        = ImColorToJsn(m_IconColor);
	outJsn[xorstr("active_icon_color")] = ImColorToJsn(m_ActiveIconColor);
	outJsn[xorstr("loading_color")]     = ImColorToJsn(m_LoadingColor);
	outJsn[xorstr("injected_color")]    = ImColorToJsn(m_InjectedColor);

	return outJsn;
}

WebApi::CConfig::CConfig(const json& jsn)
{
	m_iUid = jsn[xorstr("uid")].get<int>();
	m_Settings = Settings::CAllSettings(jsn[xorstr("data")].get<json>());
}
