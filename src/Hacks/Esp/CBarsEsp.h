/*
 * Copyright (c) 2022.
 * Created by Alpatov Softworks with love in Russia.
 */

#pragma once
#include "CBaseEsp.h"

//========= Copyright Alpatov Softworks, All rights reserved. ============//
//
// Purpose: Render Bar ESP on players.
//
//===============================================================================

namespace Esp
{
	class CBarsEsp final : public CUIEsp
	{
	public:
		CBarsEsp(Settings::BarEspSettings* pSettings) : CUIEsp(pSettings) {};
		
	private:
		void InternalRenderAt(const SSDK::CBaseEntity* pEntity) override;
	};
}