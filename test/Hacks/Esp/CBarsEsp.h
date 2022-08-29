#pragma once
#include "CBaseEsp.h"

namespace Esp
{
	class CBarsEsp : public CUIEsp
	{
	public:
		CBarsEsp(Settings::BarEspSettings* pSettings) : CUIEsp(pSettings) {};
		
	private:
		virtual void InternalRenderAt(const SSDK::CBaseEntity* pEntity);
	};
}