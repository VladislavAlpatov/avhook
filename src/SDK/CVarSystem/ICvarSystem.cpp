#include "ICvarSystem.h"
#include "../../Utils/Marker.h"
SSDK::ConVar* SSDK::ICvarSystem::FindVar(const char* cvarName)
{
	typedef ConVar* (__thiscall* FindVar_t)(void*,const char*);
	POLY_MARKER;


	return GetVirtualFunction<FindVar_t>(16)(this, cvarName);
}
