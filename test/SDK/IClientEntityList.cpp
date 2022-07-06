#include "IClientEntityList.h"

SSDK::CBaseEntity* SSDK::IClientEntityList::GetClientEntity(int entnum)
{
    typedef CBaseEntity* (__thiscall* GetEntityFunc)(void*, int);
    return GetVirtualFunction<GetEntityFunc>(3)(this, entnum);
}

std::vector<SSDK::CBaseEntity*> SSDK::IClientEntityList::GetEntityList()
{
    std::vector<SSDK::CBaseEntity*> entListOut;

    for (BYTE i = 1; i < 33; ++i)
    {
        auto pEnt = GetClientEntity(i);

        if (pEnt)
            entListOut.push_back(pEnt);
    }

    return entListOut;
}
