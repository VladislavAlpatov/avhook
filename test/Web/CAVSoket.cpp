#include "CAVSoket.h"
#include <stdexcept>
#include <ws2tcpip.h>
#include "../Utils/xorstr.h"




CAVhookServerApi::CAVhookServerApi(const std::string& ip, const int port)
{
	m_sIp   = ip;
	m_iPort = port;
	WSADATA data;

	if (!WSAStartup(MAKEWORD(2, 2), &data))
		throw std::runtime_error(xorstr("Faild to initialize WinSock."));

	m_sConnection = socket(AF_INET, SOCK_STREAM, NULL);

	
}

bool CAVhookServerApi::Reconnect() const
{
	SOCKADDR_IN addr;
	inet_pton(AF_INET,m_sIp.c_str() , &addr.sin_addr.S_un.S_addr);
	addr.sin_port = htons(m_iPort);
	addr.sin_family = AF_INET;

	return connect(m_sConnection, (sockaddr*)&addr, sizeof(addr)) == 0;
}
