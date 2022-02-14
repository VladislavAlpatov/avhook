#include "AimBot.h"

CAimBot::CAimBot(AimBotSettings* pSettings, CUserCmd* ppUsrCmd) : CHackingFeature(pSettings)
{
	m_pCUsrCmd = ppUsrCmd;
}
int CAimBot::GetBoneIDBySelectedTab()
{
	switch (reinterpret_cast<AimBotSettings*>(m_pSettings)->m_iSelectedHitBox)
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

	auto pAimBotSettings = (AimBotSettings*)m_pSettings;

	if (!IsShouldBeActivated())
	{
		pAimBotSettings->m_bIsWorking      = false;
		pAimBotSettings->m_pCurrentTarget  = nullptr;
		return;
	}
	pAimBotSettings->m_bIsWorking = true;

	int aimBone = GetBoneIDBySelectedTab();

	POLY_MARKER;
	CBaseEntity* pEnt = nullptr;

	switch (pAimBotSettings->m_iPriorityType)
	{
	case AimBotSettings::PriorityType::FieldOfView:
		pEnt = GetClosestTargetByFov(aimBone);
		break;

	case AimBotSettings::PriorityType::Distance:
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

	pAimBotSettings->m_pCurrentTarget = pEnt;

	if (IfEntityInFov(pEnt, aimBone))
	{
		if (pAimBotSettings->m_fSmooth > 0.f)
			AimSmooth(pEnt, aimBone);
		else
			AimPlain(pEnt, aimBone);
	}

	if (pAimBotSettings->m_bAutoShot)
		client->SendAttackCode();

}
void CAimBot::AimPlain(CBaseEntity* pEnt, int iBoneId)
{
	POLY_MARKER
	auto calcedAngles = CalcAimViewAngles(pEnt, iBoneId);

	if (fabs(calcedAngles.x) <= 89.f and fabs(calcedAngles.y) <= 180.f)
	{
		m_pCUsrCmd->viewangles = calcedAngles;
	}
}
void CAimBot::AimSmooth(CBaseEntity* pEnt, int iBoneId)
{
	POLY_MARKER
	using namespace GlobalVars;

	auto pAimBotSettings = (AimBotSettings*)m_pSettings;

	ImVec3 targetViewAngle = CalcAimViewAngles(pEnt, iBoneId);

	ImVec3 currentAngle = m_pCUsrCmd->viewangles;

	ImVec3 diff = targetViewAngle - currentAngle;

	diff = ClampViewAngles(NormalizeViewAngles(diff));

	ImVec3 angle = currentAngle;

	angle.x += diff.x / pAimBotSettings->m_fSmooth;
	angle.y += diff.y / pAimBotSettings->m_fSmooth;

	angle = NormalizeViewAngles(angle);
	angle = ClampViewAngles(angle);

	if (fabs(angle.x) <= 89.f and fabs(angle.y) <= 180.f)
	{
		m_pCUsrCmd->viewangles = angle;
	}
}
bool CAimBot::IfEntityInFov(CBaseEntity* entity, int iBoneId)
{
	using namespace GlobalVars;
	auto pAimBotSettings = (AimBotSettings*)m_pSettings;

	ImVec3  pLocalPlayerAngles  = m_pCUsrCmd->viewangles;
	ImVec3  targetAngles        = client->pLocalPlayer->GetAimTargetAngles(entity, iBoneId);
	ImVec2  deltaFov            = ImVec2(pLocalPlayerAngles.x - targetAngles.x, pLocalPlayerAngles.y - targetAngles.y);

	if (fabs(deltaFov.x) <= pAimBotSettings->m_fFov and fabs(deltaFov.y) <= pAimBotSettings->m_fFov)
		return true;
	return false;
}
CBaseEntity* CAimBot::GetClosestTargetByDistance(int bone)
{
	CBaseEntity* entitylist[32] = { 0 };
	auto localPlayer = GlobalVars::client->pLocalPlayer;

	IClientEntityList* VClientEntityList = GlobalVars::pIEntityList;

	int counter = 0;

	for (int i = 1; i < 33; i++)
	{
		CBaseEntity* entity = reinterpret_cast<CBaseEntity*>(VClientEntityList->GetClientEntity(i));

		if (!entity or !entity->m_IsVisible)
			continue;

		if (entity->m_iHealth > 0 and !entity->m_bDormant and localPlayer->m_iTeamNum != entity->m_iTeamNum and IfEntityInFov(entity, bone) and entity->m_IsVisible)
			entitylist[counter++] = entity;

	}
	for (int i = 0; i < counter; i++)
	{
		for (int j = 0; j < counter - 1; j++)
		{
			if (localPlayer->CalcDistaceToEntity(entitylist[j]) > localPlayer->CalcDistaceToEntity(entitylist[j + 1]))
			{
				auto temp = entitylist[j];
				entitylist[j] = entitylist[j + 1];
				entitylist[j + 1] = temp;
			}
		}

	}
	return entitylist[0];
}

CBaseEntity* CAimBot::GetClosestTargetByFov(int bone)
{
	CBaseEntity* entitylist[32] = { 0 };
	auto localPlayer = GlobalVars::client->pLocalPlayer;

	IClientEntityList* VClientEntityList = GlobalVars::pIEntityList;

	int counter = 0;

	for (int i = 1; i < 33; i++)
	{
		CBaseEntity* entity = reinterpret_cast<CBaseEntity*>(VClientEntityList->GetClientEntity(i));

		if (!entity or !entity->m_IsVisible)
			continue;

		if (entity->m_iHealth > 0 and !entity->m_bDormant and localPlayer->m_iTeamNum != entity->m_iTeamNum and IfEntityInFov(entity, bone) and entity->m_IsVisible)
			entitylist[counter++] = entity;

	}
	for (int i = 0; i < counter; i++)
	{
		for (int j = 0; j < counter - 1; j++)
		{
			ImVec3 diffFirstEntity = (CalcAimViewAngles(entitylist[j], bone) - m_pCUsrCmd->viewangles).Abs();
			ImVec3 diffSecondEntity = (CalcAimViewAngles(entitylist[j+1], bone) - m_pCUsrCmd->viewangles).Abs();
			if (diffFirstEntity.Length2D() > diffSecondEntity.Length2D())
			{
				auto temp = entitylist[j];
				entitylist[j] = entitylist[j + 1];
				entitylist[j + 1] = temp;
			}
		}

	}
	return entitylist[0];
}

ImVec3 CAimBot::CalcAimViewAngles(CBaseEntity* pEntity, int bone)
{
	ImVec3 calculated;

	ImVec3 targetPosition = pEntity->GetBonePosition(bone);

	ImVec3 localCameraPosition = GlobalVars::client->pLocalPlayer->GetCameraPosition();

	float distance = GlobalVars::client->pLocalPlayer->CalcDistaceToEntity(pEntity);

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