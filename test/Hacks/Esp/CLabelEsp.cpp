#include "CLabelEsp.h"
#include "../../imgui/imgui_internal.h"
#include "../../Globals/GlobalVars.h"

using namespace Esp;

void CLabelEsp::InternalRenderAt(CBaseEntity* pEntity)
{
	auto pSettings = GetSettings<Settings::CLabelEspSettings>();

    // Rednder labels
    if(pSettings->m_iDrawPos == Settings::CLabelEspSettings::LABELS_ALLIGN::LEFT)
        DrawLabelsAtLeftSide(pEntity, pSettings->m_Labels);
    else
        DrawLabelsAtTop(pEntity, pSettings->m_Labels);
}

void Esp::CLabelEsp::DrawLabelsAtLeftSide(const CBaseEntity* pEntity, const std::vector<std::shared_ptr<CLabels::CBaseLabel>>& labels)
{
    const float textPadding = ImGui::CalcTextSize(xorstr("x")).y;
    auto textPos = CalcEspBox(pEntity).m_vecTopRight + ImVec2(GlobalVars::settings.m_BoxEspSettings.m_iThickness + 2, 0);


    for (const auto pLabel : labels)
    {
        if (!pLabel->m_bActive)
            continue;

        if (pLabel->Render(textPos, pEntity))
            textPos.y += textPadding;
    }
}

void Esp::CLabelEsp::DrawLabelsAtTop(const CBaseEntity* pEntity, const std::vector<std::shared_ptr<CLabels::CBaseLabel>>& labels)
{
    auto pSettings = GetSettings<Settings::CLabelEspSettings>();
    const float textPadding = ImGui::CalcTextSize(xorstr("x")).y;

    auto textPos = CalcEspBox(pEntity).m_vecTopLeft - ImVec2(0, textPadding+GlobalVars::settings.m_BoxEspSettings.m_iThickness);

    for (auto pLabel : labels)
    {
        if (!pLabel->m_bActive)
            continue;

        if (pLabel->Render(textPos, pEntity))
            textPos.y -= textPadding;
    }
}
