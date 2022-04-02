#include "CSnapLinesEsp.h"
using namespace Esp;

void CSnapLinesEsp::InternalRenderAt(CBaseEntity* pEntity)
{
    auto pSettings = GetSettings<Settings::SnapLinesSettings>();
    if (!pSettings->m_bActive)
        return;

    ImVec3 pos;

    switch (pSettings->m_iSelectedBone)
    {
    case 0:
        pos = pEntity->GetBonePosition(CBaseEntity::Bone::HEAD);
        break;
    case 1:
        pos = pEntity->GetBonePosition(CBaseEntity::Bone::BODY);
        break;
    case 2:
        pos = pEntity->m_vecOrigin;
        break;
    }

    ImVec3 entity_screen_pos = WorldToScreen(pos);

    if (entity_screen_pos.z < 0.1f)
        return;

    ImVec2 window_size = ImGui::GetMainViewport()->Size;

    ImVec2 start = ImVec2(window_size.x / 2, window_size.y);
    auto pDrawList = ImGui::GetBackgroundDrawList();
    if (!pSettings->m_iDrawMode)
        pDrawList->AddLine(start, entity_screen_pos, pSettings->m_Color, static_cast<float>(pSettings->m_iThickness));
    else
        pDrawList->AddLine(start, entity_screen_pos, pEntity->GetColorBasedOnHealth(), static_cast<float>(pSettings->m_iThickness));
}