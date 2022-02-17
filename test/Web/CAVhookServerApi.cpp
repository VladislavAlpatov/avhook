#include "CAVhookServerApi.h"

CAVHookServerApi::CAVHookServerApi()
{
	m_pClient =  new httplib::Client(AVHOOK_SERVER_URL);
}
CUserInfo CAVHookServerApi::GetUserInfo()
{
	// Download user data from server
	auto  jsonUserData = nlohmann::json::parse(m_pClient->Get(xorstr("/api/profile/get")).value().body);

	return CUserInfo(jsonUserData);
}
void CAVHookServerApi::ChangeUserNameAndStatus(const char* name, const char* status)
{
	nlohmann::json payloadJson;

	payloadJson[xorstr("Name")]   = name;
	payloadJson[xorstr("Status")] = status;

	m_pClient->Post(xorstr("/api/profile/set"), payloadJson.dump(), xorstr("application/json"));
}
CAVHookServerApi::~CAVHookServerApi()
{
	delete m_pClient;
}
std::string CAVHookServerApi::GetRawAvatarData()
{
	return m_pClient->Get(xorstr("/api/profile/get_avatar")).value().body;
}
const char* CUserInfo::AccountTypeIdToString()
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

bool CAVHookServerApi::AuthByToken(const char* authToken)
{
	auto payloadJsn = json();
	payloadJsn[xorstr("Token")] = authToken;

	json authStatus = json::parse(m_pClient->Post(xorstr("/api/oauth/token"), payloadJsn.dump(), xorstr("application/json")).value().body);
	
	return authStatus[xorstr("Authorized")].get<bool>();

}
AvatarUploadStatus CAVHookServerApi::SetUserAvatar(const std::string& rawData)
{
	AvatarUploadStatus status;

	auto inputJsn = json::parse(m_pClient->Post(xorstr("/api/profile/avatar_set"), rawData, xorstr("text/plain")).value().body);
	status.m_isSucced = inputJsn[xorstr("Status")].get<bool>();
	
	if (status.m_isSucced)
		return status;

	status.m_sErrorMessage = inputJsn[xorstr("Reason")].get<std::string>();


}
CUserInfo::CUserInfo(nlohmann::json jsn)
{
	std::string sUserName   = jsn[xorstr("Name")].get<std::string>();
	std::string sUserStatus = jsn[xorstr("Status")].get<std::string>();
	// Copy data
	strcpy_s(m_sName, sUserName.c_str());
	strcpy_s(m_sStatus, sUserStatus.c_str());

	m_iAccountType = jsn[xorstr("AccountType")].get<int>();
	m_bIsPremium   = jsn[xorstr("IsPremium")].get<bool>();
	m_iUid         = jsn[xorstr("Uid")].get<int>();

}