#include "Threads.h"

Threads::Threads()
{
}
void Threads::KillAll()
{
	for (auto thread_handle : this->m_hThreadsHandles)
		TerminateThread(thread_handle, 0);
	this->m_hThreadsHandles.clear();
}
Threads::~Threads()
{
	delete m_pServer;
	if (!this->m_hThreadsHandles.empty())
		this->KillAll();
}

DWORD WINAPI Threads::TriggerBotThread(TriggerBotSettings* pTriggerBotSettings)
{
	TriggerBot triggerbot(pTriggerBotSettings);

	while (true)
	{
		Sleep(100);
	}
	ExitThread(0);
}
DWORD WINAPI Threads::ServerThread(CServer* pServer)
{
	pServer->Work();

	return 0;
}