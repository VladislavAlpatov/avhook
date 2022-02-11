#include "bhop.h"

void BunnyHop::Work()
{
	if (!IsShouldBeActivated())
		return;

	auto state = GlobalVars::client->pLocalPlayer->m_fFlags;

	if ((state == CBaseEntity::FLAGS::ON_GROUND or state == CBaseEntity::FLAGS::ON_GROUND_DUCK
		or state == CBaseEntity::FLAGS::IN_WATER or state == CBaseEntity::FLAGS::IN_WATER_DUCK))
	{
		GlobalVars::client->dwForceJump = 6;
	}
	else if ((state == CBaseEntity::FLAGS::IN_AIR or state == CBaseEntity::FLAGS::IN_AIR_DUCK) and GlobalVars::client->dwForceJump == 5)
	{
		GlobalVars::client->dwForceJump = 6;
	}
}
BunnyHop::BunnyHop(CBunnyHopSettings* pSettings) : CHackingFeature(pSettings)
{

}