#pragma once
#include "../../Globals/Interfaces.h"
#include "../../imgui/imgui_internal.h"

#include "CBaseEsp.h"

using namespace Esp;

ImVec3 CBaseEsp::WorldToScreen(const ImVec3& vecPosition) const
{
    // Screen size 
    ImVec2 viewPorstSize = ImGui::GetMainViewport()->Size;

    auto matrix = GlobalVars::g_pClient->dwViewmatrix;
    POLY_MARKER;

    float _x = matrix[0][0] * vecPosition.x + matrix[0][1] * vecPosition.y + matrix[0][2] * vecPosition.z + matrix[0][3];
    float _y = matrix[1][0] * vecPosition.x + matrix[1][1] * vecPosition.y + matrix[1][2] * vecPosition.z + matrix[1][3];
    // Dont need z cuz we need only x,y and w
    //float _z = pClient->dwViewmatrix[2][0] * vecPosition.x + pClient->dwViewmatrix[2][1] * vecPosition.y + pClient->dwViewmatrix[2][2] * vecPosition.z + pClient->dwViewmatrix[2][3];

    // w is depth
    float w =  matrix[3][0] * vecPosition.x + matrix[3][1] * vecPosition.y + matrix[3][2] * vecPosition.z + matrix[3][3];

    ImVec2 ndc;

    ndc.x = _x / w;
    ndc.y = _y / w;

    // Normalize screen cords
    float x =  (viewPorstSize.x / 2.f * ndc.x) + (ndc.x + viewPorstSize.x / 2.f);
    float y = -(viewPorstSize.y / 2.f * ndc.y) + (ndc.y + viewPorstSize.y / 2.f);

    return ImVec3(x, y, w);
}

Esp::EntityBox CBaseEsp::CalcEspBox(const CBaseEntity* pEntity) const
{
    POLY_MARKER;

    std::array<ImVec3, 93> bones;

    for (BYTE i = 0; i < bones.size(); ++i)
    {
        ImVec3 tmp;
        if (i == 8)
            tmp = WorldToScreen(pEntity->GetBonePosition(i) + ImVec3(0, 0, 8.f));
        else
            tmp = WorldToScreen(pEntity->GetBonePosition(i));

        if ((pEntity->GetBonePosition(i).DistTo(pEntity->m_vecOrigin) < 100.f) and tmp.z > 0)
        {
            bones[i] = tmp;
        }
    }
    ImVec3 mostTop = ImVec3(90000, 90000, 90000);
    ImVec3 mostBottom;

    POLY_MARKER;

    for (const auto& bone : bones)
    {
        if (bone.Length() == 0) continue;

        mostTop    = (((bone.y) < (mostTop.y))    ? (bone) : (mostTop));
        mostBottom = (((bone.y) > (mostBottom.y)) ? (bone) : (mostBottom));
    }
    const float boxHeight = abs(mostTop.y - mostBottom.y);
    const float offset = boxHeight / 4.f;

    EntityBox clacledBox;

    POLY_MARKER;

    clacledBox.m_vecTopLeft =  mostTop - ImVec2(offset, 0);
    clacledBox.m_vecTopRight = mostTop + ImVec2(offset, 0);

    POLY_MARKER;

    clacledBox.m_vecBottomLeft = clacledBox.m_vecTopLeft  + ImVec2(0, boxHeight);

    clacledBox.m_vecBottomRight  = clacledBox.m_vecTopRight + ImVec2(0, boxHeight);

    return clacledBox;
}

ImVec2 Esp::EntityBox::GetSize() const
{
    return m_vecBottomRight - m_vecTopLeft;
}
