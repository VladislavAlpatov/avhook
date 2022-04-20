#include "CBarsEsp.h"
#include "../../imgui/imgui_internal.h"
using namespace Esp;

void CBarsEsp::InternalRenderAt(CBaseEntity* pEntity)
{
    POLY_MARKER;

    auto pSettings = GetSettings<Settings::BarEspSettings>();

    auto box = CalcEspBox(pEntity);

    float maxBarLength = abs(box.m_vecTop.y - box.m_vecBottom.y);

    POLY_MARKER;


    ImVec2 bottomLeft = ImVec2(box.m_vecTop.x, box.m_vecBottom.y) - ImVec2(box.m_Width / 2.f + pSettings->m_iThickness + 3, 0);

    std::list<LineData> lines;

    if (pSettings->m_bDrawHealthBar)
        lines.push_back(LineData(pEntity->GetColorBasedOnHealth(), maxBarLength * (pEntity->m_iHealth / 100.f)));

    if (pSettings->m_bDrawArmorBar)
        lines.push_back(LineData(pSettings->m_ArmorColor, maxBarLength * (pEntity->m_ArmorValue / 100.f)));
    POLY_MARKER;
    auto pDrawList = ImGui::GetBackgroundDrawList();

    ImVec2 barStart = bottomLeft;
    for (auto& line : lines)
    {
        pDrawList->AddRectFilled(barStart, barStart + ImVec2(pSettings->m_iThickness, -maxBarLength), pSettings->m_BackGroundColor);
        pDrawList->AddRectFilled(barStart, barStart + ImVec2(pSettings->m_iThickness, -line.m_fLength), line.m_Color);
        pDrawList->AddRect(barStart + ImVec2(-1, 0), barStart + ImVec2(pSettings->m_iThickness + 1, -maxBarLength), ImColor(0, 0, 0));
        barStart.x -= pSettings->m_iThickness + 1;
    }
}