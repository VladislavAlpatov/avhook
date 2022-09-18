#pragma once
#include <WinSock2.h>
#include <string>


class CAVhookServerApi
{
public:
	CAVhookServerApi(const std::string& ip, const int port);
private:
	SOCKET m_sConnection;
	std::string m_sIp;
	int m_iPort;
	
	bool Reconnect() const;
};

