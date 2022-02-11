#include "CLocalPlayer.h"

void CLocalPlayer::AimAt(CBaseEntity* entity, CUserCmd* cmd, int bone, float speed, bool prediction, bool silent)
{

	ImVec3 targetpos = entity->GetBonePosition(bone);
	ImVec3 myPos = m_vecOrigin;

	myPos.z += m_vecViewOffset.z;
	


	ImVec3* angles = GetViewAngles();

	float distance = CalcDistaceToEntity(entity);

	if (prediction)
	{
		targetpos.x += entity->m_vecVelocity.x * (distance / speed);
		targetpos.y += entity->m_vecVelocity.y * (distance / speed);

		distance = sqrtf(powf(targetpos.x - myPos.x, 2) + powf(targetpos.y - myPos.y, 2) + powf(targetpos.z - myPos.z, 2));
	}
	ImVec3 calculatedViewAngles;
	calculatedViewAngles.x = -asinf( (targetpos.z - myPos.z) / distance) * (180 / 3.1415926f);
	calculatedViewAngles.y = atan2f(targetpos.y - myPos.y, targetpos.x - myPos.x) * (180 / 3.1415926f);


	if (fabsf(calculatedViewAngles.x) < 89.f and fabsf(calculatedViewAngles.y) < 180.f)
	{
		auto viewangles = GetViewAngles();
		*viewangles    = calculatedViewAngles;

	}
}
ImVec3 CLocalPlayer::GetAimTargetAngles(CBaseEntity* entity, int bone)
{
	ImVec3 calculated;

	ImVec3 targetpos                  = entity->GetBonePosition(bone);

	ImVec3 local_player_camera_pos = this->GetCameraPosition();

	float distance = this->CalcDistaceToEntity(entity);

	calculated.x   = -asinf((targetpos.z - local_player_camera_pos.z) / distance) * (180 / 3.1415926f);
	calculated.y   = atan2f(targetpos.y - local_player_camera_pos.y, targetpos.x - local_player_camera_pos.x) * (180 / 3.1415926f);

	return calculated;
}

ImVec3* CLocalPlayer::GetViewAngles()
{
	DWORD engineModule = reinterpret_cast<DWORD>(GetModuleHandle(xorstr("engine.dll")));
	return (ImVec3*)(*(DWORD*)(engineModule + signatures::dwClientState) + signatures::dwClientState_ViewAngles);
}
void LookAt(const ImVec3& targetPosition)
{

}