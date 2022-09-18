#pragma once
#include "hack.h"
#include "../Menu/Settings.h"
#include "../SDK/CUserCMD.h"

namespace Hacks
{
	class CBunnyHop final  : public CHackingFeature
	{
	public:
		void Work() override;
		CBunnyHop(CUserCmd* pUserCmd, Settings::CBunnyHopSettings* pSettings);
	private:
		int m_iPerfectJumps = 0;
		CUserCmd* m_pUserCmd;
	};

}
