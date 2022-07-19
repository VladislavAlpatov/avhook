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

static float oldSpeed = 0.f;

void Update(int rate, float speedVal)
{
	static auto oldTime = GetTickCount64();

	auto newTime = GetTickCount64();

	if (newTime - oldTime >= rate)
	{
		oldTime = newTime;
		oldSpeed = speedVal;
	}
}

void CCrosshairOverlay::Render()
{
	auto pDrawList = ImGui::GetBackgroundDrawList();

	const auto* pSettings = &GlobalVars::g_AllSettings.m_CrosshairSettings;

	auto screenCenter = ImGui::GetMainViewport()->Size / 2.f + ImVec2(1, 1);

	pDrawList->AddLine(screenCenter + ImVec2(0, (float)pSettings->m_iSize), screenCenter - ImVec2(0, (float)pSettings->m_iSize), pSettings->m_Color, pSettings->m_iThicness);
	pDrawList->AddLine(screenCenter + ImVec2((float)pSettings->m_iSize, 0), screenCenter - ImVec2((float)pSettings->m_iSize, 0), pSettings->m_Color, pSettings->m_iThicness);

	
	auto pLocalPlayer = GlobalVars::g_pClient->pLocalPlayer;
	
	if (!pLocalPlayer or !pSettings->m_bDrawSensors)
		return;


	float healthRatio = pLocalPlayer->GetHealthPercent() / 100.f;
	if (healthRatio > 1.f) healthRatio = 1.f;

	ImVec2 healthBarStart = screenCenter - ImVec2(pSettings->m_iDistance, 100);
	ImVec2 healthBarEnd =   screenCenter + ImVec2(-pSettings->m_iDistance, 100);

	auto healthLabel = std::to_string(pLocalPlayer->m_iHealth);

	if (pLocalPlayer->m_iHealth == 0)
		healthLabel = xorstr("DEAD");

	DrawTexCentered(healthBarStart - ImVec2(5, 6), pLocalPlayer->GetColorBasedOnHealth(), healthLabel.c_str());
	DrawOutlinedLine(healthBarStart, healthBarEnd, healthRatio, pLocalPlayer->GetColorBasedOnHealth(), 10);


	float currentSpeed = pLocalPlayer->m_vecVelocity.Length2D();

	ImVec2 speedBarStart = screenCenter + ImVec2(pSettings->m_iDistance+10, -100);
	ImVec2 speedBarEnd = screenCenter + ImVec2(pSettings->m_iDistance+10, 100);

	float speedRatio = currentSpeed / 500.f;

	if (speedRatio > 1.f) speedRatio = 1.f;

	auto gainSpeedIndicator = xorstr(u8"Λ\nΛ\nΛ");
	auto loosSpeedIndicator = xorstr("V\nV\nV");

	ImColor speedTextCol = { 255,106,0};

	if (roundf(currentSpeed) > roundf(oldSpeed))
	{
		pDrawList->AddText(speedBarStart + ImVec2(10, 0), ImColor(0, 255, 0), gainSpeedIndicator);
		speedTextCol = { 0, 255, 0 };
	}
	else if (roundf(currentSpeed) < roundf(oldSpeed))
	{
		pDrawList->AddText(speedBarEnd + ImVec2(10, -ImGui::CalcTextSize(loosSpeedIndicator).y), ImColor(255, 0, 0), loosSpeedIndicator);
		speedTextCol = { 255, 0, 0 };
	}
	else if (roundf(currentSpeed) == 0.f)
	{
		speedTextCol = { 255, 255, 255 };
	}
	DrawTexCentered(speedBarStart - ImVec2(5, 6), speedTextCol, std::to_string((int)roundf(currentSpeed)).c_str());


	Update(500, currentSpeed);

	DrawOutlinedLine(speedBarStart, speedBarEnd, speedRatio, pSettings->m_SpeedBarCol, 10);
}
