#include "GlobalVars.h"

void GlobalVars::Init(HMODULE hModule)
{
	pIEntityList   = GetInterface<IClientEntityList>(xorstr("client.dll"), xorstr("VClientEntityList003"));
	pIEngineClient = GetInterface<IVEngineClient013>(xorstr("engine.dll"), xorstr("VEngineClient014"));
	pIEngineTrace   = GetInterface<IEngineTrace>(xorstr("engine.dll"), xorstr("EngineTraceClient004"));
	client        = reinterpret_cast<ClientBase*>(GetModuleHandle(xorstr("client.dll")));
	engine        = reinterpret_cast<DWORD>(GetModuleHandle(xorstr("engine.dll")));
	GlobalVars::hModule = hModule;
}