#include <Windows.h>

#include "Globals/GlobalVars.h"
#include "Hacks/Hooks/Hooks.h"
#include "RazerSDK/CRazer.h"
#include "Web/CAVhookServerApi.h"
#include "Utils/Marker.h"

DWORD WINAPI InitCheat(HMODULE hModule)
{
	POLY_MARKER;

	CRazer razer = CRazer();
	if (razer.isSupported())
	{
		APPINFOTYPE appInfo;

		wcscpy_s(appInfo.Title, L"CSGO");
		wcscpy_s(appInfo.Description, L"CSGO");

		wcscpy_s(appInfo.Author.Name, L"CSGO");
		POLY_MARKER;
		wcscpy_s(appInfo.Author.Contact, L"CSGO");
		POLY_MARKER;
		appInfo.SupportedDevice = (0x01 | 0x02);
		appInfo.Category = 1;
		POLY_MARKER;
		razer.Init();
		razer.InitSDK(&appInfo);

		GlobalVars::bChromaSupport = true;
	}
	else
	{
		POLY_MARKER;
		GlobalVars::bChromaSupport = false;
		POLY_MARKER;
	}
	
	while (!GetModuleHandleA(xorstr("serverbrowser.dll")))
		Sleep(100);

	GlobalVars::Init(hModule);
	hooks::Attach(hModule);
	POLY_MARKER;

	while (!GetAsyncKeyState(VK_END))
	{
		Sleep(100);
	}

	// Clean up sounds

	hooks::Detach();
	POLY_MARKER;
	if (GlobalVars::bChromaSupport)
		CRazer().UnInit();

	FreeLibraryAndExitThread(hModule, NULL);
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	POLY_MARKER;

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		/*auto client = httplib::Client(AVHOOK_SERVER_URL);

		if (client.Get(xorstr("/")).error() != httplib::Error::Success)
		{
			POLY_MARKER;
			MessageBoxA(NULL, xorstr("I can't connect to the AVhook servers, check your internet connection, the game will be closed."), xorstr("Connection error"), MB_ICONERROR | MB_OK);
			exit(-1);
		}
		if (!WebApi::CAVHookServerApi().AuthByToken(GlobalVars::authToken))
		{
			POLY_MARKER;
			MessageBoxA(NULL, xorstr("Incorrect token to access the account, please inform the administrator about this error."), xorstr("Auth error"), MB_ICONERROR | MB_OK);
			exit(-1);
		}*/

		POLY_MARKER;
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)InitCheat,   hModule, 0, nullptr);
	}
	return TRUE;
}