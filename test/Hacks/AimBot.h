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
	ImVec3 CalcAimViewAngles(CBaseEntity* pEntity, int bone);
	ImVec3 ClampViewAngles(ImVec3 vecViewAngles);
	ImVec3 NormalizeViewAngles(ImVec3 vecViewAngle);
	void AimSmooth(CBaseEntity* pEnt, int iBoneId);
	void AimPlain(CBaseEntity* pEnt, int iBoneId);
	CBaseEntity* GetClosestTargetByDistance(int bone);
	CBaseEntity* GetClosestTargetByFov(int bone);
};