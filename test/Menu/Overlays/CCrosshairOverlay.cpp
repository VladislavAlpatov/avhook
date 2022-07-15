#include "CCrosshairOverlay.h"
#include "../../Globals/Settings.h"
#include "../../imgui/imgui_internal.h"
#include "../../Globals/Interfaces.h"
#include <fmt/format.h>

void DrawOutlinedLine(const ImVec2& p1, const ImVec2& p2, float ratio, ImColor col, float thickness = 1.f)
{
	auto pDrawList = ImGui::GetBackgroundDrawList();

	pDrawList->AddRect(p1 - ImVec2(thickness+1, 1), p2+ImVec2(1, 1), ImColor(0,0,0), 0.f, NULL);

	auto pos = p2 - ImVec2(0, ratio * abs(p2.y - p1.y));


	pDrawList->AddRectFilled(pos, p2-ImVec2(thickness, 0), col);
	

}

void DrawTexCentered(const ImVec2& pos, ImColor col, const char* text)
{
	auto textPos = pos - ImGui::CalcTextSize(text) / 2.f;
	ImGui::GetBackgroundDrawList()->AddText(textPos, col, text);
}

void CCrosshairOverlay::Render()
{
	auto pDrawList = ImGui::GetBackgroundDrawList();

	const auto* pSettings = &GlobalVars::g_AllSettings.m_CrosshairSettings;

	auto screenCenter = ImGui::GetMainViewport()->Size / 2.f + ImVec2(1, 1);

	pDrawList->AddLine(screenCenter + ImVec2(0, (float)pSettings->m_iSize), screenCenter - ImVec2(0, (float)pSettings->m_iSize), pSettings->m_Color, pSettings->m_iThicness);
	pDrawList->AddLine(screenCenter + ImVec2((float)pSettings->m_iSize, 0), screenCenter - ImVec2((float)pSettings->m_iSize, 0), pSettings->m_Color, pSettings->m_iThicness);

	
	auto pLocalPlayer = GlobalVars::g_pClient->pLocalPlayer;
	
	if (!pLocalPlayer)
		return;
	

	float healthRatio = pLocalPlayer->GetHealthPercent() / 100.f;

	DrawOutlinedLine(screenCenter - ImVec2(pSettings->m_iDistance, 100), screenCenter + ImVec2(-pSettings->m_iDistance, 100),healthRatio, pLocalPlayer->GetColorBasedOnHealth(), 10);


	auto start = screenCenter + ImVec2(100, -100);
	DrawTexCentered(start - ImVec2(5, 6), ImColor(255, 255, 255), std::to_string((int)pLocalPlayer->m_vecVelocity.Length2D()).c_str());

	DrawOutlinedLine(screenCenter + ImVec2(100, -100), screenCenter + ImVec2(pSettings->m_iDistance, 100), pLocalPlayer->m_vecVelocity.Length2D() / 500.f, ImColor(0, 0, 255), 10);
}
