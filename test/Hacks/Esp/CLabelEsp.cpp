#include "CLabelEsp.h"

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
    ImVec3 up = WorldToScreen(pEntity->m_vecOrigin);

    ImVec3 bottom      = WorldToScreen(pEntity->GetBonePosition(CBaseEntity::Bone::HEAD) + ImVec3(0, 0, 7.9f));
    const float height = up.y - bottom.y;
    ImVec2 bottomRight = ImVec2(WorldToScreen(pEntity->m_vecOrigin).x + height / 4.f + 4.f, bottom.y);

    const auto pDrawList = ImGui::GetBackgroundDrawList();

    for (auto pLabel : labels)
    {
        if (!pLabel->m_bActive)
            continue;

        if (pLabel->Render(bottomRight, pEntity))
            bottomRight.y += 13.f;

    }
}

void Esp::CLabelEsp::DrawLabelsAtTop(const CBaseEntity* pEntity, const std::vector<CLabels::CBaseLabel*>& labels)
{
    ImVec3 up = WorldToScreen(pEntity->m_vecOrigin);

    ImVec3 bottom      = WorldToScreen(pEntity->GetBonePosition(CBaseEntity::Bone::HEAD) + ImVec3(0, 0, 7.9f));
    const float height = up.y - bottom.y;
    ImVec2 bottomLeft  = ImVec2(WorldToScreen(pEntity->m_vecOrigin).x - height / 4.f, bottom.y - 13.f);

    for (auto pLabel : labels)
    {
        if (pLabel->Render(bottomLeft, pEntity))
            bottomLeft.y -= 13.f;
    }
}
