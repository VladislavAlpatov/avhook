#include "IClientEntityList.h"

SSDK::CBaseEntity* SSDK::IClientEntityList::GetClientEntity(int index)
{
    typedef CBaseEntity* (__thiscall* GetEntityFunc)(void*, int);
    return GetVirtualFunction<GetEntityFunc>(3)(this, index);
}

std::vector<SSDK::CBaseEntity*> SSDK::IClientEntityList::GetEntityList()
{
    std::vector<SSDK::CBaseEntity*> entListOut;

    for (BYTE i = 1; i < 33; ++i)
    {
	    if (auto pEnt = GetClientEntity(i))
            entListOut.push_back(pEnt);
    }

    return entListOut;
}
