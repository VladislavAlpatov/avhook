#pragma once
#include "../SDK/IVEngineClient013/IVEngineClient013.h"
#include "../SDK/IEngineTrace.h"
#include "../SDK/ClientBase.h"
#include "../Menu/Settings.h"
#include "../Utils/xorstr.h"
#include "../SDK/IClientEntityList.h"

#ifndef _DEBUG
	#define AVHOOK_SERVER_URL xorstr("http://server.avhook.ru")
#else
	#define AVHOOK_SERVER_URL xorstr("http://192.168.0.16:5000")
#endif // !_DEBUG

namespace GlobalVars
{
	inline SSDK::ClientBase*        pClient;
	inline DWORD                    engine;
	inline HMODULE                  hModule;
	inline SSDK::IClientEntityList* pIEntityList;
	inline SSDK::IVEngineClient013* pIEngineClient;
	inline Settings::SAllSettings   settings;
	inline SSDK::IEngineTrace*      pIEngineTrace;
	inline ImVec3			        veLocalPlayerViewAngles;
#ifdef DEV_BUILD
	inline const char		  authToken[] = "bWevWkyjyNLFwn4f3tjXJGgSux4H8Jbe";
#elif _DEBUG
	inline const char		  authToken[] = "bWevWkyjyNLFwn4f3tjXJGgSux4H8Jbe";
#else
	inline const char		  authToken[] = ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>";
#endif // DEV_BUILD

	inline bool bChromaSupport = false;
	void Init(HMODULE hModule);
}