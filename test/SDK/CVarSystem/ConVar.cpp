#include "ConVar.h"
#include "../../Utils/Marker.h"

std::string SSDK::ConVar::GetCvarName() const
{
	typedef const char*(__thiscall* GetCvarName_t)();
	POLY_MARKER;
	return GetVirtualFunction<GetCvarName_t>(4)();
}

float SSDK::ConVar::GetValueAsFloat() const
{
	POLY_MARKER;
	uintptr_t decryptedVal = *(uintptr_t*)(&m_pParentCvar->m_fValue) ^ (uintptr_t)this;
	return *(float*)(&decryptedVal);
}

int SSDK::ConVar::GetValueAsInt() const
{
	return (int)(m_pParentCvar->m_iValue^ (int)(this));
}

std::string SSDK::ConVar::GetString() const
{
	POLY_MARKER;

	char const* szValue = m_pParentCvar->m_String;
	return szValue ? szValue : "";
}

void SSDK::ConVar::SetValue(const char* value)
{
	typedef const char* (__thiscall* SetValue_t)(void*,const char*);

	GetVirtualFunction<SetValue_t>(14)(this, value);
}

void SSDK::ConVar::SetValue(float value)
{
	typedef const char* (__thiscall* SetValue_t)(void*,float);

	GetVirtualFunction<SetValue_t>(15)(this, value);
}

void SSDK::ConVar::SetValue(int value)
{
	typedef const char* (__thiscall* SetValue_t)(void*,int);

	GetVirtualFunction<SetValue_t>(16)(this, value);
}
