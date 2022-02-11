#pragma once
#include "CBaseEntity.h"
#include "../Utils/GetInterface.h"
#include "IClientEntityList.h"
#include "CUserCMD.h"

class CLocalPlayer : public CBaseEntity
{
public:
	ImVec3* GetViewAngles();
	// Aim on target entity
	void AimAt(CBaseEntity* entity, CUserCmd* cmd,int bone, float speed = 999999.0f, bool prediction = false, bool silent = false);
	// Return angles to target
	ImVec3 GetAimTargetAngles(CBaseEntity* entity, int bone);
private:

};
