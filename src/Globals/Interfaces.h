#pragma once

#include "../SDK/IVEngineClient013/IVEngineClient013.h"
#include "../SDK/IEngineTrace.h"
#include "../SDK/IClientEntityList.h"
#include "../SDK/IGlowObjectManager.h"
#include "../SDK/CVarSystem/ICvarSystem.h"


namespace GlobalVars
{
	inline SSDK::IClientEntityList*  g_pIEntityList;
	inline SSDK::IVEngineClient013*  g_pIEngineClient;
	inline SSDK::IEngineTrace*		 g_pIEngineTrace;
	inline SSDK::IGlowObjectManager* g_pGlowObjectManager;
	inline SSDK::ICvarSystem*        g_pCvarManager;
}