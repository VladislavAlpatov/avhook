#include "ClientBase.h"
#include "../Utils/memory.h"

CMatrix4x4 SSDK::ClientBase::GetViewMatrix()
{
	static CMatrix4x4* pViewMatrix = nullptr;

	if (pViewMatrix)
		return *pViewMatrix;


	const auto address = *(uintptr_t*)(Memory::FindPattern(xorstr("client.dll"), xorstr("0F 10 05 ? ? ? ? 8D 85 ? ? ? ? B9")) + 3);
	pViewMatrix = (CMatrix4x4*)(address + 0xb0 );

	return *pViewMatrix;

}

SSDK::CBaseEntity* SSDK::ClientBase::GetLocalPlayer()
{
	static auto pTraceFilter = *(SSDK::CBaseEntity***)(Memory::FindPattern(xorstr("client.dll"), xorstr("8D 34 85 ? ? ? ? 89 15 ? ? ? ? 8B 41 08 8B 48 04 83 F9 FF")) + 3);

	return pTraceFilter[1];
}
