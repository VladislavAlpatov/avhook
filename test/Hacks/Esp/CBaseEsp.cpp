#pragma once
#include "../../Globals/GlobalVars.h"

#include "CBaseEsp.h"

using namespace Esp;

ImVec3 CBaseEsp::WorldToScreen(const ImVec3& vecPosition)
{
    // Screen size 
    ImVec2 viewPorstSize = ImGui::GetMainViewport()->Size;

    auto client = GlobalVars::pClient;

    float _x = client->dwViewmatrix[0][0] * vecPosition.x + client->dwViewmatrix[0][1] * vecPosition.y + client->dwViewmatrix[0][2] * vecPosition.z + client->dwViewmatrix[0][3];
    float _y = client->dwViewmatrix[1][0] * vecPosition.x + client->dwViewmatrix[1][1] * vecPosition.y + client->dwViewmatrix[1][2] * vecPosition.z + client->dwViewmatrix[1][3];
    // Dont need z cuz we need only x,y and w
    //float _z = pClient->dwViewmatrix[2][0] * vecPosition.x + pClient->dwViewmatrix[2][1] * vecPosition.y + pClient->dwViewmatrix[2][2] * vecPosition.z + pClient->dwViewmatrix[2][3];

    // w is depth
    float w =  client->dwViewmatrix[3][0] * vecPosition.x + client->dwViewmatrix[3][1] * vecPosition.y + client->dwViewmatrix[3][2] * vecPosition.z + client->dwViewmatrix[3][3];

    ImVec2 ndc;

    ndc.x = _x / w;
    ndc.y = _y / w;

    // Normalize screen cords
    float x =  (viewPorstSize.x / 2.f * ndc.x) + (ndc.x + viewPorstSize.x / 2.f);
    float y = -(viewPorstSize.y / 2.f * ndc.y) + (ndc.y + viewPorstSize.y / 2.f);

    return ImVec3(x, y, w);
}

Esp::EntityBox CBaseEsp::CalcEspBox(const CBaseEntity* pEntity)
{
    std::array<ImVec3, 93> bones;
    EntityBox box;
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
    ImVec3 mostRight;
    ImVec3 mostLeft = ImVec3(90000, 90000, 90000);

    for (auto& bone : bones)
    {
        if (bone.Length() == 0) continue;

        mostRight  = (((bone.x) > (mostRight.x))  ? (bone) : (mostRight));
        mostLeft   = (((bone.x) < (mostLeft.x))   ? (bone) : (mostLeft));

        mostTop    = (((bone.y) < (mostTop.y))    ? (bone) : (mostTop));
        mostBottom = (((bone.y) > (mostBottom.y)) ? (bone) : (mostBottom));
    }
    box.m_vecBottom = mostBottom;
    box.m_vecTop    = mostTop;
    box.m_Width     = abs(mostLeft.x - mostRight.x);

    return box;
}