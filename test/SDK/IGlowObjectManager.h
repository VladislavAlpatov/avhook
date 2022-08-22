#pragma once
#include "CBaseEntity.h"
#include "../imgui/imgui.h"


namespace SSDK
{
    class GlowObjectDefinition
    {
    public:

        int nextFreeSlot;
        CBaseEntity* m_pEntity;

        ImColor m_Color;
        bool m_bGlowAlphaCappedByRenderAlpha;
        float m_fGlowAlphaFunctionOfMaxVelocity;
        float m_fGlowAlphaMax;
        float m_fGlowPulseOverdrive;
        bool m_bRenderWhenOccluded;
        bool m_bRenderWhenUnoccluded;
        bool m_bFullBloomRender;
        int  m_iFullBloomStencilTestValue;
        int  m_iGlowStyle;
        int  m_iSplitScreenSlot;

        inline bool IsUnused() const
        {
            return nextFreeSlot != -2;
        }

        void SetColor(const ImColor& color)
        {
            m_Color = color;

            m_bRenderWhenOccluded = true;
        }
        
    };

	class IGlowObjectManager
	{
    public:
        GlowObjectDefinition& GetGlowObject(size_t index) const;
        int m_iFirstFreeSlot;

        int GetGlowEntitiesCount() const;
	};

}
