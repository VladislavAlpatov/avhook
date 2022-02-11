#include "CAVhookServerApi.h"

CAVHookServerApi::CAVHookServerApi()
{
	m_pClient =  new httplib::Client(AVHOOK_SERVER_URL);
}
CUserInfo CAVHookServerApi::GetUserInfo(const char* sEmail)
{
	nlohmann::json jsn;
	jsn[xorstr("Email")] = sEmail;

	// Download user data from server
	auto  jsonUserData = nlohmann::json::parse(m_pClient->Post(xorstr("/api/members/get"), jsn.dump(), xorstr("application/json")).value().body);

	return CUserInfo(jsonUserData);
}
void CAVHookServerApi::SetUserNameAndStatus(const char* email, const char* name, const char* status)
{
	nlohmann::json payloadJson;
	payloadJson[xorstr("Email")]  = email;
	payloadJson[xorstr("Name")]   = name;
	payloadJson[xorstr("Status")] = status;

	m_pClient->Post(xorstr("/api/members/set"), payloadJson.dump(), xorstr("application/json"));
}
CAVHookServerApi::~CAVHookServerApi()
{
	delete m_pClient;
}
std::string CAVHookServerApi::GetRawAvatarDataByUserId(int iUserId)
{
	
	return m_pClient->Get(std::format(xorstr("/media/avatars/{}"), iUserId).c_str()).value().body;

}