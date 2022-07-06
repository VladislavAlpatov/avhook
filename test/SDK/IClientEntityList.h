#pragma once
#include "CBaseEntity.h"
#include "IBaseInterface.h"
#include <vector>

namespace SSDK
{
	class IClientEntityList : public IBaseInterface
	{
	public:
		CBaseEntity* GetClientEntity(int entnum);
		std::vector<CBaseEntity*> GetEntityList();
	};
}
