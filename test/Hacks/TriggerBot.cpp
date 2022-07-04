#include "TriggerBot.h"
#include "../Globals/Interfaces.h"

using namespace Hacks;

TriggerBot::TriggerBot(Settings::TriggerBotSettings* settings) : CHackingFeature(settings)
{

}


void TriggerBot::Work()
{

	auto pTriggerBotSettings  = (Settings::TriggerBotSettings*)m_pSettings;
	CBaseEntity* localplayer  = GlobalVars::g_pClient->pLocalPlayer;
	CBaseEntity*  entity      = GlobalVars::g_pIEntityList->GetClientEntity(localplayer->m_iCrosshairId);


	if ((localplayer->m_iTeamNum == entity->m_iTeamNum or !entity->IsAlive()) or !localplayer->m_iCrosshairId)
		return;

	Sleep(pTriggerBotSettings->m_iDelay);
	if (pTriggerBotSettings->m_bRageMode)
		//localplayer->AimAt(entity, NULL, this->bone);

	GlobalVars::g_pClient->dwForceAttack = 6;
	Sleep(20);

}