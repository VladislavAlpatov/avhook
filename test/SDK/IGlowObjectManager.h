#pragma once
#include "CBaseEntity.h"
#include "../imgui/imgui.h"


namespace SSDK
{
    class GlowObjectDefinition
    {
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
        int m_iFullBloomStencilTestValue;
        int m_iGlowStyle;
        int m_iSplitScreenSlot;

        inline bool IsUnused() const
        {
            return nextFreeSlot != -1;
        }

        void SetColor(const ImColor& color)
        {
            m_Color = color;

            m_bRenderWhenOccluded = true;
        }

        static constexpr int END_OF_FREE_LIST = -1;
        static constexpr int ENTRY_IN_USE = -2;
    };

	class IGlowObjectManager
	{
    public:

        BYTE __pad1[20];
        int m_iFirstFreeSlot;
	};

}
