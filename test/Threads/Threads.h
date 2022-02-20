#pragma once
#include <Windows.h>
#include "../Server/Server.h"

#include <vector>
#include "../Hacks/AimBot.h"
#include "../Hacks/bhop.h"
#include "../Hacks/TriggerBot.h"
#include "../Hacks/Hooks/Hooks.h"

class Threads
{
public:
	Threads();
	void KillAll();
	~Threads();
	CServer* m_pServer;
private:
	std::vector<HANDLE> m_hThreadsHandles;
	static DWORD WINAPI TriggerBotThread(Settings::TriggerBotSettings* pTriggerBotSettings);
	static DWORD WINAPI ServerThread(CServer* pServer);
};