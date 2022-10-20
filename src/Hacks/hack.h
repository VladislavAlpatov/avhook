//========= Copyright Alpatov Softworks, All rights reserved. ============//
//
// Base class for all cheat features except esp
//
//===============================================================================


#pragma once
#include "../Menu/Settings.h"

#include <stdexcept>
#include "../Utils/xorstr.h"

namespace Hacks
{

	class CHackFeature
	{
	public:
		CHackFeature(Settings::CBaseSettings* pSettings);
		virtual void Work() = 0;
	private:

		Settings::CBaseSettings* m_pSettings = nullptr;
	protected:

		bool IsShouldBeActivated() const;

		template <typename Type>
		Type* GetSettings() const
		{
			auto pSet = dynamic_cast<Type*>(m_pSettings);
			if (!pSet)
				throw std::runtime_error(xorstr("Bad cast for feature settings class"));
			return pSet;
		}
	};

}
