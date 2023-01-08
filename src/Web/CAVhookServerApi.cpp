#include "CAVhookServerApi.h"
#include "../Utils/Marker.h"

using namespace WebApi;


CAVHookServerApi::CAVHookServerApi()
{
	POLY_MARKER;
    m_sConnection.Connect("89.111.137.169", 7777);
    nlohmann::json jsn;
    jsn["type"] = 1;
    jsn["email"] = "1@mail.ru";
    jsn["password"] = "1235";

    m_sConnection.SendJson(jsn);
    m_sConnection.RecvString();
}
CUserInfo CAVHookServerApi::GetUserInfo() const
{
	POLY_MARKER;
	// Download user data from server
    nlohmann::json jsn;
    jsn["type"] = 3;

    m_sConnection.SendJson(jsn);

	return m_sConnection.RecvJson();
}
void CAVHookServerApi::ChangeUserNameAndStatus(const char* name, const char* status) const 
{
	POLY_MARKER;
	nlohmann::json payloadJson;

	payloadJson[xorstr("name")]   = name;
	payloadJson[xorstr("status")] = status;

	//m_pClient->Post(xorstr("/api/profile/set"), payloadJson.dump(), xorstr("application/json"));
}
std::vector<CConfig> WebApi::CAVHookServerApi::GetListOfConfigs() const
{
	POLY_MARKER;
    nlohmann::json jsn;
    jsn["type"] = 6;
    m_sConnection.SendJson(jsn);
	auto cfgList = std::vector<CConfig>();
	for (const auto& cfgJson : m_sConnection.RecvJson()[xorstr("configs")].get<std::list<nlohmann::json>>())
	{
		cfgList.emplace_back(cfgJson);
	}
	return cfgList;
}
bool WebApi::CAVHookServerApi::UpdateConfig(const int cfgIid, const nlohmann::json& data)
{
	POLY_MARKER;
	nlohmann::json postJsn;

	postJsn[xorstr("id")]   = cfgIid;
	postJsn[xorstr("data")] = data;

	// auto respJsn = nlohmann::json::parse(m_pClient->Post(xorstr("/api/profile/configs/update"), postJsn.dump(), xorstr("application/json")).value().body);

	//return respJsn[xorstr("Status")].get<bool>();

    return false;
}
std::string CAVHookServerApi::GetRawAvatarData() const
{
	POLY_MARKER;
	//return m_pClient->Get(xorstr("/api/profile/get_avatar")).value().body;

    return {};
}
CLoaderTheme WebApi::CAVHookServerApi::GetLoaderTheme() const
{
	POLY_MARKER;
	//const auto jsn = nlohmann::json::parse(m_pClient->Get(xorstr("/api/loader/get/theme")).value().body);

	return {};
}
void WebApi::CAVHookServerApi::UpdateLoaderTheme(const CLoaderTheme& theme) const
{
	POLY_MARKER;
	//m_pClient->Post(xorstr("/api/loader/update/theme"), theme.ToJson().dump(), xorstr("application/json"));
}
std::string CUserInfo::AccountTypeIdToString() const
{
	POLY_MARKER;
	switch (m_iAccountType)
	{
	case AccountType::Standart:   return xorstr("Standard");
	case AccountType::BetaTester: return xorstr("Beta tester");
	case AccountType::Developer:  return xorstr("Developer");
	default:                      return xorstr("Unknown");
	}
}
AvatarUploadStatus CAVHookServerApi::SetUserAvatar(const std::string& rawData) const
{
	//POLY_MARKER;
	//AvatarUploadStatus status;

	//auto inputJsn = nlohmann::json::parse(m_pClient->Post(xorstr("/api/profile/avatar_set"), rawData, xorstr("text/plain")).value().body);
	//status.mIsSucced = inputJsn[xorstr("Status")].get<bool>();
	//if (status.mIsSucced)
	//	return status;
	//POLY_MARKER;
	//status.m_sErrorMessage = inputJsn[xorstr("Reason")].get<std::string>();

	return {};

}

CAVHookServerApi::~CAVHookServerApi()
{

}

CAVHookServerApi *CAVHookServerApi::Get()
{
    static auto pApi = std::unique_ptr<CAVHookServerApi>(new CAVHookServerApi());

    return pApi.get();
}

CUserInfo::CUserInfo(nlohmann::json jsn)
{
	POLY_MARKER;
	const auto sUserName   = jsn[xorstr("name")].get<std::string>();
	const auto sUserStatus = jsn[xorstr("status")].get<std::string>();
	// Copy data
	strcpy_s(m_sName,   sUserName.c_str());
	strcpy_s(m_sStatus, sUserStatus.c_str());

	m_iAccountType = jsn[xorstr("type")].get<int>();
	m_bIsPremium   = false;
	m_iUid         = jsn[xorstr("id")].get<int>();

}

WebApi::CLoaderTheme::CLoaderTheme(const nlohmann::json& jsn)
{
	POLY_MARKER;
	m_IconColor       = ImportImColorFromJson(jsn[xorstr("icon_color")].get<nlohmann::json>());
	m_ActiveIconColor = ImportImColorFromJson(jsn[xorstr("active_icon_color")].get<nlohmann::json>());
	m_LoadingColor    = ImportImColorFromJson(jsn[xorstr("loading_color")].get<nlohmann::json>());
	m_InjectedColor   = ImportImColorFromJson(jsn[xorstr("injected_color")].get<nlohmann::json>());

}

nlohmann::json WebApi::CLoaderTheme::ToJson() const
{
	POLY_MARKER;
	nlohmann::json outJsn;
	
	outJsn[xorstr("icon_color")]        = ImColorToJsn(m_IconColor);
	outJsn[xorstr("active_icon_color")] = ImColorToJsn(m_ActiveIconColor);
	outJsn[xorstr("loading_color")]     = ImColorToJsn(m_LoadingColor);
	outJsn[xorstr("injected_color")]    = ImColorToJsn(m_InjectedColor);

	return outJsn;
}

WebApi::CConfig::CConfig(const nlohmann::json& jsn)
{
	POLY_MARKER;

	m_iUid = jsn[xorstr("id")].get<int>();
	m_Settings = Settings::CAllSettings(jsn[xorstr("data")].get<nlohmann::json>());
}
