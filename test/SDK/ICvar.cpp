#pragma once
#include "../Utils/memory.h"

#include "ICvar.h"

SSDK::IConVar* SSDK::ICvar::FindCvar(const char* cvarName)
{
	typedef IConVar*(__thiscall* FindCvar_t)(void*, const char*);
	return GetVirtualFunction<FindCvar_t>(16)(this, cvarName);
}

bool SSDK::IConVar::SetValue(float nValue)
{
	typedef bool(__thiscall* SetValue_t)(void*, float);
	static auto func = (SetValue_t)Memory::FindPattern(xorstr("client.dll"), xorstr("56 E8 ? ? ? ? 8B F0 85 F6 74 09"));

	return func(this, nValue);
}
