#include "IVEngineClient013.h"
using namespace SSDK;

player_info_s IVEngineClient013::GetPlayerInfo(int iEntIndex)
{
	player_info_s info;
	typedef player_info_s* (__thiscall* GetPlayerInfT)(void*,int, player_info_t*);
	GetVirtualFunction<GetPlayerInfT>(8)(this, iEntIndex, &info);
	return info;
}
bool IVEngineClient013::Con_IsVisible()
{
	typedef bool (__thiscall* Con_IsVisibleT)(void*);
	return GetVirtualFunction<Con_IsVisibleT>(11)(this);
}
int IVEngineClient013::GetLocalPlayer()
{
	typedef int(__thiscall* GetLocalPlayer)(void*);
	return GetVirtualFunction<GetLocalPlayer>(12)(this);
}
bool IVEngineClient013::IsInGame()
{
	typedef bool(__thiscall* IsInGameT)(void*);
	return GetVirtualFunction<IsInGameT>(26)(this);
}
bool IVEngineClient013::IsConnected()
{
	typedef bool(__thiscall* IsConnectedT)(void*);
	return GetVirtualFunction<IsConnectedT>(27)(this);
}