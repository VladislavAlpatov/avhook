#include "CBarsEsp.h"


void CBarsEsp::InternalRenderAt(CBaseEntity* pEntity)
{
    POLY_MARKER;

    auto pSettings = GetSettings<BarEspSettings>();

    ImVec3 up       = WorldToScreen(pEntity->m_vecOrigin);

    ImVec3 bottom   = WorldToScreen(pEntity->GetBonePosition(CBaseEntity::Bone::HEAD) + ImVec3(0, 0, 7.9f));

    float maxBarLength = up.y - bottom.y;

    ImVec2 bottomLeft;

    POLY_MARKER;


    bottomLeft.x = up.x - (maxBarLength / 4.f) - pSettings->m_iThickness;
    bottomLeft.y = up.y;

    std::list<LineData> lines;

    if (pSettings->m_bDrawHealthBar)
        lines.push_back(LineData(pEntity->GetColorBasedOnHealth(), maxBarLength * (pEntity->m_iHealth / 100.f)));

    if (pSettings->m_bDrawArmorBar)
        lines.push_back(LineData(pSettings->m_ArmorColor, maxBarLength * (pEntity->m_ArmorValue / 100.f)));
    POLY_MARKER;
    auto pDrawList = ImGui::GetBackgroundDrawList();

    ImVec2 barStart = bottomLeft - ImVec2(3, 0);
    for (auto& line : lines)
    {
        pDrawList->AddRectFilled(barStart, barStart + ImVec2(pSettings->m_iThickness, -maxBarLength), pSettings->m_BackGroundColor);
        pDrawList->AddRectFilled(barStart, barStart + ImVec2(pSettings->m_iThickness, -line.m_fLength), line.m_Color);
        pDrawList->AddRect(barStart + ImVec2(-1, 0), barStart + ImVec2(pSettings->m_iThickness + 1, -maxBarLength), ImColor(0, 0, 0));
        barStart.x -= pSettings->m_iThickness;
    }
}