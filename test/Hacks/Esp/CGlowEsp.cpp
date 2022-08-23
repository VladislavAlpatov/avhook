#include "CGlowEsp.h"
#include "../../Globals/Interfaces.h"
#include "../../Globals/Settings.h"





void Esp::CGlowEsp::RenderAt(SSDK::GlowObjectDefinition& glowObj)
{
	auto pSettings = GetSettings<Settings::CGlowEspSettings>();
	glowObj.m_fGlowAlphaMax = pSettings->m_fGlowSize;
	glowObj.m_iGlowStyle = pSettings->m_iStyle;


	if (GlobalVars::g_AllSettings.m_AimBotSettings.m_pCurrentTarget != glowObj.m_pEntity)
		glowObj.SetColor(pSettings->m_Color);
	else
		glowObj.SetColor(ImColor(255, 0, 255));
}
