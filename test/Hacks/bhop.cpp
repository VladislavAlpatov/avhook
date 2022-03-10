#include "bhop.h"
using namespace Hacks;


void ÑBunnyHop::Work()
{
	if (!IsShouldBeActivated())
		return;

	auto state = GlobalVars::pClient->pLocalPlayer->m_fFlags;

	if ((state == CBaseEntity::FLAGS::ON_GROUND or state == CBaseEntity::FLAGS::ON_GROUND_DUCK
		or state == CBaseEntity::FLAGS::IN_WATER or state == CBaseEntity::FLAGS::IN_WATER_DUCK))
	{
		GlobalVars::pClient->dwForceJump = 6;
	}
	else if ((state == CBaseEntity::FLAGS::IN_AIR or state == CBaseEntity::FLAGS::IN_AIR_DUCK) and GlobalVars::pClient->dwForceJump == 5)
	{
		GlobalVars::pClient->dwForceJump = 6;
	}
}
ÑBunnyHop::ÑBunnyHop(Settings::CBunnyHopSettings* pSettings) : CHackingFeature(pSettings)
{

}