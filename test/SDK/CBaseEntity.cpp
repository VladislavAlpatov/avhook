#include "CBaseEntity.h"
ImVec3 CBaseEntity::GetBonePosition(int bone)
{
	DWORD  pBone = this->boneMatrix;
	ImVec3 position;

	position.x = *reinterpret_cast<float*>((pBone + 0x30 * bone + 0x0C));
	position.y = *reinterpret_cast<float*>((pBone + 0x30 * bone + 0x1C));
	position.z = *reinterpret_cast<float*>((pBone + 0x30 * bone + 0x2C));

	return position;
}

float CBaseEntity::CalcDistaceToEntity(CBaseEntity* entity)
{

	return (m_vecOrigin + m_vecViewOffset).DistTo(entity->GetBonePosition(8));
}

ImColor CBaseEntity::GetColorBasedOnHealth()
{
	if (20 >= m_iHealth)
		return ImColor(255, 0, 0);

	else if (60 >= m_iHealth)
		return ImColor(255, 255, 0);

	else if (m_iHealth >= 60)
		return ImColor(0, 255, 0);

	return ImColor(221, 0, 255);
}

ImVec3 CBaseEntity::GetCameraPosition()
{
	return m_vecOrigin + m_vecViewOffset;
}
bool   CBaseEntity::IsAlive()
{
	if (m_iHealth > 0)
			return true;
	return false;
}