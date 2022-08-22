#pragma once
#include "GlobalVars.h"
#include "Interfaces.h"
#include "../Utils/memory.h"


SSDK::IGlowObjectManager* GetGlowManager()
{
	// Get addr of instruction "mov edx, dword ptr GlowObjectManager"

	const static uintptr_t inscructionAddr = Memory::FindPattern(xorstr("client.dll"), xorstr("8B 15 ? ? ? ? 85 D2 74 15 A1 ? ? ? ? 52 8B 08 8B 01 FF 50 14 33 D2 89 15 ? ? ? ? C7 05 ? ? ? ? ? ? ? ? 89 15 ? ? ? ? C3 A1 ? ? ? ? A3 ? ? ? ? C3 CC CC 55 8B EC 53 8B 5D 08"));

	// Add 2 to addr since move edx code as 2 bytes
	return *(SSDK::IGlowObjectManager**)(inscructionAddr + 2);
}
void GlobalVars::Init()
{
	g_pIEntityList    = SSDK::GetInterface<SSDK::IClientEntityList>(xorstr("client.dll"),  xorstr("VClientEntityList003"));
	g_pIEngineClient  = SSDK::GetInterface<SSDK::IVEngineClient013>(xorstr("engine.dll"),  xorstr("VEngineClient014"));
	g_pIEngineTrace   = SSDK::GetInterface<SSDK::IEngineTrace>(     xorstr("engine.dll"),  xorstr("EngineTraceClient004"));
	// g_pICvar		  = SSDK::GetInterface<ICvar>(					xorstr("vstdlib.dll"), xorstr("VEngineCvar007"));
	g_pClient         = reinterpret_cast<SSDK::ClientBase*>(GetModuleHandleA(xorstr("client.dll")));
}