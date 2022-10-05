#include "bhop.h"
#include "../Globals/Interfaces.h"
#include "../Utils/Marker.h"
using namespace Hacks;


void CBunnyHop::Work()
{
	if (!IsShouldBeActivated())
		return;
	POLY_MARKER;
	if (!(SSDK::ClientBase::GetLocalPlayer()->m_fFlags & 1))
		m_pUserCmd->m_iButtons &= ~2;
	POLY_MARKER;
}
CBunnyHop::CBunnyHop(SSDK::CUserCmd* pUserCmd, Settings::CBunnyHopSettings* pSettings) : CHackFeature(pSettings)
{
	POLY_MARKER;
	m_pUserCmd = pUserCmd;
}