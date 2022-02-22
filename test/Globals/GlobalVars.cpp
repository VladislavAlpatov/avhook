#include "GlobalVars.h"

void GlobalVars::Init(HMODULE hModule)
{
	pIEntityList    = SSDK::GetInterface<SSDK::IClientEntityList>(xorstr("client.dll"), xorstr("VClientEntityList003"));
	pIEngineClient  = SSDK::GetInterface<SSDK::IVEngineClient013>(xorstr("engine.dll"), xorstr("VEngineClient014"));
	pIEngineTrace   = SSDK::GetInterface<SSDK::IEngineTrace>(xorstr("engine.dll"), xorstr("EngineTraceClient004"));
	client          = reinterpret_cast<SSDK::ClientBase*>(GetModuleHandle(xorstr("client.dll")));
	engine          = reinterpret_cast<DWORD>(GetModuleHandle(xorstr("engine.dll")));
	GlobalVars::hModule = hModule;
}