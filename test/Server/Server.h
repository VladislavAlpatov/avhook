#pragma once 

#include <Windows.h>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include "../Globals/GlobalVars.h"
#include "Server.h"
#include <string.h>
#include <string>
#include <stdexcept>


class CServer
{
public:
	CServer();
	~CServer();
	int GetFreePort();
	void Work();
private:
	char m_ServerBuff[512] = {0};
};