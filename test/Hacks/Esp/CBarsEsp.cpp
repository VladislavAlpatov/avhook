#include "CBarsEsp.h"


void CBarsEsp::InternalRenderAt(CBaseEntity* pEntity)
{
    POLY_MARKER;

    auto pSettings = GetSettings<BarEspSettings>();

    ImVec3 up       = WorldToScreen(pEntity->m_vecOrigin);

    ImVec3 bottom   = WorldToScreen(pEntity->GetBonePosition(CBaseEntity::Bone::HEAD) + ImVec3(0, 0, 7.9f));

    float maxHeight = up.y - bottom.y;

    ImVec2 topleft;

    POLY_MARKER;

    topleft.x = up.x - (maxHeight / 4.f) - pSettings->m_iThickness;
    topleft.y = up.y;

    std::list<LineData> lines;

    if (pSettings->m_bDrawHealthBar)
        lines.push_back(LineData(pEntity->GetColorBasedOnHealth(), maxHeight * (pEntity->m_iHealth / 100.f)));

    if (pSettings->m_bDrawArmorBar)
        lines.push_back(LineData(pSettings->m_ArmorColor, maxHeight * (pEntity->m_ArmorValue / 100.f)));
    
    POLY_MARKER;
    auto pDrawList = ImGui::GetBackgroundDrawList();

    ImVec2 lineStart = topleft - ImVec2(3, 0);
    for (auto& line : lines)
    {
        pDrawList->AddLine(lineStart, lineStart - ImVec2(0, maxHeight), ImColor(0, 0, 0), (float)pSettings->m_iThickness);
        pDrawList->AddLine(lineStart, lineStart - ImVec2(0, line.m_fLength), line.m_Color, (float)pSettings->m_iThickness);
        lineStart.x -= pSettings->m_iThickness;
    }
}