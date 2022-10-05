
#include "hack.h"

using namespace Hacks;
CHackFeature::CHackFeature(Settings::CBaseSettings* pSettings)
{
	m_pSettings = pSettings;
}

bool CHackFeature::IsShouldBeActivated() const
{
	if (!m_pSettings->m_bOnKey)
		return m_pSettings->m_bActive;
	return m_pSettings->m_bActive and GetAsyncKeyState(m_pSettings->m_iBindKey) & 0x8000;
}
