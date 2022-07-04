#pragma once
#include "AimBot.h"
#include "../Globals/Interfaces.h"
#include "../Utils/Math/Math.h"
#include "../Utils/Marker.h"


using namespace Hacks;

CAimBot::CAimBot(Settings::CAimBotSettings* pSettings, CUserCmd* ppUsrCmd) : CHackingFeature(pSettings)
{
	m_pCUsrCmd = ppUsrCmd;
}
int CAimBot::GetBoneIDBySelectedTab(const int iTabIndex)
{
	switch (iTabIndex)
	{
	case 0:
		return CBaseEntity::Bone::HEAD;
		break;
	case 1:
		return CBaseEntity::Bone::BODY;
		break;
	case 2:
		return CBaseEntity::Bone::LEGS;
		break;
	}

	return CBaseEntity::Bone::HEAD;
}
void CAimBot::Work()
{
	using namespace GlobalVars;

	POLY_MARKER;

	auto pAimBotSettings = (Settings::CAimBotSettings*)m_pSettings;

	if (!IsShouldBeActivated())
	{
		pAimBotSettings->m_bIsWorking      = false;
		pAimBotSettings->m_pCurrentTarget  = nullptr;
		return;
	}
	pAimBotSettings->m_bIsWorking = true;

	int aimBone = GetBoneIDBySelectedTab(reinterpret_cast<Settings::CAimBotSettings*>(m_pSettings)->m_iSelectedHitBox);

	CBaseEntity* pEnt = nullptr;

	POLY_MARKER;

	switch (pAimBotSettings->m_iPriorityType)
	{
	case Settings::CAimBotSettings::PriorityType::FieldOfView:
		pEnt = GetClosestTargetByFov(aimBone);
		break;

	case Settings::CAimBotSettings::PriorityType::Distance:
		pEnt = GetClosestTargetByDistance(aimBone);
		break;

	default:
		pEnt = GetClosestTargetByFov(aimBone);
		break;
	}

	POLY_MARKER;

	if (!pEnt)
	{
		pAimBotSettings->m_pCurrentTarget = nullptr;
		return;
	}
	if (pAimBotSettings->m_iHitBoxFilterMode == Settings::CAimBotSettings::HitBoxFilterMode::Dynamic)
		aimBone = GetBoneIdByEntityHealth(pEnt);

	pAimBotSettings->m_pCurrentTarget = pEnt;

	if (IfEntityInFov(pEnt, aimBone))
	{
		if (pAimBotSettings->m_fSmooth > 0.f)
			AimSmooth(pEnt, aimBone);
		else
		{
			AimPlain(pEnt, aimBone);
			if (pAimBotSettings->m_bRcsControle)
				m_pCUsrCmd->viewangles = Utils::NormalizeViewAngles(m_pCUsrCmd->viewangles - GlobalVars::g_pClient->pLocalPlayer->m_vecAimPuchAngle * 2.f);
		}
	}
	
	if (pAimBotSettings->m_bAutoShot)
		g_pClient->SendAttackCode();

	POLY_MARKER;
}
void CAimBot::AimPlain(const CBaseEntity* pEnt, int iBoneId)
{
	POLY_MARKER;

	auto calcedAngles = CalcAimViewAngles(pEnt, iBoneId);

	if (fabs(calcedAngles.x) <= 89.f and fabs(calcedAngles.y) <= 180.f)
	{
		m_pCUsrCmd->viewangles = calcedAngles;
	}
}
void CAimBot::AimSmooth(const CBaseEntity* pEnt, int iBoneId)
{
	using namespace GlobalVars;

	POLY_MARKER;

	auto pAimBotSettings = (Settings::CAimBotSettings*)m_pSettings;

	ImVec3 targetViewAngle = CalcAimViewAngles(pEnt, iBoneId);

	ImVec3 currentAngle = m_pCUsrCmd->viewangles;

	ImVec3 diff = targetViewAngle - currentAngle;

	diff = Utils::ClampViewAngles(Utils::NormalizeViewAngles(diff));

	ImVec3 angle = currentAngle;

	angle.x += diff.x / pAimBotSettings->m_fSmooth;
	angle.y += diff.y / pAimBotSettings->m_fSmooth;

	POLY_MARKER;

	angle = Utils::ClampViewAngles(Utils::NormalizeViewAngles(angle));
	
	if (fabs(angle.x) <= 89.f and fabs(angle.y) <= 180.f)
	{
		m_pCUsrCmd->viewangles = angle;
	}
}
bool CAimBot::IfEntityInFov(const CBaseEntity* entity, const int iBoneId) const
{
	using namespace GlobalVars;
	auto pAimBotSettings = (Settings::CAimBotSettings*)m_pSettings;

	POLY_MARKER;

	ImVec3  pLocalPlayerAngles = m_pCUsrCmd->viewangles;
	ImVec3  targetAngles = CalcAimViewAngles(entity, iBoneId);
	ImVec3  deltaFov = (pLocalPlayerAngles - targetAngles).Abs();
	POLY_MARKER;

	return  pAimBotSettings->m_fFov >= deltaFov.Length2D();
}
CBaseEntity* CAimBot::GetClosestTargetByDistance(int bone)
{
	POLY_MARKER;
	std::vector<CBaseEntity*> validEntities = GetValidEntities(bone);
	
	if (validEntities.size() == 0)
		return NULL;
	POLY_MARKER;
	std::sort(validEntities.begin(), validEntities.end(),

		[](CBaseEntity* first, CBaseEntity* second)
		{
			return GlobalVars::g_pClient->pLocalPlayer->CalcDistaceToEntity(first) < GlobalVars::g_pClient->pLocalPlayer->CalcDistaceToEntity(second);
		});
	return validEntities[0];
}

CBaseEntity* CAimBot::GetClosestTargetByFov(int bone)
{
	std::vector<CBaseEntity*> validEntities = GetValidEntities(bone);
	POLY_MARKER;

	if (validEntities.size() == 0)
		return NULL;

	POLY_MARKER;

	auto localPlayer = GlobalVars::g_pClient->pLocalPlayer;

	std::sort(validEntities.begin(), validEntities.end(),

		[this, bone](CBaseEntity* pEntityFirst, CBaseEntity* pEntitySecond)
		{
			ImVec3 diffFirstEntity = (CalcAimViewAngles(pEntityFirst,   bone) - m_pCUsrCmd->viewangles).Abs();
			ImVec3 diffSecondEntity = (CalcAimViewAngles(pEntitySecond, bone) - m_pCUsrCmd->viewangles).Abs();

			return diffFirstEntity.Length2D() < diffSecondEntity.Length2D();
		});

	return validEntities[0];
}

ImVec3 CAimBot::CalcAimViewAngles(const CBaseEntity* pEntity, const int bone) 
{
	ImVec3 calculated;

	ImVec3 targetPosition = pEntity->GetBonePosition(bone);

	ImVec3 localCameraPosition = GlobalVars::g_pClient->pLocalPlayer->GetCameraPosition();

	POLY_MARKER;

	float distance = GlobalVars::g_pClient->pLocalPlayer->CalcDistaceToEntity(pEntity);

	calculated.x = - Utils::RadiansToDegrees(asinf((targetPosition.z - localCameraPosition.z) / distance));
	calculated.y =   Utils::RadiansToDegrees(atan2f(targetPosition.y - localCameraPosition.y, targetPosition.x - localCameraPosition.x));

	return calculated;
}

std::vector<CBaseEntity*> CAimBot::GetValidEntities(const int boneId) const
{
	std::vector<CBaseEntity*> validEntities;
	const auto localPlayer = GlobalVars::g_pClient->pLocalPlayer;

	POLY_MARKER;

	for (int i = 1; i < 33; i++)
	{
		CBaseEntity* pEntites = reinterpret_cast<CBaseEntity*>(GlobalVars::g_pIEntityList->GetClientEntity(i));

		if (!pEntites or !pEntites->m_IsVisible)
			continue;

		if (pEntites->IsAlive() and !pEntites->m_bDormant and localPlayer->m_iTeamNum != pEntites->m_iTeamNum and IfEntityInFov(pEntites, boneId) and pEntites->m_IsVisible)
			validEntities.push_back(pEntites);

	}
	return validEntities;

}

int Hacks::CAimBot::GetBoneIdByEntityHealth(const CBaseEntity* pEntiy) const
{
	auto pSettings = (Settings::CAimBotSettings*)m_pSettings;
	POLY_MARKER;
	if (pEntiy->GetHealthPercent() > pSettings->m_iHealthBorder)
		return CBaseEntity::Bone::HEAD;
	
	return CBaseEntity::Bone::BODY;
}
