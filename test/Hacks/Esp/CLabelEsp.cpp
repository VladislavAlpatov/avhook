#include "CLabelEsp.h"
#include "../../imgui/imgui_internal.h"
#include "../../Globals/Settings.h"
#include "../../Globals/Interfaces.h"
#include "../../SDK/ClientBase.h"

using namespace Esp;

void CLabelEsp::InternalRenderAt(const SSDK::CBaseEntity* pEntity)
{
	const auto pSettings = GetSettings<Settings::CLabelEspSettings>();

    if (SSDK::ClientBase::GetLocalPlayer()->CalcDistanceToEntity(pEntity) > (float)pSettings->m_iMaxDrawDistance)
        return;


    if(pSettings->m_iDrawPos == Settings::CLabelEspSettings::LABELS_ALLIGN::LEFT)
        DrawLabelsAtLeftSide(pEntity, pSettings->m_Labels);
    else
        DrawLabelsAtTop(pEntity, pSettings->m_Labels);
}

void Esp::CLabelEsp::DrawLabelsAtLeftSide(const SSDK::CBaseEntity* pEntity, const std::vector<std::shared_ptr<CLabels::CBaseLabel>>& labels) const
{
    // Using single char to calc text height for padding
    const float textPadding = ImGui::CalcTextSize(xorstr(" ")).y;
    auto textPos = CalcEspBox(pEntity).m_vecTopRight + ImVec2(GlobalVars::g_AllSettings.m_BoxEspSettings.m_iThickness + 2, 0);


    for (const auto& pLabel : labels)
    {
        if (!pLabel->m_bActive)
            continue;

        if (pLabel->Render(textPos, pEntity))
            textPos.y += textPadding;
    }
}

void Esp::CLabelEsp::DrawLabelsAtTop(const SSDK::CBaseEntity* pEntity, const std::vector<std::shared_ptr<CLabels::CBaseLabel>>& labels) const
{
    // Using single char to calc text height for padding
    auto pSettings = GetSettings<Settings::CLabelEspSettings>();
    const float textPadding = ImGui::CalcTextSize(xorstr(" ")).y;

    auto textPos = CalcEspBox(pEntity).m_vecTopLeft - ImVec2(0, textPadding+GlobalVars::g_AllSettings.m_BoxEspSettings.m_iThickness);

    for (const auto& pLabel : labels)
    {
        if (!pLabel->m_bActive)
            continue;

        if (pLabel->Render(textPos, pEntity))
            textPos.y -= textPadding;
    }
}
