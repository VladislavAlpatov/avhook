#include "TriggerBot.h"

TriggerBot::TriggerBot(TriggerBotSettings* settings) : CHackingFeature(settings)
{

}
void TriggerBot::Work()
{
	if (!IsShouldBeActivated())
		return;

	auto pTriggerBotSettings = (TriggerBotSettings*)m_pSettings;
	CLocalPlayer* localplayer = GlobalVars::client->pLocalPlayer;
	CBaseEntity*  entity      = GlobalVars::pIEntityList->GetClientEntity(localplayer->m_iCrosshairId);


	if ((localplayer->m_iTeamNum == entity->m_iTeamNum or !entity->IsAlive()) or !localplayer->m_iCrosshairId)
		return;

	Sleep(pTriggerBotSettings->m_iDelay);
	if (pTriggerBotSettings->m_bRageMode)
		localplayer->AimAt(entity, NULL, this->bone);

	GlobalVars::client->dwForceAttack = 6;
	Sleep(20);

}