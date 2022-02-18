#include <Windows.h>

#include "Threads/Threads.h"
#include "Globals/GlobalVars.h"
#include "Hacks/Hooks/Hooks.h"
#include "resource.h"
#include "Utils/memory.h"
#include "Mmsystem.h"
#include "RazerSDK/CRazer.h"
#include "nlohmann/json.hpp"


DWORD WINAPI InitCheat(HMODULE hModule)
{
	POLY_MARKER

	CRazer razer = CRazer();
	if (razer.isSupported())
	{
		APPINFOTYPE appInfo;

		wcscpy_s(appInfo.Title, L"CSGO");
		wcscpy_s(appInfo.Description, L"CSGO");

		wcscpy_s(appInfo.Author.Name, L"CSGO");
		wcscpy_s(appInfo.Author.Contact, L"CSGO");

		appInfo.SupportedDevice = (0x01 | 0x02);
		appInfo.Category = 1;

		razer.Init();
		razer.InitSDK(&appInfo);

		GlobalVars::bChromaSupport = true;
	}
	else
	{
		GlobalVars::bChromaSupport = false;
	}

	GlobalVars::Init(hModule);
	hooks::Attach(hModule);
	
	PlaySound((char*)GlobalVars::activatedSound, hModule, SND_MEMORY | SND_ASYNC);

	while (!GetAsyncKeyState(VK_END))
	{
		Sleep(100);
	}

	PlaySound((char*)GlobalVars::deactivatedSound, hModule, SND_MEMORY | SND_ASYNC);

	// Clean up sounds

	delete GlobalVars::deactivatedSound;
	delete GlobalVars::activatedSound;

	POLY_MARKER

	hooks::Detach();
	
	if (GlobalVars::bChromaSupport)
		CRazer().UnInit();

	FreeLibraryAndExitThread(hModule, NULL);
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	POLY_MARKER;

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		auto client = httplib::Client(AVHOOK_SERVER_URL);

		if (client.Get(xorstr("/")).error() != httplib::Error::Success)
		{
			MessageBox(NULL, xorstr("I can't connect to the AVhook servers, check your internet connection, the game will be closed."), xorstr("Connection error"), MB_ICONERROR | MB_OK);
			exit(-1);
		}
		if (!WebApi::CAVHookServerApi().AuthByToken(GlobalVars::authToken))
		{
			MessageBox(NULL, xorstr("Incorrect token to access the account, please inform the administrator about this error."), xorstr("Auth error"), MB_ICONERROR | MB_OK);
			exit(-1);
		}

		auto data = client.Get(xorstr("/media/sounds/activated.wav")).value().body;
		GlobalVars::activatedSound = new char[data.size()];
			
		memcpy_s(GlobalVars::activatedSound, data.size(), data.c_str(), data.size());

		data = client.Get(xorstr("/media/sounds/deactivated.wav")).value().body;
		GlobalVars::deactivatedSound = new char[data.size()];

		memcpy_s(GlobalVars::deactivatedSound, data.size(), data.c_str(), data.size());

		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)InitCheat,   hModule, 0, nullptr);
	}
	return TRUE;
}