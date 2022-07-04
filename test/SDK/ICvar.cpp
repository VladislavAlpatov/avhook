#include "ICvar.h"

SSDK::IConVar* SSDK::ICvar::FindCvar(const char* cvarName)
{
	typedef IConVar*(__thiscall* FindCvar_t)(LPVOID, const char*);
	return GetVirtualFunction<FindCvar_t>(16)(this, cvarName);
}

bool SSDK::IConVar::SetValue(int nValue)
{
	typedef bool(__thiscall* SetValue_t)(LPVOID, int);
	return GetVirtualFunction<SetValue_t>(3)(this, nValue);
}
