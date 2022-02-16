#pragma once
#include "../SDK/IVEngineClient013/IVEngineClient013.h"
#include "../SDK/IEngineTrace.h"
#include "../SDK/ClientBase.h"
#include "../Menu/Settings.h"
#include "../Utils/xorstr.h"

#ifndef _DEBUG
	#define AVHOOK_SERVER_URL xorstr("http://server.avhook.ru")
#else
	#define AVHOOK_SERVER_URL xorstr("http://192.168.0.16:5000")
#endif // !_DEBUG

namespace GlobalVars
{
	inline ClientBase*        client;
	inline DWORD              engine;
	inline HMODULE            hModule;
	inline IClientEntityList* pIEntityList;
	inline IVEngineClient013* pIEngineClient;
	inline SAllSettings       settings;
	inline IEngineTrace*      pIEngineTrace;
	inline ImVec3			  veLocalPlayerViewAngles;
	inline const char		  authToken[] = "bWevWkyjyNLFwn4f3tjXJGgSux4H8Jbe";
	inline bool bChromaSupport = false;
	void Init(HMODULE hModule);

	inline char* activatedSound   = nullptr;
	inline char* deactivatedSound = nullptr;
}