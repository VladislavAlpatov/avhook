#pragma once
#include "hack.h"
#include "../Menu/Settings.h"

namespace Hacks
{
	class BunnyHop : public CHackingFeature
	{
	public:
		void Work() override;
		BunnyHop(CBunnyHopSettings* pSettings);
	private:
		int m_iPerfectJumps = 0;
	};

}
