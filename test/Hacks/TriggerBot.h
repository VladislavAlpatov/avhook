#pragma once
#include "hack.h"

namespace Hacks
{
	class TriggerBot : public CHackingFeature
	{

	public:
		TriggerBot(Settings::TriggerBotSettings* settings);
		void Work() override;
	private:
		int bone = 8;
	};
}

