#include "ClientBase.h"
#include "../Utils/memory.h"
#include "../Utils/Marker.h"

matrix SSDK::ClientBase::GetViewMatrix()
{
	POLY_MARKER;
	static float* pViewMatrix = nullptr;

	if (pViewMatrix)
		return { 4, 4, pViewMatrix };


	const auto address = *(uintptr_t*)(memory::FindPattern(xorstr("client.dll"), xorstr("0F 10 05 ? ? ? ? 8D 85 ? ? ? ? B9")) + 3);
	pViewMatrix = (float*)(address + 0xb0 );
	POLY_MARKER;
	return { 4, 4, pViewMatrix };

}

SSDK::CBaseEntity* SSDK::ClientBase::GetLocalPlayer()
{
	POLY_MARKER;
	static auto pTraceFilter = *(SSDK::CBaseEntity***)(memory::FindPattern(xorstr("client.dll"), xorstr("8D 34 85 ? ? ? ? 89 15 ? ? ? ? 8B 41 08 8B 48 04 83 F9 FF")) + 3);

	return pTraceFilter[1];
}
