#include "CUserCMD.h"

#include <cmath>
#include "../Utils/Math/Math.h"
#include "../Utils/Marker.h"

SSDK::fix_usercmd::fix_usercmd(CUserCmd* pUserCmd)
{
	POLY_MARKER;
	m_pUserCmd   = pUserCmd;
	m_oldUserCmd = *pUserCmd;
}

SSDK::fix_usercmd::~fix_usercmd()
{
	POLY_MARKER;
	float fDeltaYaw;
	float f1;
	float f2;

	if (m_oldUserCmd.m_vecViewAngles.y < 0.f)
		f1 = 360.f + m_oldUserCmd.m_vecViewAngles.y;
	else
		f1 = m_oldUserCmd.m_vecViewAngles.y;

	POLY_MARKER;

	if (m_pUserCmd->m_vecViewAngles.y < 0.f)
		f2 = 360.f + m_pUserCmd->m_vecViewAngles.y;
	else
		f2 = m_pUserCmd->m_vecViewAngles.y;
	POLY_MARKER;

	if (f2 < f1)
		fDeltaYaw = abs(f2 - f1);
	else
		fDeltaYaw = 360.f - abs(f1 - f2);

	fDeltaYaw = 360.f - fDeltaYaw;
	POLY_MARKER;

	m_pUserCmd->m_fForwardMove = cos(Utils::DegToRad(fDeltaYaw)) * m_oldUserCmd.m_fForwardMove + cos(Utils::DegToRad(fDeltaYaw + 90.f)) * m_oldUserCmd.m_fSideMove;
	m_pUserCmd->m_fSideMove    = sin(Utils::DegToRad(fDeltaYaw)) * m_oldUserCmd.m_fForwardMove + sin(Utils::DegToRad(fDeltaYaw + 90.f)) * m_oldUserCmd.m_fSideMove;
	POLY_MARKER;
}
