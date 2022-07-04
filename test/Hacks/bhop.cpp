#include "bhop.h"
#include "../Globals/Interfaces.h"

using namespace Hacks;


void CBunnyHop::Work()
{
	if (!IsShouldBeActivated())
		return;

	auto state = GlobalVars::g_pClient->pLocalPlayer->m_fFlags;

	if ((state == CBaseEntity::FLAGS::ON_GROUND or state == CBaseEntity::FLAGS::ON_GROUND_DUCK
		or state == CBaseEntity::FLAGS::IN_WATER or state == CBaseEntity::FLAGS::IN_WATER_DUCK))
	{
		GlobalVars::g_pClient->dwForceJump = 6;
	}
	else if ((state == CBaseEntity::FLAGS::IN_AIR or state == CBaseEntity::FLAGS::IN_AIR_DUCK) and GlobalVars::g_pClient->dwForceJump == 5)
	{
		GlobalVars::g_pClient->dwForceJump = 6;
	}
}
CBunnyHop::CBunnyHop(Settings::CBunnyHopSettings* pSettings) : CHackingFeature(pSettings)
{

}