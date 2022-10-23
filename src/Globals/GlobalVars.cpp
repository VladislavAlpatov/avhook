#include "GlobalVars.h"
#include "Interfaces.h"
#include "../Utils/Marker.h"



void GlobalVars::Init()
{
	POLY_MARKER;
	g_pIEntityList    = SSDK::GetInterface<SSDK::IClientEntityList>(xorstr("client.dll"),  xorstr("VClientEntityList003"));
	POLY_MARKER;
	g_pIEngineClient  = SSDK::GetInterface<SSDK::IVEngineClient013>(xorstr("engine.dll"),  xorstr("VEngineClient014"));
	POLY_MARKER;
	g_pIEngineTrace   = SSDK::GetInterface<SSDK::IEngineTrace>(xorstr("engine.dll"),       xorstr("EngineTraceClient004"));
	POLY_MARKER;
	g_pCvarManager	  = SSDK::GetInterface<SSDK::ICvarSystem>(xorstr("vstdlib.dll"),       xorstr("VEngineCvar007"));
	POLY_MARKER;
}