#include "CLabelEsp.h"
#include "../../imgui/imgui_internal.h"

using namespace Esp;

void CLabelEsp::InternalRenderAt(CBaseEntity* pEntity)
{
	auto pSettings = GetSettings<Settings::CLabelEspSettings>();

    auto pLabels = &pSettings->m_Labels;

    // Rednder labels
    if(pSettings->m_iDrawPos == Settings::CLabelEspSettings::LABELS_ALLIGN::LEFT)
        DrawLabelsAtLeftSide(pEntity, *pLabels);
    else
        DrawLabelsAtTop(pEntity, *pLabels);
}

void Esp::CLabelEsp::DrawLabelsAtLeftSide(const CBaseEntity* pEntity, const std::vector<CLabels::CBaseLabel*>& labels)
{
    auto box = CalcEspBox(pEntity);

    ImVec2 bottomLeft = box.m_vecTop + ImVec2(box.m_Width / 2.f + 4, 0);

    for (auto pLabel : labels)
    {
        if (!pLabel->m_bActive)
            continue;

        if (pLabel->Render(bottomLeft, pEntity))
            bottomLeft.y -= 13.f;
    }
}

void Esp::CLabelEsp::DrawLabelsAtTop(const CBaseEntity* pEntity, const std::vector<CLabels::CBaseLabel*>& labels)
{
    auto box = CalcEspBox(pEntity);

    ImVec2 bottomLeft  = box.m_vecTop - ImVec2(box.m_Width / 2.f,13);

    for (auto pLabel : labels)
    {
        if (!pLabel->m_bActive)
            continue;

        if (pLabel->Render(bottomLeft, pEntity))
            bottomLeft.y -= 13.f;
    }
}
