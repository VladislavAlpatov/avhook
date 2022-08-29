#include "CBarsEsp.h"
#include "../../imgui/imgui_internal.h"
#include "../../Globals/Settings.h"
#include <list>
#include <memory>


using namespace Esp;

class CBaseBar
{
public:
    CBaseBar(float fMaxLength)
    {
        m_fMaxLength = fMaxLength;
    }
    virtual void Render(const ImVec2& vecRenderPos) const = 0;
    virtual bool IsActive() const = 0;

protected:
    float	m_fMaxLength;
};

class CHealthBar : public CBaseBar
{
public:
    CHealthBar(const SSDK::CBaseEntity* pEntity, float fMaxLength) : CBaseBar(fMaxLength)
    {
        m_pEntity = pEntity;
    }
    bool IsActive() const override
    {
        return GlobalVars::g_AllSettings.m_BarEspSettings.m_bDrawHealthBar;
    }
    ImColor GetGradientColor(float fVal, float fMaxVal) const
    {
        float fRatio = fVal / fMaxVal;

        if (fRatio >= 0.5f)
            return ImColor(1.f - (fRatio - 0.5f) * 2.f, 1.f, 0.f);

        return ImColor(1.f, fRatio * 2.f, 0.f);
    }
    void Render(const ImVec2& vecRenderPos) const override
    {
        auto pSettings    = &GlobalVars::g_AllSettings.m_BarEspSettings;
        auto fHealthRatio = m_pEntity->m_iHealth / 100.f;
        auto fBarHeight   = fHealthRatio * m_fMaxLength;
        auto pDrawList    = ImGui::GetBackgroundDrawList();


        // ===VERY IMPORTANT=======
        // This line of code fixes a bug in which there would be a
        // chance that the Health bar would be rendered when the
        // player is off the screen, which led to game crashes and severe lags.
        // ========================
        if (fBarHeight > ImGui::GetMainViewport()->Size.y or fBarHeight < 0.f)
            return;


        // Draw background fill and foreground fill
        pDrawList->AddRectFilled(vecRenderPos, vecRenderPos + ImVec2(pSettings->m_iThickness, -m_fMaxLength), pSettings->m_BackGroundColor);

        if (pSettings->m_iStyle == 0)
            pDrawList->AddRectFilled(vecRenderPos, vecRenderPos + ImVec2(pSettings->m_iThickness, -fBarHeight), m_pEntity->GetColorBasedOnHealth());
        else
        for (int i = 0; i <= (int)fBarHeight+1; ++i)
        {
            pDrawList->AddLine(vecRenderPos + ImVec2(pSettings->m_iThickness, -i), vecRenderPos + ImVec2(-1, -i), GetGradientColor(i, m_fMaxLength));
        }

        // Add outline
        pDrawList->AddRect(vecRenderPos + ImVec2(-1, 0), vecRenderPos + ImVec2(pSettings->m_iThickness + 1, -m_fMaxLength), ImColor(0, 0, 0));


    }
private:
    const SSDK::CBaseEntity* m_pEntity;
};

class CArrmorBar : public CBaseBar
{
public:
    CArrmorBar(const SSDK::CBaseEntity* pEntity, float fMaxLength) : CBaseBar(fMaxLength)
    {
        m_pEntity = pEntity;
    }
    void Render(const ImVec2& vecRenderPos) const override
    {
        auto pSettings = &GlobalVars::g_AllSettings.m_BarEspSettings;

        auto fArrmorRatio = m_pEntity->m_ArmorValue / 100.f;
        auto fBarHeight = fArrmorRatio * m_fMaxLength;

        auto pDrawList = ImGui::GetBackgroundDrawList();

        // Draw background fill and foreground fill
        pDrawList->AddRectFilled(vecRenderPos, vecRenderPos + ImVec2(pSettings->m_iThickness, -m_fMaxLength), pSettings->m_BackGroundColor);
        pDrawList->AddRectFilled(vecRenderPos, vecRenderPos + ImVec2(pSettings->m_iThickness, -fBarHeight),   pSettings->m_ArmorColor);

        // Add outline
        pDrawList->AddRect(vecRenderPos + ImVec2(-1, 0), vecRenderPos + ImVec2(pSettings->m_iThickness + 1, -m_fMaxLength), ImColor(0, 0, 0));


    }
    bool IsActive() const override
    {
        return GlobalVars::g_AllSettings.m_BarEspSettings.m_bDrawArmorBar;
    }
private:
    const SSDK::CBaseEntity* m_pEntity;
};

void CBarsEsp::InternalRenderAt(const SSDK::CBaseEntity* pEntity)
{
    POLY_MARKER;

    auto pSettings = GetSettings<Settings::BarEspSettings>();

    auto box = CalcEspBox(pEntity);

    float maxBarLength = box.GetSize().y;


    POLY_MARKER;


    std::vector<std::shared_ptr<CBaseBar>> bars = {std::shared_ptr<CBaseBar>(new CHealthBar(pEntity, maxBarLength)), std::shared_ptr<CBaseBar>(new CArrmorBar(pEntity, maxBarLength)) };

    ImVec2 barStart = box.m_vecBottomLeft - ImVec2(pSettings->m_iThickness + GlobalVars::g_AllSettings.m_BoxEspSettings.m_iThickness + 2, 0);

    for (const auto pBar : bars)
    {
        if (!pBar->IsActive()) continue;

        pBar->Render(barStart);
        barStart.x -= pSettings->m_iThickness + 2;
    }
}