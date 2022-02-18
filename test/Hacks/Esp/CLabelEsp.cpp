#include "CLabelEsp.h"
using namespace Esp;

void CLabelEsp::InternalRenderAt(CBaseEntity* pEntity)
{
    POLY_MARKER;
	auto pSettings = GetSettings<CLabelEspSettings>();

    ImVec3 up = WorldToScreen(pEntity->m_vecOrigin);

    ImVec3 bottom = WorldToScreen(pEntity->GetBonePosition(CBaseEntity::Bone::HEAD) +  ImVec3(0,0, 7.9f));

    float height = up.y - bottom.y;

    ImVec2 bottomRight = ImVec2(WorldToScreen(pEntity->m_vecOrigin).x + height / 4.f + 4.f, bottom.y);


    std::list<Label> drawTextList;

    if (pSettings->m_bDrawName)
        drawTextList.push_back(Label(pSettings->m_NameLabelColor, GlobalVars::pIEngineClient->GetPlayerInfo(pEntity->m_Index).szName));

    if (pSettings->m_bDrawHealth)
        drawTextList.push_back(Label(pEntity->GetColorBasedOnHealth(), std::format(xorstr("Health: {}/100"), pEntity->m_iHealth)));

    if (pSettings->m_bDrawArmor)
        drawTextList.push_back(Label(pSettings->m_ArmorLabelColor, std::format(xorstr("Armor: {}/100"), pEntity->m_ArmorValue)));

    if (pSettings->m_bDrawDistance)
        drawTextList.push_back(Label(pSettings->m_DistanceLabelColor, std::format(xorstr("Distance: {}m"), static_cast<int>(GlobalVars::client->pLocalPlayer->CalcDistaceToEntity(pEntity) * 2.54f / 100.f))));

    if (pEntity->m_IsVisible and pSettings->m_bDrawVisibility)
        drawTextList.push_back(Label(pSettings->m_VisibilityLabelColor, xorstr("*VISIBLE*")));

    if (pEntity == GlobalVars::settings.m_AimBotSettings.m_pCurrentTarget)
        drawTextList.push_back(Label(ImColor(255, 0, 255), xorstr("*AIMBOT TARGET*")));

    auto pDrawList = ImGui::GetBackgroundDrawList();
    for (auto& textData : drawTextList)
    {
        pDrawList->AddText(bottomRight, textData.m_Color, textData.m_Text.c_str());
        bottomRight.y += 13;
    }
}