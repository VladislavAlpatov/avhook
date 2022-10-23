/*
 * Copyright (c) 2022.
 * Created by Alpatov Softworks with love in Russia.
 */

#pragma once
#include "CBaseEsp.h"

namespace Esp
{
	class CSnapLinesEsp final : public CUIEsp
	{
	public:
		CSnapLinesEsp(Settings::SnapLinesSettings* pSettings) : CUIEsp(pSettings) {};
	private:
		virtual void InternalRenderAt(const SSDK::CBaseEntity* pEntity);
	};
}