
/*
 * Copyright (c) 2022.
 * Created by Alpatov Softworks with love in Russia.
 */

#include "AimBot.h"
#include "../Globals/Interfaces.h"
#include "TriggerBot.h"

#include "../Utils/Math/Math.h"
#include "../Utils/Marker.h"
#include "../SDK/ClientBase.h"

using namespace Hacks;

CAimBot::CAimBot(Settings::CAimBotSettings* settings, SSDK::CUserCmd* pUsrCmd) : CHackFeature(settings)
{
	POLY_MARKER;
	m_pCUsrCmd = pUsrCmd;
}
void CAimBot::Work()
{
	using namespace GlobalVars;

	POLY_MARKER;

	const auto pAimBotSettings = GetSettings<Settings::CAimBotSettings>();
	const auto pLocalPlayer = SSDK::ClientBase::GetLocalPlayer();

	if (!IsShouldBeActivated())
	{
		pAimBotSettings->m_bIsWorking      = false;
		pAimBotSettings->m_pCurrentTarget  = nullptr;
		return;
	}
	pAimBotSettings->m_bIsWorking = true;

	int iTargetBone = GetSettings<Settings::CAimBotSettings>()->m_iSelectedHitBox;

	SSDK::CBaseEntity* pEnt = nullptr;

	POLY_MARKER;

	switch (pAimBotSettings->m_iPriorityType)
	{
	case Settings::CAimBotSettings::PriorityType::FieldOfView:
		pEnt = GetClosestTargetByFov();
		break;

	case Settings::CAimBotSettings::PriorityType::Distance:
		pEnt = GetClosestTargetByDistance();
		break;

	default:
		pEnt = GetClosestTargetByFov();
		break;
	}

	POLY_MARKER;

	if (!pEnt)
	{
		pAimBotSettings->m_pCurrentTarget = nullptr;
		return;
	}

	if (pAimBotSettings->m_iHitBoxFilterMode == Settings::CAimBotSettings::HitBoxFilterMode::Dynamic)
		iTargetBone = GetBoneIdByEntityHealth(pEnt);

	pAimBotSettings->m_pCurrentTarget = pEnt;

	if (IfEntityInFov(pEnt))
	{
		if (pAimBotSettings->m_fSmooth > 0.f)
			AimSmooth(pEnt);
		else
		{
			AimPlain(pEnt);

			if (pAimBotSettings->m_bRcsControle)
				m_pCUsrCmd->m_vecViewAngles = Utils::NormalizeViewAngles(m_pCUsrCmd->m_vecViewAngles - pLocalPlayer->m_vecAimPuchAngle * 2.f);
		}
	}
	
	if (pAimBotSettings->m_bAutoShot and  Hacks::TriggerBot::IsEnemyEntityInSight())
		m_pCUsrCmd->m_iButtons |= SSDK::CUserCmd::IN_ATTACK;

	POLY_MARKER;
}
void CAimBot::AimPlain(const SSDK::CBaseEntity* pEntity) const
{
	POLY_MARKER;
	const auto calculatedViewAngle = CalcAimViewAngles(pEntity, GetSettings<Settings::CAimBotSettings>()->m_iSelectedHitBox);
	if (fabs(calculatedViewAngle.x) <= 89.f && fabs(calculatedViewAngle.y) <= 180.f)
		m_pCUsrCmd->m_vecViewAngles = calculatedViewAngle;
}
void CAimBot::AimSmooth(const SSDK::CBaseEntity* pEntity) const
{
	using namespace GlobalVars;

	POLY_MARKER;

	const auto pAimBotSettings = GetSettings<Settings::CAimBotSettings>();

	const ImVec3 targetViewAngle = CalcAimViewAngles(pEntity, pAimBotSettings->m_iSelectedHitBox);

	ImVec3 currentAngle = m_pCUsrCmd->m_vecViewAngles;

	const ImVec3 diff = Utils::ClampViewAngles(Utils::NormalizeViewAngles(targetViewAngle - currentAngle));


	currentAngle.x += diff.x / pAimBotSettings->m_fSmooth;
	currentAngle.y += diff.y / pAimBotSettings->m_fSmooth;

	POLY_MARKER;

	currentAngle = Utils::ClampViewAngles(Utils::NormalizeViewAngles(currentAngle));
	
	if (fabs(currentAngle.x) <= 89.f && fabs(currentAngle.y) <= 180.f)
	{
		m_pCUsrCmd->m_vecViewAngles = currentAngle;
	}
}
bool CAimBot::IfEntityInFov(const SSDK::CBaseEntity* pEntity) const
{
	using namespace GlobalVars;
	const auto pAimBotSettings = GetSettings<Settings::CAimBotSettings>();

	POLY_MARKER;

	const ImVec3  pLocalPlayerAngles = m_pCUsrCmd->m_vecViewAngles;
	const ImVec3  targetAngles = CalcAimViewAngles(pEntity, pAimBotSettings->m_iSelectedHitBox);
	ImVec3  deltaFov = (pLocalPlayerAngles - targetAngles);
	POLY_MARKER;

	return  deltaFov.Length2D() <= pAimBotSettings->m_fFov;
}
SSDK::CBaseEntity* CAimBot::GetClosestTargetByDistance() const
{
	POLY_MARKER;
	auto validEntities = GetValidEntities();
	
	if (validEntities.empty())
		return nullptr;
	POLY_MARKER;
	auto pLocalPlayer = SSDK::ClientBase::GetLocalPlayer();
	std::sort(validEntities.begin(), validEntities.end(),

		[pLocalPlayer](const SSDK::CBaseEntity* first, const SSDK::CBaseEntity* second)
		{
			return pLocalPlayer->CalcDistanceToEntity(first) < pLocalPlayer->CalcDistanceToEntity(second);
		});
	return validEntities[0];
}
SSDK::CBaseEntity* CAimBot::GetClosestTargetByFov() const
{

	POLY_MARKER;
	std::vector<SSDK::CBaseEntity*> validEntities = GetValidEntities();


	if (validEntities.empty()) return nullptr;

	POLY_MARKER;
	int iBone = GetSettings<Settings::CAimBotSettings>()->m_iSelectedHitBox;

	std::sort(validEntities.begin(), validEntities.end(),

		[this, iBone](const SSDK::CBaseEntity* pEntityFirst, const SSDK::CBaseEntity* pEntitySecond)
		{
			const ImVec3 diffFirstEntity = (CalcAimViewAngles(pEntityFirst,   iBone) - m_pCUsrCmd->m_vecViewAngles).Abs();
			const ImVec3 diffSecondEntity = (CalcAimViewAngles(pEntitySecond, iBone) - m_pCUsrCmd->m_vecViewAngles).Abs();

			return diffFirstEntity.Length2D() < diffSecondEntity.Length2D();
		});

	return validEntities[0];
}
ImVec3 CAimBot::CalcAimViewAngles(const SSDK::CBaseEntity* pEntity, const int bone) 
{
	POLY_MARKER;
	const auto pLocalPlayer = SSDK::ClientBase::GetLocalPlayer();
	return CalcAimViewAngles(pLocalPlayer->GetCameraPosition(), pEntity->GetBonePosition(bone));
}
ImVec3 CAimBot::CalcAimViewAngles(const ImVec3& origin, const ImVec3& target)
{
	POLY_MARKER;
	ImVec3 out;
	const float distance = origin.DistTo(target);

	// Make x negative since -89 is top and 89 is bottom
	out.x = -Utils::RadToDeg(asinf((target.z - origin.z) / distance));
	out.y = Utils::RadToDeg(atan2f(target.y  - origin.y, target.x - origin.x));

	return out;
}
std::vector<SSDK::CBaseEntity*> CAimBot::GetValidEntities() const
{
	POLY_MARKER;
	std::vector<SSDK::CBaseEntity*> validEntities;
	const auto localPlayer = SSDK::ClientBase::GetLocalPlayer();

	POLY_MARKER;

	for (int i = 1; i < 33; i++)
	{
		SSDK::CBaseEntity* pEntity =GlobalVars::g_pIEntityList->GetClientEntity(i);

		if (!pEntity)
			continue;

		if (pEntity->IsAlive() && !pEntity->m_bDormant && localPlayer->m_iTeamNum != pEntity->m_iTeamNum && IfEntityInFov(pEntity) && IsEntityVisible(pEntity))
			validEntities.push_back(pEntity);

	}
	return validEntities;

}
int Hacks::CAimBot::GetBoneIdByEntityHealth(const SSDK::CBaseEntity* pEntity) const
{
	const auto pSettings = GetSettings<Settings::CAimBotSettings>();

	POLY_MARKER;
	if (pEntity->GetHealthPercent() > pSettings->m_iHealthBorder)
		return SSDK::CBaseEntity::Bone::HEAD;
	
	return SSDK::CBaseEntity::Bone::BODY;
}
bool Hacks::CAimBot::IsEntityVisible(const SSDK::CBaseEntity* pEntity) const
{
	const auto pLocalPlayer = SSDK::ClientBase::GetLocalPlayer();


	if (!pEntity->IsAlive())
			return false;

	SSDK::CGameTrace   trace;
	SSDK::Ray_t        ray;
	SSDK::CTraceFilter tracefilter;

	tracefilter.m_pSkip = static_cast<void*>(pLocalPlayer);
		
	ray.Init(pLocalPlayer->m_vecOrigin + pLocalPlayer->m_vecViewOffset, pEntity->GetBonePosition(GetSettings<Settings::CAimBotSettings>()->m_iSelectedHitBox));
		
	GlobalVars::g_pIEngineTrace->TraceRay(ray, MASK_SHOT | CONTENTS_GRATE, &tracefilter, &trace);

	return trace.m_pHitEntity == pEntity;
}
