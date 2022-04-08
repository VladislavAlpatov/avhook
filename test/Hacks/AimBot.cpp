#pragma once
#include "AimBot.h"
#include "../Globals/GlobalVars.h"

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
				m_pCUsrCmd->viewangles = NormalizeViewAngles(m_pCUsrCmd->viewangles - GlobalVars::pClient->pLocalPlayer->m_vecAimPuchAngle * 2.f);
		}
	}
	
	if (pAimBotSettings->m_bAutoShot)
		pClient->SendAttackCode();

}
void CAimBot::AimPlain(const CBaseEntity* pEnt, int iBoneId)
{
	auto calcedAngles = CalcAimViewAngles(pEnt, iBoneId);

	if (fabs(calcedAngles.x) <= 89.f and fabs(calcedAngles.y) <= 180.f)
	{
		m_pCUsrCmd->viewangles = calcedAngles;
	}
}
void CAimBot::AimSmooth(const CBaseEntity* pEnt, int iBoneId)
{
	using namespace GlobalVars;

	auto pAimBotSettings = (Settings::CAimBotSettings*)m_pSettings;

	ImVec3 targetViewAngle = CalcAimViewAngles(pEnt, iBoneId);

	ImVec3 currentAngle = m_pCUsrCmd->viewangles;

	ImVec3 diff = targetViewAngle - currentAngle;

	diff = ClampViewAngles(NormalizeViewAngles(diff));

	ImVec3 angle = currentAngle;

	angle.x += diff.x / pAimBotSettings->m_fSmooth;
	angle.y += diff.y / pAimBotSettings->m_fSmooth;

	angle = ClampViewAngles(NormalizeViewAngles(angle));
	
	if (fabs(angle.x) <= 89.f and fabs(angle.y) <= 180.f)
	{
		m_pCUsrCmd->viewangles = angle;
	}
}
bool CAimBot::IfEntityInFov(const CBaseEntity* entity, const int iBoneId) const
{
	using namespace GlobalVars;
	auto pAimBotSettings = (Settings::CAimBotSettings*)m_pSettings;

	ImVec3  pLocalPlayerAngles   = m_pCUsrCmd->viewangles;
	ImVec3  targetAngles         = CalcAimViewAngles(entity, iBoneId);
	ImVec3  deltaFov             = pLocalPlayerAngles - targetAngles;

	return fabs(deltaFov.x) <= pAimBotSettings->m_fFov and fabs(deltaFov.y) <= pAimBotSettings->m_fFov;
}
CBaseEntity* CAimBot::GetClosestTargetByDistance(int bone)
{
	std::vector<CBaseEntity*> validEntities = GetValidEntities(bone);
	
	if (validEntities.size() == 0)
		return NULL;

	std::sort(validEntities.begin(), validEntities.end(),

		[](CBaseEntity* first, CBaseEntity* second)
		{
			return GlobalVars::pClient->pLocalPlayer->CalcDistaceToEntity(first) < GlobalVars::pClient->pLocalPlayer->CalcDistaceToEntity(second);
		});
	return validEntities[0];
}

CBaseEntity* CAimBot::GetClosestTargetByFov(int bone)
{
	std::vector<CBaseEntity*> validEntities = GetValidEntities(bone);

	if (validEntities.size() == 0)
		return NULL;

	auto localPlayer = GlobalVars::pClient->pLocalPlayer;

	std::sort(validEntities.begin(), validEntities.end(),

		[this, bone](CBaseEntity* pEntityFirst, CBaseEntity* pEntitySecond)
		{
			ImVec3 diffFirstEntity = (CalcAimViewAngles(pEntityFirst,   bone) - m_pCUsrCmd->viewangles).Abs();
			ImVec3 diffSecondEntity = (CalcAimViewAngles(pEntitySecond, bone) - m_pCUsrCmd->viewangles).Abs();

			return diffFirstEntity.Length2D() < diffSecondEntity.Length2D();
		});

	return validEntities[0];
}

ImVec3 CAimBot::CalcAimViewAngles(const CBaseEntity* pEntity, const int bone) const 
{
	ImVec3 calculated;

	ImVec3 targetPosition = pEntity->GetBonePosition(bone);

	ImVec3 localCameraPosition = GlobalVars::pClient->pLocalPlayer->GetCameraPosition();

	float distance = GlobalVars::pClient->pLocalPlayer->CalcDistaceToEntity(pEntity);

	calculated.x = -asinf((targetPosition.z - localCameraPosition.z) / distance) * (180.f / 3.1415926f);
	calculated.y = atan2f(targetPosition.y - localCameraPosition.y, targetPosition.x - localCameraPosition.x) * (180.f / 3.1415926f);

	return calculated;
}

ImVec3 CAimBot::NormalizeViewAngles(ImVec3 vecViewAngle)
{
	if (vecViewAngle.x > 180)
		vecViewAngle.x -= 360.0f;

	if (vecViewAngle.x < 180)
		vecViewAngle.x += 360.0f;

	if (vecViewAngle.y > 180)
		vecViewAngle.y -= 360.0f;

	if (vecViewAngle.y < 180)
		vecViewAngle.y += 360.0f;

	return vecViewAngle;
}
ImVec3 CAimBot::ClampViewAngles(ImVec3 vecViewAngles)
{
	if (vecViewAngles.x > 89.0f && vecViewAngles.x <= 180.0f)
		vecViewAngles.x = 89.0f;

	if (vecViewAngles.x > 180.0f)
		vecViewAngles.x = vecViewAngles.x - 360.0f;

	if (vecViewAngles.x < -89.0f)
		vecViewAngles.x = -89.0f;

	if (vecViewAngles.y > 180.0f)
		vecViewAngles.y = vecViewAngles.y - 360.0f;

	if (vecViewAngles.y < -180.0f)
		vecViewAngles.y = vecViewAngles.y + 360.0f;

	return vecViewAngles;
}

std::vector<CBaseEntity*> CAimBot::GetValidEntities(const int boneId) const
{
	std::vector<CBaseEntity*> validEntities;
	const auto localPlayer = GlobalVars::pClient->pLocalPlayer;


	for (int i = 1; i < 33; i++)
	{
		CBaseEntity* pEntites = reinterpret_cast<CBaseEntity*>(GlobalVars::pIEntityList->GetClientEntity(i));

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

	if (pEntiy->GetHealthPercent() > pSettings->m_iHealthBorder)
		return CBaseEntity::Bone::HEAD;
	
	return CBaseEntity::Bone::BODY;
}
