#pragma once

#include "CBarsEsp.h"
#include "../../imgui/imgui_internal.h"
#include "../../Globals/GlobalVars.h"

#include <list>

using namespace Esp;

void CBarsEsp::InternalRenderAt(CBaseEntity* pEntity)
{
    POLY_MARKER;

    auto pSettings = GetSettings<Settings::BarEspSettings>();

    auto box = CalcEspBox(pEntity);

    float maxBarLength = box.GetSize().y;


    POLY_MARKER;


    std::list<LineData> lines;

    if (pSettings->m_bDrawHealthBar)
        lines.push_back(LineData(pEntity->GetColorBasedOnHealth(), maxBarLength * (pEntity->m_iHealth / 100.f)));

    if (pSettings->m_bDrawArmorBar)
        lines.push_back(LineData(pSettings->m_ArmorColor, maxBarLength * (pEntity->m_ArmorValue / 100.f)));

    POLY_MARKER;
    auto pDrawList = ImGui::GetBackgroundDrawList();

    ImVec2 barStart = box.m_vecBottomLeft - ImVec2(pSettings->m_iThickness+GlobalVars::settings.m_BoxEspSettings.m_iThickness+2, 0);
    for (auto& line : lines)
    {
        pDrawList->AddRectFilled(barStart, barStart + ImVec2(pSettings->m_iThickness, -maxBarLength), pSettings->m_BackGroundColor);
        pDrawList->AddRectFilled(barStart, barStart + ImVec2(pSettings->m_iThickness, -line.m_fLength), line.m_Color);
        pDrawList->AddRect(barStart + ImVec2(-1, 0), barStart + ImVec2(pSettings->m_iThickness + 1, -maxBarLength), ImColor(0, 0, 0));
        barStart.x -= pSettings->m_iThickness + 2;
    }
}