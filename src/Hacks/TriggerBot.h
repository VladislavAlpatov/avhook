/*
 * Copyright (c) 2022.
 * Created by Alpatov Softworks with love in Russia.
 */

#pragma once
#include "hack.h"
#include "../SDK/CUserCMD.h"

namespace Hacks
{
	class TriggerBot final: public CHackFeature
	{

	public:
		TriggerBot(Settings::TriggerBotSettings* settings, SSDK::CUserCmd* pUsrCmd);
		void Work() override;
		static bool IsEnemyEntityInSight();
	private:
		SSDK::CUserCmd* m_pUserCmd;
	};
}

