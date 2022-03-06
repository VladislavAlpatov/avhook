#include "CBaseEntity.h"
using namespace SSDK;

ImVec3 CBaseEntity::GetBonePosition(const int bone) const
{
	DWORD  pBone = m_pBoneMatrix;
	ImVec3 position;

	position.x = *(float*)((pBone + 0x30 * bone + 0x0C));
	position.y = *(float*)((pBone + 0x30 * bone + 0x1C));
	position.z = *(float*)((pBone + 0x30 * bone + 0x2C));

	return position;
}

float CBaseEntity::CalcDistaceToEntity(const CBaseEntity* entity) const
{
	return (m_vecOrigin + m_vecViewOffset).DistTo(entity->GetBonePosition(8));
}

ImColor CBaseEntity::GetColorBasedOnHealth() const
{

	if (20 >= m_iHealth)
		return ImColor(255, 0, 0);

	else if (60 >= m_iHealth)
		return ImColor(255, 255, 0);

	else if (m_iHealth >= 60)
		return ImColor(0, 255, 0);

	return ImColor(221, 0, 255);
}

ImVec3 CBaseEntity::GetCameraPosition() const
{
	return m_vecOrigin + m_vecViewOffset;
}
bool CBaseEntity::IsAlive() const
{
	return m_iHealth > 0;
}

float SSDK::CBaseEntity::GetHealthPercent() const
{
	return m_iHealth;
}
