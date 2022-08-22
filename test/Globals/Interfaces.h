#pragma once

#include "../SDK/IVEngineClient013/IVEngineClient013.h"
#include "../SDK/IEngineTrace.h"
#include "../SDK/ClientBase.h"
#include "../SDK/IClientEntityList.h"
#include "../SDK/IGlowObjectManager.h"

namespace GlobalVars
{
	inline SSDK::ClientBase*		 g_pClient;
	inline SSDK::IClientEntityList*  g_pIEntityList;
	inline SSDK::IVEngineClient013*  g_pIEngineClient;
	inline SSDK::IEngineTrace*		 g_pIEngineTrace;
	inline SSDK::IGlowObjectManager* g_pGlowObjectManager;
}