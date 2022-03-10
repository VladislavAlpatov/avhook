#pragma once
#include "hack.h"
#include "../Menu/Settings.h"

namespace Hacks
{
	class ÑBunnyHop : public CHackingFeature
	{
	public:
		void Work() override;
		ÑBunnyHop(Settings::CBunnyHopSettings* pSettings);
	private:
		int m_iPerfectJumps = 0;
	};

}
