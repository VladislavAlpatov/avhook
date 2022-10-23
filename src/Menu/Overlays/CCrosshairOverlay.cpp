/*
 * Copyright (c) 2022.
 * Created by Alpatov Softworks with love in Russia.
 */

#include "CCrosshairOverlay.h"
#include "../../Globals/Settings.h"
#include "../../imgui/imgui_internal.h"
#include "../../Globals/Interfaces.h"
#include "../../SDK/ClientBase.h"

#include <fmt/format.h>

void DrawTexCentered(const ImVec2& pos, ImColor col, const char* text)
{
	auto textPos = pos;
	textPos.x -= ImGui::CalcTextSize(text).x / 2.f;

	ImGui::GetBackgroundDrawList()->AddText(textPos, col, text);
}

static int oldSpeed = 0;

void Update(int rate, int speedVal)
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

	const auto pLocalPlayer = SSDK::ClientBase::GetLocalPlayer();

	const auto pSettings = &GlobalVars::g_AllSettings.m_CrosshairSettings;
	if (!pLocalPlayer or !pSettings->m_bDrawSensors)
		return;

	const ImVec2 vecScreenCenter = ImGui::GetMainViewport()->Size / 2.f;

	auto fRatio = pLocalPlayer->GetHealthPercent() / 100.f;
	if (fRatio > 1.f)
		fRatio = 1.f;

	DrawHealthBar(vecScreenCenter - ImVec2(pSettings->m_iDistance+10, 0), fRatio, 10, 200);
	DrawSpeedBar(vecScreenCenter + ImVec2(pSettings->m_iDistance, 0), 250.f, 10, 200);
}

void CCrosshairOverlay::DrawCrosshair() const
{
	const auto pDrawList = ImGui::GetBackgroundDrawList();

	const auto* pSettings = &GlobalVars::g_AllSettings.m_CrosshairSettings;

	const auto screenCenter = ImGui::GetMainViewport()->Size / 2.f + ImVec2(1, 1);

	pDrawList->AddLine(screenCenter + ImVec2(0, (float)pSettings->m_iSize), screenCenter - ImVec2(0, (float)pSettings->m_iSize), pSettings->m_Color, pSettings->m_iThicness);
	pDrawList->AddLine(screenCenter + ImVec2((float)pSettings->m_iSize, 0), screenCenter - ImVec2((float)pSettings->m_iSize, 0), pSettings->m_Color, pSettings->m_iThicness);


}

void CCrosshairOverlay::DrawHealthBar(const ImVec2& vecDrawPos, float fHealthRatio, float thickness, float fHight) const
{
	const auto pLocalPlayer = SSDK::ClientBase::GetLocalPlayer();


	const ImVec2 topLeft     = vecDrawPos - ImVec2(0, fHight / 2.f);
	const ImVec2 bottomRight = vecDrawPos + ImVec2(thickness, fHight / 2.f);

	auto healthLabel = std::to_string(pLocalPlayer->m_iHealth);

	if (!pLocalPlayer->IsAlive())
		healthLabel = xorstr("[DEAD]");

	const auto pDrawList = ImGui::GetBackgroundDrawList();

	DrawTexCentered(topLeft + ImVec2(thickness / 2.f, -15), pLocalPlayer->GetColorBasedOnHealth(), healthLabel.c_str());


	const auto  top   = topLeft     + ImVec2(1, 1);
	const auto bottom = bottomRight - ImVec2(1, 1);

	auto tmp = bottom - ImVec2(0, fHight / 2.f);
	tmp.x = top.x;

	if (fHealthRatio < 1.f)
		pDrawList->PushClipRect(topLeft +ImVec2(0, fHight*(1.f- fHealthRatio)), bottom);
	pDrawList->AddRectFilledMultiColor(top, bottom - ImVec2(0, fHight / 2.f), ImColor(0, 255, 0), ImColor(0, 255, 0), ImColor(255, 255, 0), ImColor(255, 255, 0));
	pDrawList->AddRectFilledMultiColor(ImVec2(top.x, bottom.y - fHight / 2.f), bottom, ImColor(255, 255, 0), ImColor(255, 255, 0), ImColor(255, 0, 0), ImColor(255, 0, 0));

	if (fHealthRatio < 1.f)
		pDrawList->PopClipRect();


	pDrawList->AddRect(topLeft, bottomRight, ImColor(0, 0, 0));

}

void CCrosshairOverlay::DrawSpeedBar(const ImVec2& vecDrawPos, float fSpeedPerBar, float thickness, float fHeight) const
{
	const auto pDrawList = ImGui::GetBackgroundDrawList();
	const auto pLocalPlayer = SSDK::ClientBase::GetLocalPlayer();

	const ImVec2 topLeft     = vecDrawPos - ImVec2(0, fHeight / 2.f);
	const ImVec2 bottomRight = vecDrawPos + ImVec2(thickness, fHeight / 2.f);

	pDrawList->AddRect(topLeft, bottomRight, ImColor(0, 0, 0));

	const int currentSpeed = roundf(pLocalPlayer->m_vecVelocity.Length2D());

	ImColor speedTextCol = { 255,106,0 };

	if (currentSpeed > oldSpeed)
	{
		pDrawList->AddText(topLeft + ImVec2(20, 0), ImColor(0, 255, 0), xorstr(u8"Λ\nΛ\nΛ"));
		speedTextCol = { 0, 255, 0 };
	}
	else if (currentSpeed < oldSpeed)
	{
		pDrawList->AddText(bottomRight + ImVec2(10, -ImGui::CalcTextSize(xorstr(u8"V\nV\nV")).y), ImColor(255, 0, 0), xorstr(u8"V\nV\nV"));
		speedTextCol = { 255, 0, 0 };
	}
	else if (currentSpeed == 0.f)
	{
		speedTextCol = { 255, 255, 255 };
	}
	DrawTexCentered(topLeft + ImVec2(thickness / 2.f, -12), speedTextCol, std::to_string((int)currentSpeed).c_str());

	float velocityRatio  = roundf(pLocalPlayer->m_vecVelocity.Length2D()) / fSpeedPerBar;
	const int barsCount = (int)ceilf(velocityRatio);
	const ImColor colors[] = { ImColor(255,0, 0), ImColor(0, 255, 0), ImColor(0, 0, 255) };

	for (int i = 0; i < barsCount and velocityRatio > 0.f; i++)
	{
		float currentSpeedBarRatio = 1.f;

		if (velocityRatio < 1.f)
			currentSpeedBarRatio = velocityRatio;

		const float height = fHeight * (1.f - currentSpeedBarRatio);

		pDrawList->AddRectFilled(topLeft + ImVec2(0.f, height) + ImVec2(1, 1), bottomRight - ImVec2(1, 1), colors[i]);

		velocityRatio -= 1.f;
	}

	Update(500, currentSpeed);
}
