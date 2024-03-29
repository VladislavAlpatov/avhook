/*
 * Copyright (c) 2022.
 * Created by Alpatov Softworks with love in Russia.
 */

#include "TriggerBot.h"

#include "../Globals/Interfaces.h"
#include  "../SDK/Finder.h"
#include "../Utils/Marker.h"
#include "../SDK/ClientBase.h"


using namespace Hacks;

TriggerBot::TriggerBot(Settings::TriggerBotSettings* settings, SSDK::CUserCmd* pUsrCmd) : CHackFeature(settings)
{
	POLY_MARKER;
	m_pUserCmd = pUsrCmd;
}




void TriggerBot::Work()
{
	POLY_MARKER;

	if (IsShouldBeActivated() && IsEnemyEntityInSight())
		m_pUserCmd->m_iButtons |= SSDK::CUserCmd::IN_ATTACK;

}

bool TriggerBot::IsEnemyEntityInSight()
{
	POLY_MARKER;
	const auto pLocalPlayer = SSDK::ClientBase::GetLocalPlayer();
	const auto vecRayStart = pLocalPlayer->m_vecOrigin + pLocalPlayer->m_vecViewOffset;

	POLY_MARKER;

	SSDK::CGameTrace   trace;
	SSDK::Ray_t        ray;
	SSDK::CTraceFilter tracefilter;
	tracefilter.m_pSkip = pLocalPlayer;

	POLY_MARKER;
	ray.Init(vecRayStart, vecRayStart.Transform(pLocalPlayer->m_vecViewAngles + pLocalPlayer->m_vecAimPuchAngle, 9000.f));
	GlobalVars::g_pIEngineTrace->TraceRay(ray, MASK_SHOT | CONTENTS_GRATE, &tracefilter, &trace);


	const auto pHitEntity = (SSDK::CBaseEntity*)trace.m_pHitEntity;
	POLY_MARKER;


	return !(!pHitEntity || (pHitEntity->GetClientClass()->m_iClassId != SSDK::ClassIndex::CCSPlayer) || !pHitEntity->IsAlive() || pHitEntity->m_iTeamNum == pLocalPlayer->m_iTeamNum);

}


