#include "CGlowEsp.h"
#include "../../Globals/Interfaces.h"
#include "../../Globals/Settings.h"





void Esp::CGlowEsp::RenderAt(SSDK::GlowObjectDefinition& glowObj)
{
	const auto pSettings    = GetSettings<Settings::CGlowEspSettings>();
	auto pLocalPlayer = SSDK::ClientBase::GetLocalPlayer();

	glowObj.m_fGlowAlphaMax = (pSettings->m_iDrawMode == Settings::CGlowEspSettings::Static) ? pSettings->m_fGlowSize : CalcAdaptiveGlowBrightness(glowObj.m_pEntity, pSettings->m_iMaxDistance);

	glowObj.m_iGlowStyle = pSettings->m_iStyle;
	glowObj.m_bFullBloomRender = false;
	if (GlobalVars::g_AllSettings.m_AimBotSettings.m_pCurrentTarget != glowObj.m_pEntity)
		glowObj.SetColor(pSettings->m_Color);
	else
		glowObj.SetColor(ImColor(255, 0, 255));
}

float Esp::CGlowEsp::CalcAdaptiveGlowBrightness(const SSDK::CBaseEntity* pEntity, float fMaxDistance)
{
	auto pLocalPlayer = SSDK::ClientBase::GetLocalPlayer();

	return  1.f - pLocalPlayer->m_vecOrigin.DistTo(pEntity->m_vecOrigin) / fMaxDistance;
}
