#include "CBoxEsp.h"


void CBoxEsp::InternalRenderAt(CBaseEntity* pEntity)
{
    POLY_MARKER;

    auto pSettings = GetSettings<BoxEspSettings>();

    if (!pSettings->m_bActive)
        return;
    ImColor drawColor = pSettings->m_Color;


    if (pEntity == GlobalVars::settings.m_AimBotSettings.m_pCurrentTarget)
        drawColor = ImColor(255, 0, 255);

    else if (pSettings->m_iDrawMode == DrawMod::AUTO)
        drawColor = pEntity->GetColorBasedOnHealth();

    switch (pSettings->m_iStyle)
    {
    case BoxEspSettings::Style::Solid:
        DrawSolidBox(pEntity, drawColor, pSettings->m_iThickness);

    case BoxEspSettings::Style::Cornered:
        DrawCorneredBox(pEntity, drawColor, pSettings->m_iThickness);

    default:
        break;
    }
}

void CBoxEsp::DrawSolidBox(CBaseEntity* pEntity, const ImColor& drawColor, int thickness)
{

    ImVec3 up = WorldToScreen(pEntity->m_vecOrigin);

    ImVec3 headpos = pEntity->GetBonePosition(CBaseEntity::Bone::HEAD);
    headpos.z += 8.1f;

    ImVec3 bottom = WorldToScreen(headpos);
    float height = fabs(up.y - bottom.y);


    ImVec2 topLeft = ImVec2(up.x - (height / 4.f), up.y);
    ImVec2 topRight = ImVec2(up.x + (height / 4.f), up.y);
    ImVec2 bottomRight = ImVec2(topRight.x, bottom.y);
    ImVec2 bottomLeft = ImVec2(topLeft.x, bottom.y);

    auto pDrawList = ImGui::GetBackgroundDrawList();

    pDrawList->AddLine(topLeft, topRight, drawColor,       (float)thickness);
    pDrawList->AddLine(bottomLeft, bottomRight, drawColor, (float)thickness);
    pDrawList->AddLine(topLeft, bottomLeft, drawColor,     (float)thickness);
    pDrawList->AddLine(topRight, bottomRight, drawColor,   (float)thickness);
}
void CBoxEsp::DrawCorneredBox(CBaseEntity* pEntity, const ImColor& drawColor, int thickness)
{
    ImVec3 up = WorldToScreen(pEntity->m_vecOrigin);

    ImVec3 headpos = pEntity->GetBonePosition(CBaseEntity::Bone::HEAD);
    headpos.z += 8.1f;

    ImVec3 bottom = WorldToScreen(headpos);
    float height = fabs(up.y - bottom.y);


    ImVec2 topLeft     = ImVec2(up.x - (height / 4.f), up.y);
    ImVec2 topRight    = ImVec2(up.x + (height / 4.f), up.y);
    ImVec2 bottomRight = ImVec2(topRight.x, bottom.y);
    ImVec2 bottomLeft  = ImVec2(topLeft.x, bottom.y);

    auto pDrawList = ImGui::GetBackgroundDrawList();
    float offset = height / 7.f;

    pDrawList->AddLine(topLeft,  topLeft + ImVec2(offset, 0), drawColor, (float)thickness);
    pDrawList->AddLine(topLeft,  topLeft - ImVec2(0, offset), drawColor, (float)thickness);

    pDrawList->AddLine(topRight, topRight - ImVec2(offset, 0), drawColor, (float)thickness);
    pDrawList->AddLine(topRight, topRight - ImVec2(0, offset), drawColor, (float)thickness);

    pDrawList->AddLine(bottomLeft, bottomLeft + ImVec2(offset, 0), drawColor, (float)thickness);
    pDrawList->AddLine(bottomLeft, bottomLeft + ImVec2(0, offset), drawColor, (float)thickness);

    pDrawList->AddLine(bottomRight, bottomRight - ImVec2(offset, 0), drawColor, (float)thickness);
    pDrawList->AddLine(bottomRight, bottomRight + ImVec2(0, offset), drawColor, (float)thickness);

}