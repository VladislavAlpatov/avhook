//========= Copyright Alpatov Softworks, All rights reserved. ============//
//
// Base class for all cheat features except esp
//
//===============================================================================



#pragma once
#include <Windows.h>
#include "../Menu/Settings.h"

namespace Hacks
{
	using namespace SSDK;

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