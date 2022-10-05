#include "TriggerBot.h"

#include "../Globals/Interfaces.h"
#include  "../SDK/Finder.h"
#include "../Utils/Marker.h"


using namespace Hacks;

TriggerBot::TriggerBot(Settings::TriggerBotSettings* settings) : CHackFeature(settings)
{

}


void TriggerBot::Work()
{
	POLY_MARKER;
	static auto pForceAttack = SSDK::GetForceAttack();

	if (!IsShouldBeActivated()) return;


	const auto pLocalPlayer = SSDK::ClientBase::GetLocalPlayer();
	const auto vecRayStart = pLocalPlayer->m_vecOrigin + pLocalPlayer->m_vecViewOffset;

	POLY_MARKER;

	SSDK::CGameTrace   trace;
	SSDK::Ray_t        ray;
	SSDK::CTraceFilter tracefilter;
	tracefilter.pSkip = pLocalPlayer;

	POLY_MARKER;


	ray.Init(vecRayStart, vecRayStart.Transform(pLocalPlayer->m_vecViewAngles+pLocalPlayer->m_vecAimPuchAngle, 9000.f));

	POLY_MARKER;

	GlobalVars::g_pIEngineTrace->TraceRay(ray, MASK_SHOT | CONTENTS_GRATE, &tracefilter, &trace);
	const auto pHittedEntity = (SSDK::CBaseEntity*)trace.m_pHitEntity;

	if (!pHittedEntity or (pHittedEntity->GetClientClass()->m_iClassId != SSDK::ClassIndex::CCSPlayer) or !pHittedEntity->IsAlive() or pHittedEntity->m_iTeamNum == pLocalPlayer->m_iTeamNum)
		return;

	POLY_MARKER;

	*pForceAttack = 6;
}


