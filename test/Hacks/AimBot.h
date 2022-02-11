#pragma once
#include "hack.h"
#include "../SDK/CUserCMD.h"
#include "../Utils/Marker.h"


class CAimBot : public CHackingFeature
{
public:
	CAimBot(AimBotSettings* settings, CUserCmd* pUsrCmd);
	virtual void Work();

private:
	CUserCmd*       m_pCUsrCmd;
	bool IfEntityInFov(CBaseEntity* ent, int bone);
	__forceinline int GetBoneIDBySelectedTab();
	ImVec3 CalcAimViewAngles(CBaseEntity* pEntity, int bone)
	{
		ImVec3 calculated;

		ImVec3 targetPosition = pEntity->GetBonePosition(bone);

		ImVec3 localCameraPosition = GlobalVars::client->pLocalPlayer->GetCameraPosition();

		float distance = GlobalVars::client->pLocalPlayer->CalcDistaceToEntity(pEntity);

		calculated.x = -asinf((targetPosition.z - localCameraPosition.z) / distance) * (180 / 3.1415926f);
		calculated.y = atan2f(targetPosition.y - localCameraPosition.y, targetPosition.x - localCameraPosition.x) * (180 / 3.1415926f);

		return calculated;
	}
	ImVec3 ClampViewAngles(ImVec3 vecViewAngles)
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
	ImVec3 NormalizeViewAngles(ImVec3 vecViewAngle)
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
	void AimSmooth(CBaseEntity* pEnt, int iBoneId);
	void AimPlain(CBaseEntity* pEnt, int iBoneId);
	CBaseEntity* GetClosestTargetByDistance(int bone);
	CBaseEntity* GetClosestTargetByFov(int bone);
};