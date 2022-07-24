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
	auto textPos = pos;
	textPos.x -= ImGui::CalcTextSize(text).x / 2.f;

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
	DrawCrosshair();

	auto pLocalPlayer = GlobalVars::g_pClient->pLocalPlayer;

	auto pSettings = &GlobalVars::g_AllSettings.m_CrosshairSettings;
	if (!pLocalPlayer or !pSettings->m_bDrawSensors)
		return;

	ImVec2 vecScreenCenter = ImGui::GetMainViewport()->Size / 2.f;


	DrawHealthBar(vecScreenCenter - ImVec2(pSettings->m_iDistance, 0), pLocalPlayer->GetHealthPercent() / 100.f, 10, 200);

	/*DrawTexCentered(healthBarStart - ImVec2(5, 6), pLocalPlayer->GetColorBasedOnHealth(), healthLabel.c_str());
	DrawOutlinedLine(healthBarStart, healthBarEnd, healthRatio, pLocalPlayer->GetColorBasedOnHealth(), 10);


	float currentSpeed = roundf(pLocalPlayer->m_vecVelocity.Length2D());

	ImVec2 speedBarStart = screenCenter + ImVec2(pSettings->m_iDistance+10, -100);
	ImVec2 speedBarEnd = screenCenter + ImVec2(pSettings->m_iDistance+10, 100);

	float speedRatio = currentSpeed / 500.f;

	if (speedRatio > 1.f) speedRatio = 1.f;

	auto gainSpeedIndicator = xorstr(u8"Λ\nΛ\nΛ");
	auto loosSpeedIndicator = xorstr("V\nV\nV");

	ImColor speedTextCol = { 255,106,0};

	if (currentSpeed > oldSpeed)
	{
		pDrawList->AddText(speedBarStart + ImVec2(10, 0), ImColor(0, 255, 0), gainSpeedIndicator);
		speedTextCol = { 0, 255, 0 };
	}
	else if (currentSpeed < oldSpeed)
	{
		pDrawList->AddText(speedBarEnd + ImVec2(10, -ImGui::CalcTextSize(loosSpeedIndicator).y), ImColor(255, 0, 0), loosSpeedIndicator);
		speedTextCol = { 255, 0, 0 };
	}
	else if (currentSpeed == 0.f)
	{
		speedTextCol = { 255, 255, 255 };
	}
	DrawTexCentered(speedBarStart - ImVec2(5, 6), speedTextCol, std::to_string((int)currentSpeed).c_str());


	Update(500, currentSpeed);

	DrawOutlinedLine(speedBarStart, speedBarEnd, speedRatio, pSettings->m_SpeedBarCol, 10);*/
}

void CCrosshairOverlay::DrawCrosshair() const
{
	auto pDrawList = ImGui::GetBackgroundDrawList();

	const auto* pSettings = &GlobalVars::g_AllSettings.m_CrosshairSettings;

	auto screenCenter = ImGui::GetMainViewport()->Size / 2.f + ImVec2(1, 1);

	pDrawList->AddLine(screenCenter + ImVec2(0, (float)pSettings->m_iSize), screenCenter - ImVec2(0, (float)pSettings->m_iSize), pSettings->m_Color, pSettings->m_iThicness);
	pDrawList->AddLine(screenCenter + ImVec2((float)pSettings->m_iSize, 0), screenCenter - ImVec2((float)pSettings->m_iSize, 0), pSettings->m_Color, pSettings->m_iThicness);


}

void CCrosshairOverlay::DrawHealthBar(const ImVec2& vecDrawPos, float fHealthRatio, float thickness, float fHight) const
{
	const auto pLocalPlayer = GlobalVars::g_pClient->pLocalPlayer;
	float healthRatio = pLocalPlayer->GetHealthPercent() / 100.f;

	if (healthRatio > 1.f) healthRatio = 1.f;


	ImVec2 topLeft     = vecDrawPos - ImVec2(0, fHight / 2.f);
	ImVec2 bottomRight = vecDrawPos + ImVec2(thickness, fHight / 2.f);

	auto healthLabel = std::to_string(pLocalPlayer->m_iHealth);

	if (!pLocalPlayer->IsAlive())
		healthLabel = xorstr("[DEAD]");

	auto pDrawList = ImGui::GetBackgroundDrawList();

	DrawTexCentered(topLeft + ImVec2(thickness / 2.f, -15), pLocalPlayer->GetColorBasedOnHealth(), healthLabel.c_str());
	pDrawList->AddRectFilled(topLeft+ImVec2(1,1), bottomRight-ImVec2(1, 1), pLocalPlayer->GetColorBasedOnHealth());

	pDrawList->AddRect(topLeft, bottomRight, ImColor(0, 0, 0));

}
