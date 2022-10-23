/*
 * Copyright (c) 2022.
 * Created by Alpatov Softworks with love in Russia.
 */

#pragma once
#include "hack.h"
#include "../Menu/Settings.h"
#include "../SDK/CUserCMD.h"

namespace Hacks
{
	class CBunnyHop final  : public CHackFeature
	{
	public:
		void Work() override;
		CBunnyHop(SSDK::CUserCmd* pUserCmd, Settings::CBunnyHopSettings* pSettings);
	private:
		int m_iPerfectJumps = 0;
		SSDK::CUserCmd* m_pUserCmd;
	};

}
