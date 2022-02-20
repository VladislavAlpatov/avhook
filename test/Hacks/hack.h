#pragma once
#include <Windows.h>

#include "../SDK/SDK.h"
#include "../Menu/Settings.h"
#include "../Utils/xorstr.h"
#include "../Globals/GlobalVars.h"
namespace Hacks
{
	class CHackingFeature
	{
	public:
		CHackingFeature(Settings::CBaseSettings* pSettings);
		virtual void Work() = 0;
	protected:
		Settings::CBaseSettings* m_pSettings = nullptr;
		bool IsShouldBeActivated();

	};

}