/*
 * Copyright (c) 2022.
 * Created by Alpatov Softworks with love in Russia.
 */

#include "CSnapLinesEsp.h"
#include "../../Utils/Marker.h"

using namespace Esp;

void CSnapLinesEsp::InternalRenderAt(const SSDK::CBaseEntity* pEntity)
{
    POLY_MARKER;
    const auto pSettings = GetSettings<Settings::SnapLinesSettings>();

    ImVec3 pos;

    switch (pSettings->m_iSelectedBone)
    {
    case 0:
        pos = pEntity->GetBonePosition(SSDK::CBaseEntity::Bone::HEAD);
        break;
    case 1:
        pos = pEntity->GetBonePosition(SSDK::CBaseEntity::Bone::BODY);
        break;
    case 2:
        pos = pEntity->m_vecOrigin;
        break;

    	default:return;
    }

    const ImVec3 entity_screen_pos = WorldToScreen(pos);
    POLY_MARKER;

    const ImVec2 window_size = ImGui::GetMainViewport()->Size;

    const ImVec2 start = ImVec2(window_size.x / 2, window_size.y);
    const auto pDrawList = ImGui::GetBackgroundDrawList();

    POLY_MARKER;

    if (!pSettings->m_iDrawMode)
        pDrawList->AddLine(start, entity_screen_pos, pSettings->m_Color, static_cast<float>(pSettings->m_iThickness));
    else
        pDrawList->AddLine(start, entity_screen_pos, pEntity->GetColorBasedOnHealth(), static_cast<float>(pSettings->m_iThickness));
}