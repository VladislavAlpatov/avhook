//========= Copyright Alpatov Softworks, All rights reserved. ============//
//
// Purpose: Provide ESP info as labels such as: health, distance, etc....
//
//===============================================================================



#include "CLabel.h"
#include "../../../Globals/Settings.h"
#include "../../../Globals/Interfaces.h"
#include "../../../Utils/Math/Math.h"
#include "../../../SDK/ClientBase.h"
#include "../../../Utils/Marker.h"

#include <fmt/format.h>

using namespace CLabels;



bool CNameLabel::Render(const ImVec2& vecPosition, const SSDK::CBaseEntity* pEntity) const
{
	POLY_MARKER;
	const auto pDrawList = ImGui::GetBackgroundDrawList();
	pDrawList->AddText(vecPosition, m_Color, GlobalVars::g_pIEngineClient->GetPlayerInfo(pEntity->m_Index).szName);
	return true;
}
bool CHealthLabel::Render(const ImVec2& vecPosition, const SSDK::CBaseEntity* pEntity) const
{
	POLY_MARKER;
	const auto pDrawList = ImGui::GetBackgroundDrawList();
	pDrawList->AddText(vecPosition, pEntity->GetColorBasedOnHealth(), fmt::format(xorstr("Health: {}/100"), pEntity->m_iHealth).c_str());

	return true;
}
bool CArmorLabel::Render(const ImVec2& vecPosition, const SSDK::CBaseEntity* pEntity) const
{
	POLY_MARKER;
	const auto pDrawList = ImGui::GetBackgroundDrawList();
	pDrawList->AddText(vecPosition, m_Color, fmt::format(xorstr("Armor: {}/100"), pEntity->m_ArmorValue).c_str());

	return true;
}

bool CDistanceLabel::Render(const ImVec2& vecPosition, const SSDK::CBaseEntity* pEntity) const
{
	POLY_MARKER;
	static auto pDrawList = ImGui::GetBackgroundDrawList();
	const auto distance = SSDK::ClientBase::GetLocalPlayer()->CalcDistanceToEntity(pEntity);
	pDrawList->AddText(vecPosition, m_Color, fmt::format(xorstr("Distance: {}m"), (int)Utils::HamToMet(distance)).c_str());

	return true;
}
bool CVisibilityLabel::Render(const ImVec2& vecPosition, const SSDK::CBaseEntity* pEntity) const
{
	POLY_MARKER;
	if (!pEntity->m_IsVisible)
		return false;

	const auto pDrawList = ImGui::GetBackgroundDrawList();
	pDrawList->AddText(vecPosition, m_Color, xorstr("*VISIBLE*"));

	return true;
}
bool CAimBotTargetLabel::Render(const ImVec2& vecPosition, const SSDK::CBaseEntity* pEntity) const
{
	POLY_MARKER;
	if (pEntity != GlobalVars::g_AllSettings.m_AimBotSettings.m_pCurrentTarget)
		return false;
	POLY_MARKER;
	const auto pDrawList = ImGui::GetBackgroundDrawList();
	pDrawList->AddText(vecPosition, m_Color, xorstr("*AIMBOT TARGET*"));

	return true;
}

CLabels::CBaseLabel::CBaseLabel(const std::string& name, const bool bActive, const ImColor& color)
{
	POLY_MARKER;

	m_sName   = name;
	m_bActive = bActive;
	m_Color   = color;
}
