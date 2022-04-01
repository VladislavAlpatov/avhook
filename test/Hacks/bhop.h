#pragma once
#include "hack.h"
#include "../Menu/Settings.h"

namespace Hacks
{
	class CBunnyHop : public CHackingFeature
	{
	public:
		void Work() override;
		CBunnyHop(Settings::CBunnyHopSettings* pSettings);
	private:
		int m_iPerfectJumps = 0;
	};

}
