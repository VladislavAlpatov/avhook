#include <Windows.h>

#include "Globals/GlobalVars.h"
#include "Hacks/Hooks/Hooks.h"
#include "resource.h"
#include "Utils/memory.h"
#include "Mmsystem.h"
#include "RazerSDK/CRazer.h"
#include "nlohmann/json.hpp"

DWORD WINAPI InitCheat(HMODULE hModule)
{
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

	while (!GetModuleHandle(xorstr("serverbrowser.dll")))
		Sleep(100);

	GlobalVars::Init(hModule);
	hooks::Attach(hModule);

	while (!GetAsyncKeyState(VK_END))
	{
		Sleep(100);
	}

	// Clean up sounds

	hooks::Detach();
	
	if (GlobalVars::bChromaSupport)
		CRazer().UnInit();

	FreeLibraryAndExitThread(hModule, NULL);
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
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

		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)InitCheat,   hModule, 0, nullptr);
	}
	return TRUE;
}