#pragma once
#include "hack.h"
#include "../Menu/Settings.h"

class BunnyHop : public CHackingFeature
{
public:
	void Work() override;
	BunnyHop(CBunnyHopSettings* pSettings);
private:
	int m_iPerfectJumps = 0;
};
