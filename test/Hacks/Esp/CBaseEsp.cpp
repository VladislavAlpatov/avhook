#include "../../Globals/Interfaces.h"
#include "../../imgui/imgui_internal.h"
#include  "../../SDK/ClientBase.h"

#include "CBaseEsp.h"

using namespace Esp;

ImVec3 CUIEsp::WorldToScreen(const ImVec3& vecPosition)
{
    POLY_MARKER;
    // Screen size 
    const ImVec2 viewPortSize = ImGui::GetMainViewport()->Size;

    auto matrix = SSDK::ClientBase::GetViewMatrix();
    POLY_MARKER;

    auto out = matrix * vecPosition;

    const float _x = out.at(0, 0);
    const float _y = out.at(1, 0);
    const float w  = out.at(3, 0);


    ImVec2 ndc;

    ndc.x = _x / w;
    ndc.y = _y / w;

    // Normalize screen cords
    const float x =  (viewPortSize.x / 2.f * ndc.x) + (ndc.x + viewPortSize.x / 2.f);
    const float y = -(viewPortSize.y / 2.f * ndc.y) + (ndc.y + viewPortSize.y / 2.f);

    return { x, y, w };
}

Esp::EntityBox CUIEsp::CalcEspBox(const SSDK::CBaseEntity* pEntity) const
{
    POLY_MARKER;

    std::array<ImVec3, 93> bones;

    for (int i = 0; i < bones.size(); ++i)
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
    auto mostTop = ImVec3(90000, 90000, 90000);
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

    EntityBox calcedBox;

    POLY_MARKER;

    calcedBox.m_vecTopLeft =  mostTop - ImVec2(offset, 0);
    calcedBox.m_vecTopRight = mostTop + ImVec2(offset, 0);

    POLY_MARKER;

    calcedBox.m_vecBottomLeft = calcedBox.m_vecTopLeft  + ImVec2(0, boxHeight);

    calcedBox.m_vecBottomRight  = calcedBox.m_vecTopRight + ImVec2(0, boxHeight);

    return calcedBox;
}

ImVec2 Esp::EntityBox::GetSize() const
{
    return m_vecBottomRight - m_vecTopLeft;
}
