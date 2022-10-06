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
	private:
		SSDK::CUserCmd* m_pUserCmd;

		static bool IsEnemyEntityInSight();
	};
}

