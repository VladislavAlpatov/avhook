#pragma once

#include "CBoxEsp.h"
#include "../../imgui/imgui_internal.h"
#include <algorithm>
#include "../../Globals/GlobalVars.h"

#include "../../SDK/CBaseEntity.h"
using namespace Esp;
using namespace SSDK;

void CBoxEsp::InternalRenderAt(CBaseEntity* pEntity)
{
    auto pSettings = GetSettings<Settings::BoxEspSettings>();

    if (!pSettings->m_bActive)
        return;
    ImColor drawColor = pSettings->m_Color;


    if (pEntity == GlobalVars::settings.m_AimBotSettings.m_pCurrentTarget)
        drawColor = ImColor(255, 0, 255);

    else if (pSettings->m_iDrawMode == Settings::DrawMod::AUTO)
        drawColor = pEntity->GetColorBasedOnHealth();

    switch (pSettings->m_iStyle)
    {
    case Settings::BoxEspSettings::Style::Solid:
        DrawSolidBox(pEntity, drawColor, pSettings->m_iThickness);
        break;

    case Settings::BoxEspSettings::Style::Cornered:
        DrawCorneredBox(pEntity, drawColor, pSettings->m_iThickness);
        break;

    default:
        break;
    }
}

void CBoxEsp::DrawSolidBox(const CBaseEntity* pEntity, const ImColor& drawColor, int thickness)
{
    auto pDrawList = ImGui::GetBackgroundDrawList();

    auto box = CalcEspBox(pEntity);

    ImVec2 topLeft = box.m_vecTop - ImVec3(box.m_Width / 2.f, 0, 0);
    ImVec2 topRight = box.m_vecTop + ImVec3(box.m_Width / 2.f, 0, 0);


    ImVec2 bottomRight = ImVec3(box.m_vecTop.x, box.m_vecBottom.y, 0) + ImVec3(box.m_Width / 2.f, 0, 0);

    ImVec2 bottomLeft = ImVec3(box.m_vecTop.x, box.m_vecBottom.y, 0) - ImVec3(box.m_Width / 2.f, 0, 0);


    pDrawList->AddLine(topLeft, topRight, drawColor, (float)thickness);
    pDrawList->AddLine(topLeft, bottomLeft, drawColor, (float)thickness);

    pDrawList->AddLine(bottomLeft, bottomRight, drawColor, (float)thickness);
    pDrawList->AddLine(topRight, bottomRight, drawColor, (float)thickness);

}
void CBoxEsp::DrawCorneredBox(const CBaseEntity* pEntity, const ImColor& drawColor,const  int thickness)
{
    auto pDrawList = ImGui::GetBackgroundDrawList();

    auto box = CalcEspBox(pEntity);

    ImVec2 topLeft  = box.m_vecTop - ImVec3(box.m_Width / 2.f, 0, 0);
    ImVec2 topRight = box.m_vecTop + ImVec3(box.m_Width / 2.f, 0, 0);



    ImVec2 bottomRight = ImVec3(box.m_vecTop.x, box.m_vecBottom.y, 0) + ImVec3(box.m_Width / 2.f, 0, 0);

    ImVec2 bottomLeft  = ImVec3(box.m_vecTop.x, box.m_vecBottom.y, 0) - ImVec3(box.m_Width / 2.f, 0, 0);

    auto offset = abs(box.m_vecTop.y - box.m_vecBottom.y) / 7.f;

    pDrawList->AddLine(topLeft, topLeft + ImVec2(offset, 0), drawColor, (float)thickness);
    pDrawList->AddLine(topLeft, topLeft + ImVec2(0, offset), drawColor, (float)thickness);

    pDrawList->AddLine(topRight, topRight - ImVec2(offset, 0), drawColor, (float)thickness);
    pDrawList->AddLine(topRight, topRight + ImVec2(0, offset), drawColor, (float)thickness);

    pDrawList->AddLine(bottomLeft, bottomLeft + ImVec2(offset, 0), drawColor, (float)thickness);
    pDrawList->AddLine(bottomLeft, bottomLeft - ImVec2(0, offset), drawColor, (float)thickness);

    pDrawList->AddLine(bottomRight, bottomRight - ImVec2(offset, 0), drawColor, (float)thickness);
    pDrawList->AddLine(bottomRight, bottomRight - ImVec2(0, offset), drawColor, (float)thickness);

}
