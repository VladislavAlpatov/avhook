#pragma once
#include "CBaseEsp.h"

//========= Copyright Alpatov Softworks, All rights reserved. ============//
//
// Purpose: Render Bar ESP on players.
//
//===============================================================================

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