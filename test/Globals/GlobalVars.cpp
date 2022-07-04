#pragma once
#include "GlobalVars.h"
#include "Interfaces.h"
#include "Settings.h"
#include "DirectX9.h"

void GlobalVars::Init()
{
	g_pIEntityList    = SSDK::GetInterface<SSDK::IClientEntityList>(xorstr("client.dll"), xorstr("VClientEntityList003"));
	g_pIEngineClient  = SSDK::GetInterface<SSDK::IVEngineClient013>(xorstr("engine.dll"), xorstr("VEngineClient014"));
	g_pIEngineTrace   = SSDK::GetInterface<SSDK::IEngineTrace>(xorstr("engine.dll"), xorstr("EngineTraceClient004"));
	g_pClient         = reinterpret_cast<SSDK::ClientBase*>(GetModuleHandleA(xorstr("client.dll")));
}