#include "CLabel.h"
#include "../../../Globals/GlobalVars.h"
#include <fmt/format.h>


using namespace CLabels;



bool CNameLabel::Render(const ImVec2& vecPosition, const SSDK::CBaseEntity* pEntity)
{
	auto pDrawList = ImGui::GetBackgroundDrawList();
	pDrawList->AddText(vecPosition, m_Color, GlobalVars::pIEngineClient->GetPlayerInfo(pEntity->m_Index).szName);
	return true;
}
bool CHealthLabel::Render(const ImVec2& vecPosition, const SSDK::CBaseEntity* pEntity)
{
	auto pDrawList = ImGui::GetBackgroundDrawList();
	pDrawList->AddText(vecPosition, pEntity->GetColorBasedOnHealth(), fmt::format(xorstr("Health: {}/100"), pEntity->m_iHealth).c_str());

	return true;
}
bool CArmorLabel::Render(const ImVec2& vecPosition, const SSDK::CBaseEntity* pEntity)
{
	auto pDrawList = ImGui::GetBackgroundDrawList();
	pDrawList->AddText(vecPosition, m_Color, fmt::format(xorstr("Armor: {}/100"), pEntity->m_ArmorValue).c_str());

	return true;
}
bool CDistanceLabel::Render(const ImVec2& vecPosition, const SSDK::CBaseEntity* pEntity)
{
	auto pDrawList = ImGui::GetBackgroundDrawList();
	pDrawList->AddText(vecPosition, m_Color, fmt::format(xorstr("Distance: {}m"), (int)(GlobalVars::pClient->pLocalPlayer->CalcDistaceToEntity(pEntity) * 2.54f / 100.f)).c_str());

	return true;
}
bool CVisibilityLabel::Render(const ImVec2& vecPosition, const SSDK::CBaseEntity* pEntity)
{
	auto pDrawList = ImGui::GetBackgroundDrawList();
	pDrawList->AddText(vecPosition, m_Color, xorstr("*VISIBLE*"));

	return true;
}
bool CAimBotTargetLabel::Render(const ImVec2& vecPosition, const SSDK::CBaseEntity* pEntity)
{
	if (pEntity != GlobalVars::settings.m_AimBotSettings.m_pCurrentTarget)
		return false;

	auto pDrawList = ImGui::GetBackgroundDrawList();
	pDrawList->AddText(vecPosition, m_Color, xorstr("*AIMBOT TARGET*"));

	return true;
}