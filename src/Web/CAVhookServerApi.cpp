#include "CAVhookServerApi.h"
#include "../Utils/Marker.h"
#include <ws2tcpip.h>

using namespace WebApi;



CAVHookServerApi::CAVHookServerApi()
{
	POLY_MARKER;
    m_sIp   = "127.0.0.1";
    m_iPort = 7777;
    WSADATA data;

    WSAStartup(MAKEWORD(2, 2), &data);

    m_sConnection = socket(AF_INET, SOCK_STREAM, NULL);

    while (!Reconnect())
        Sleep(500);
    nlohmann::json jsn;
    jsn["type"] = 1;
    jsn["email"] = "1@mail.ru";
    jsn["password"] = "1234";
    send_json(jsn);

}
CUserInfo CAVHookServerApi::GetUserInfo() const
{
	POLY_MARKER;
	// Download user data from server
    nlohmann::json jsn;
    jsn["type"] = 3;
    send_json(jsn);
    char buff[1024] = {0};

    recv(m_sConnection, buff, 1024, 0);

	return nlohmann::json::parse(buff);
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
	//auto jsn = nlohmann::json::parse(m_pClient->Get(xorstr("/api/profile/configs/get/list")).value().body);
	auto cfgList = std::vector<CConfig>();
	//for (const auto& cfgJson : jsn[xorstr("configs")].get<std::list<nlohmann::json>>())
	//{
	//	cfgList.emplace_back(cfgJson);
	//}
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

bool CAVHookServerApi::Reconnect()
{
    SOCKADDR_IN addr;
    inet_pton(AF_INET,m_sIp.c_str() , &addr.sin_addr.S_un.S_addr);
    addr.sin_port = htons(m_iPort);
    addr.sin_family = AF_INET;

    return !connect(m_sConnection, (sockaddr*)&addr, sizeof(addr));
}

void CAVHookServerApi::send_json(const nlohmann::json &jsn) const
{
    std::string str = jsn.dump();
    int size = str.size();
    send(m_sConnection, (const char*)&size, 4, 0);
    for (int sentBytes = 0; sentBytes < str.length(); )
    {
        sentBytes += send(m_sConnection, str.c_str()+sentBytes, str.size(), 0);
    }
}

CAVHookServerApi::~CAVHookServerApi()
{
    closesocket(m_sConnection);
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

	m_iUid = jsn[xorstr("uid")].get<int>();
	m_Settings = Settings::CAllSettings(jsn[xorstr("data")].get<nlohmann::json>());
}
