/*
 * Copyright (c) 2022.
 * Created by Alpatov Softworks with love in Russia.
 */

#pragma once
#include "CBaseEsp.h"
#include "../../SDK/IGlowObjectManager.h"

namespace hooks
{
	int __fastcall hRenderGlowEffects(SSDK::IGlowObjectManager* pThis, void* edx, int a2, int a3);
}
namespace Esp
{
	class CGlowEsp final : public CBaseEsp
	{
		friend int __fastcall hooks::hRenderGlowEffects(SSDK::IGlowObjectManager* pThis, void* edx, int a2, int a3);
	public:
		CGlowEsp(Settings::CGlowEspSettings* pSettings) : CBaseEsp(pSettings)
		{
			
		};

	private:
		virtual void RenderAt(SSDK::GlowObjectDefinition& glowObj);
		inline float CalcAdaptiveGlowBrightness(const SSDK::CBaseEntity* pEntity, float fMaxDistance= 4096.f);
	};
}


