#pragma once
#include "CBaseEntity.h"
#include "AbstractInterface.h"
#include "../Utils/memory.h"
#include <vector>

namespace SSDK
{
	class IClientEntityList : public CAbstractInterface
	{
	public:
		CBaseEntity* GetClientEntity(int entnum)
		{
			typedef CBaseEntity* (__thiscall* GetEntityFunc)(void*, int);
			return GetVirtualFunction<GetEntityFunc>(3)(this, entnum);
		}
		std::vector<CBaseEntity*> GetEntityList();
	};
}
