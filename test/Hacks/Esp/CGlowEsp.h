#pragma once
#include "CBaseEsp.h"

namespace hooks
{
	int __fastcall DoPostScreenSpaceEffects(void* pThis, void* edx, void* pView);
}
namespace Esp
{
	class CGlowEsp : public CBaseEsp
	{
	public:
		friend int __fastcall hooks::DoPostScreenSpaceEffects(void* pThis, void* edx, void* pView);
		CGlowEsp(Settings::CLabelEspSettings* pSettings) : CBaseEsp(pSettings) {};

	private:
		virtual void InternalRenderAt(const SSDK::CBaseEntity* pEntity) override;
	};
}


