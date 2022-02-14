#include "CBaseEsp.h"


ImVec3 CBaseEsp::WorldToScreen(const ImVec3& vecPosition)
{
    // Screen size 
    ImVec2 viewPorstSize = ImGui::GetMainViewport()->Size;

    auto client = GlobalVars::client;

    float _x = client->dwViewmatrix[0][0] * vecPosition.x + client->dwViewmatrix[0][1] * vecPosition.y + client->dwViewmatrix[0][2] * vecPosition.z + client->dwViewmatrix[0][3];
    float _y = client->dwViewmatrix[1][0] * vecPosition.x + client->dwViewmatrix[1][1] * vecPosition.y + client->dwViewmatrix[1][2] * vecPosition.z + client->dwViewmatrix[1][3];
    // Dont need z cuz we need only x,y and w
    //float _z = client->dwViewmatrix[2][0] * vecPosition.x + client->dwViewmatrix[2][1] * vecPosition.y + client->dwViewmatrix[2][2] * vecPosition.z + client->dwViewmatrix[2][3];

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