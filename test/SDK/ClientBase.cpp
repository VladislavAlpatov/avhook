#include "ClientBase.h"
#include "../Utils/memory.h"

matrix4x4 SSDK::ClientBase::GetViewMatrix()
{
	static matrix4x4* addr = NULL;

	if (addr)
		return *addr;


	addr = *(matrix4x4**)(Memory::FindPattern(xorstr("client.dll"), xorstr("0F 10 05 ? ? ? ? 8D 85 ? ? ? ? B9 ? ? ? ?")) + 3);
	addr = (matrix4x4*)( (uintptr_t)addr + 0xb0 );

	return *addr;

}

SSDK::CBaseEntity* SSDK::ClientBase::GetLocalPlayer()
{

	return nullptr;
}
