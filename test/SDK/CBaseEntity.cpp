#include "CBaseEntity.h"
#include <math.h>
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
	auto healthRatio = GetHealthPercent() / 100.f;

	if (healthRatio >= 0.5f)
		return ImColor(1.f - (healthRatio - 0.5f) * 2.f, 1.f, 0.f);

	return ImColor(1.f, healthRatio / 2.f,  0.f);
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
	return 100.f * m_iHealth / m_iMaxHealth;
}
