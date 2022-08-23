#pragma once
#include "CBaseEsp.h"
#include "../../SDK/IGlowObjectManager.h"

namespace hooks
{
	int __fastcall DoPostScreenSpaceEffects(void* pThis, void* edx, void* pView);
}
namespace Esp
{
	class CGlowEsp : public CBaseEsp
	{
		friend int __fastcall hooks::DoPostScreenSpaceEffects(void* pThis, void* edx, void* pView);
	public:
		CGlowEsp(Settings::CGlowEspSettings* pSettings) : CBaseEsp(pSettings) {};

	private:
		virtual void RenderAt(SSDK::GlowObjectDefinition& glowObj);
	};
}


