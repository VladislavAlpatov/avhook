#include "CBoxEsp.h"


void CBoxEsp::InternalRenderAt(CBaseEntity* pEntity)
{
    POLY_MARKER;

    auto pSettings = GetSettings<BoxEspSettings>();

    if (!pSettings->m_bActive)
        return;
    ImColor draw_color = pSettings->m_Color;
    ImVec3 up = WorldToScreen(pEntity->m_vecOrigin);

    ImVec3 headpos = pEntity->GetBonePosition(CBaseEntity::Bone::HEAD);
    headpos.z += 8.1f;

    ImVec3 bottom = WorldToScreen(headpos);
    float height = fabs(up.y - bottom.y);

    if (pEntity == GlobalVars::settings.m_AimBotSettings.m_pCurrentTarget)
        draw_color = ImColor(255, 0, 255);

    else if (pSettings->m_iDrawMode == DrawMod::AUTO)
        draw_color = pEntity->GetColorBasedOnHealth();

    ImVec2 topLeft      = ImVec2(up.x - (height / 4.f), up.y);
    ImVec2 topRight     = ImVec2(up.x + (height / 4.f), up.y);
    ImVec2 bottomRight  = ImVec2(topRight.x, bottom.y);
    ImVec2 bottomLeft   = ImVec2(topLeft.x, bottom.y);

    auto pDrawList = ImGui::GetBackgroundDrawList();

    pDrawList->AddLine(topLeft, topRight, draw_color,       (float)pSettings->m_iThickness);
    pDrawList->AddLine(bottomLeft, bottomRight, draw_color, (float)pSettings->m_iThickness);
    pDrawList->AddLine(topLeft, bottomLeft, draw_color,     (float)pSettings->m_iThickness);
    pDrawList->AddLine(topRight, bottomRight, draw_color,   (float)pSettings->m_iThickness);
}