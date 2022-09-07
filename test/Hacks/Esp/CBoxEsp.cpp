#pragma once

#include "CBoxEsp.h"
#include "../../imgui/imgui_internal.h"
#include "../../Globals/Settings.h"
#include "../../SDK/CBaseEntity.h"

using namespace Esp;
using namespace SSDK;

void CBoxEsp::InternalRenderAt(const CBaseEntity* pEntity)
{
    const auto pSettings = GetSettings<Settings::BoxEspSettings>();

    if (!pSettings->m_bActive)
        return;
    ImColor drawColor = pSettings->m_Color;


    if (pEntity == GlobalVars::g_AllSettings.m_AimBotSettings.m_pCurrentTarget)
        drawColor = ImColor(255, 0, 255);

    else if (pSettings->m_iDrawMode == Settings::DrawMod::AUTO)
        drawColor = pEntity->GetColorBasedOnHealth();

    switch (pSettings->m_iStyle)
    {
    case Settings::BoxEspSettings::Style::Solid:
        DrawSolidBox(pEntity, drawColor, pSettings->m_iThickness);
        break;

    case Settings::BoxEspSettings::Style::Cornered:
        DrawCorneredBox(pEntity, drawColor, (float)pSettings->m_iThickness);
        break;

    default:
        break;
    }
}

void CBoxEsp::DrawSolidBox(const CBaseEntity* pEntity, const ImColor& drawColor, const  float thickness) const 
{
    auto pDrawList = ImGui::GetBackgroundDrawList();

    const auto box = CalcEspBox(pEntity);

    pDrawList->AddLine(box.m_vecTopLeft,    box.m_vecTopRight,    drawColor, thickness);
    pDrawList->AddLine(box.m_vecTopLeft,    box.m_vecBottomLeft,  drawColor, thickness);
    pDrawList->AddLine(box.m_vecBottomLeft, box.m_vecBottomRight, drawColor, thickness);
    pDrawList->AddLine(box.m_vecTopRight,   box.m_vecBottomRight, drawColor, thickness);

}
void CBoxEsp::DrawCorneredBox(const CBaseEntity* pEntity, const ImColor& drawColor,const float thickness) const
{
    auto pDrawList = ImGui::GetBackgroundDrawList();

    const auto box = CalcEspBox(pEntity);
    const auto offset = box.GetSize().y / 7.f;

    pDrawList->AddLine(box.m_vecTopLeft, box.m_vecTopLeft + ImVec2(offset, 0), drawColor, thickness);
    pDrawList->AddLine(box.m_vecTopLeft, box.m_vecTopLeft + ImVec2(0, offset), drawColor, thickness);

    pDrawList->AddLine(box.m_vecTopRight, box.m_vecTopRight - ImVec2(offset, 0), drawColor, thickness);
    pDrawList->AddLine(box.m_vecTopRight, box.m_vecTopRight + ImVec2(0, offset), drawColor, thickness);

    pDrawList->AddLine(box.m_vecBottomLeft, box.m_vecBottomLeft + ImVec2(offset, 0), drawColor, thickness);
    pDrawList->AddLine(box.m_vecBottomLeft, box.m_vecBottomLeft - ImVec2(0, offset), drawColor, thickness);

    pDrawList->AddLine(box.m_vecBottomRight, box.m_vecBottomRight - ImVec2(offset, 0), drawColor, thickness);
    pDrawList->AddLine(box.m_vecBottomRight, box.m_vecBottomRight - ImVec2(0, offset), drawColor, thickness);

}
