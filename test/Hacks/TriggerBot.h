#pragma once
#include "hack.h"


class TriggerBot : public CHackingFeature
{

public:
	TriggerBot(TriggerBotSettings* settings);
	void Work() override;
private:
	int bone = 8;
};

