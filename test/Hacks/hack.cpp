#include "hack.h"
using namespace Hacks;
CHackingFeature::CHackingFeature(CBaseSettings* pSettings)
{
	m_pSettings = pSettings;
}

bool CHackingFeature::IsShouldBeActivated()
{
	if (!m_pSettings->m_bOnKey)
		return m_pSettings->m_bActive;
	return m_pSettings->m_bActive and GetAsyncKeyState(m_pSettings->m_iBindKey) & 0x8000;
}