#include "CCrosshairOverlay.h"
#include "../../Globals/Settings.h"
#include "../../imgui/imgui_internal.h"

void CCrosshairOverlay::Render()
{
	auto pDrawList = ImGui::GetBackgroundDrawList();

	const auto* pSettings = &GlobalVars::g_AllSettings.m_CrosshairSettings;

	auto screenCenter = ImGui::GetMainViewport()->Size / 2.f + ImVec2(1, 1);

	pDrawList->AddLine(screenCenter + ImVec2(0, (float)pSettings->m_iSize), screenCenter - ImVec2(0, (float)pSettings->m_iSize), pSettings->m_Color, pSettings->m_iThicness);
	pDrawList->AddLine(screenCenter + ImVec2((float)pSettings->m_iSize, 0), screenCenter - ImVec2((float)pSettings->m_iSize, 0), pSettings->m_Color, pSettings->m_iThicness);

}
