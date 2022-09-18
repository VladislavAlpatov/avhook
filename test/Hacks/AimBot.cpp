
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

	const auto pAimBotSettings = (Settings::CAimBotSettings*)m_pSettings;
	const auto pLocalPlayer = SSDK::ClientBase::GetLocalPlayer();
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
				m_pCUsrCmd->m_vecViewAngles = Utils::NormalizeViewAngles(m_pCUsrCmd->m_vecViewAngles - pLocalPlayer->m_vecAimPuchAngle * 2.f);
		}
	}
	
	if (pAimBotSettings->m_bAutoShot)
		m_pCUsrCmd->m_iButtons &= 1;

	POLY_MARKER;
}
void CAimBot::AimPlain(const CBaseEntity* pEntity, const int iBoneId) const
{
	POLY_MARKER;

	if (const auto calculatedViewAngle = CalcAimViewAngles(pEntity, iBoneId); fabs(calculatedViewAngle.x) <= 89.f and fabs(calculatedViewAngle.y) <= 180.f)
	{
		m_pCUsrCmd->m_vecViewAngles = calculatedViewAngle;
	}
}
void CAimBot::AimSmooth(const CBaseEntity* pEntity, const int iBoneId) const
{
	using namespace GlobalVars;

	POLY_MARKER;

	const auto pAimBotSettings = (Settings::CAimBotSettings*)m_pSettings;

	const ImVec3 targetViewAngle = CalcAimViewAngles(pEntity, iBoneId);

	ImVec3 currentAngle = m_pCUsrCmd->m_vecViewAngles;

	const ImVec3 diff = Utils::ClampViewAngles(Utils::NormalizeViewAngles(targetViewAngle - currentAngle));


	currentAngle.x += diff.x / pAimBotSettings->m_fSmooth;
	currentAngle.y += diff.y / pAimBotSettings->m_fSmooth;

	POLY_MARKER;

	currentAngle = Utils::ClampViewAngles(Utils::NormalizeViewAngles(currentAngle));
	
	if (fabs(currentAngle.x) <= 89.f and fabs(currentAngle.y) <= 180.f)
	{
		m_pCUsrCmd->m_vecViewAngles = currentAngle;
	}
}
bool CAimBot::IfEntityInFov(const CBaseEntity* pEntity, const int iBoneId) const
{
	using namespace GlobalVars;
	const auto pAimBotSettings = (Settings::CAimBotSettings*)m_pSettings;

	POLY_MARKER;

	const ImVec3  pLocalPlayerAngles = m_pCUsrCmd->m_vecViewAngles;
	const ImVec3  targetAngles = CalcAimViewAngles(pEntity, iBoneId);
	ImVec3  deltaFov = (pLocalPlayerAngles - targetAngles);
	POLY_MARKER;

	return  pAimBotSettings->m_fFov >= deltaFov.Abs().Length2D();
}
CBaseEntity* CAimBot::GetClosestTargetByDistance(const int bone) const
{
	POLY_MARKER;
	std::vector<CBaseEntity*> validEntities = GetValidEntities(bone);
	
	if (validEntities.empty())
		return nullptr;
	POLY_MARKER;
	auto pLocalPlayer = SSDK::ClientBase::GetLocalPlayer();
	std::sort(validEntities.begin(), validEntities.end(),

		[pLocalPlayer](const CBaseEntity* first, const CBaseEntity* second)
		{
			return pLocalPlayer->CalcDistanceToEntity(first) < pLocalPlayer->CalcDistanceToEntity(second);
		});
	return validEntities[0];
}

CBaseEntity* CAimBot::GetClosestTargetByFov(int bone) const
{

	POLY_MARKER;
	std::vector<CBaseEntity*> validEntities = GetValidEntities(bone);


	if (validEntities.empty()) return nullptr;

	POLY_MARKER;

	std::sort(validEntities.begin(), validEntities.end(),

		[this, bone](const CBaseEntity* pEntityFirst, const CBaseEntity* pEntitySecond)
		{
			const ImVec3 diffFirstEntity = (CalcAimViewAngles(pEntityFirst,   bone) - m_pCUsrCmd->m_vecViewAngles).Abs();
			const ImVec3 diffSecondEntity = (CalcAimViewAngles(pEntitySecond, bone) - m_pCUsrCmd->m_vecViewAngles).Abs();

			return diffFirstEntity.Length2D() < diffSecondEntity.Length2D();
		});

	return validEntities[0];
}

ImVec3 CAimBot::CalcAimViewAngles(const CBaseEntity* pEntity, const int bone) 
{
	POLY_MARKER;
	const auto pLocalPlayer = SSDK::ClientBase::GetLocalPlayer();
	return CalcAimViewAngles(pLocalPlayer->GetCameraPosition(), pEntity->GetBonePosition(bone));
}

ImVec3 Hacks::CAimBot::CalcAimViewAngles(const ImVec3& origin, const ImVec3& target)
{

	ImVec3 out;
	const float distance = origin.DistTo(target);

	// Make x negative since -89 is top and 89 is bottom
	out.x = -Utils::RadToDeg(asinf((target.z - origin.z) / distance));
	out.y = Utils::RadToDeg(atan2f(target.y  - origin.y, target.x - origin.x));

	return out;
}

std::vector<CBaseEntity*> CAimBot::GetValidEntities(const int boneId) const
{
	std::vector<CBaseEntity*> validEntities;
	const auto localPlayer = SSDK::ClientBase::GetLocalPlayer();

	POLY_MARKER;

	for (int i = 1; i < 33; i++)
	{
		CBaseEntity* pEntity =GlobalVars::g_pIEntityList->GetClientEntity(i);

		if (!pEntity or !pEntity->m_IsVisible)
			continue;

		if (pEntity->IsAlive() and !pEntity->m_bDormant and localPlayer->m_iTeamNum != pEntity->m_iTeamNum and IfEntityInFov(pEntity, boneId) and pEntity->m_IsVisible)
			validEntities.push_back(pEntity);

	}
	return validEntities;

}

int Hacks::CAimBot::GetBoneIdByEntityHealth(const CBaseEntity* pEntity) const
{
	const auto pSettings = (Settings::CAimBotSettings*)m_pSettings;
	POLY_MARKER;
	if (pEntity->GetHealthPercent() > pSettings->m_iHealthBorder)
		return CBaseEntity::Bone::HEAD;
	
	return CBaseEntity::Bone::BODY;
}
