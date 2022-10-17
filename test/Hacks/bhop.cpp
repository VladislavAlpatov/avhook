#include "bhop.h"
#include "../Utils/Marker.h"
#include "../SDK/ClientBase.h"

using namespace Hacks;


void CBunnyHop::Work()
{
	POLY_MARKER;
	if (!IsShouldBeActivated())
		return;
	POLY_MARKER;
	if (!(SSDK::ClientBase::GetLocalPlayer()->m_fFlags & 1))
		m_pUserCmd->m_iButtons &= ~SSDK::CUserCmd::IN_JUMP;
	POLY_MARKER;
}
CBunnyHop::CBunnyHop(SSDK::CUserCmd* pUserCmd, Settings::CBunnyHopSettings* pSettings) : CHackFeature(pSettings)
{
	POLY_MARKER;
	m_pUserCmd = pUserCmd;
}