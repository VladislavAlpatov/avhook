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

float CBaseEntity::CalcDistanceToEntity(const CBaseEntity* entity) const
{
	return (m_vecOrigin + m_vecViewOffset).DistTo(entity->GetBonePosition(8));
}

ImColor CBaseEntity::GetColorBasedOnHealth() const
{
	const auto healthRatio = GetHealthPercent() / 100.f;

	if (healthRatio >= 0.5f)
		return { 1.f - (healthRatio - 0.5f) * 2.f, 1.f, 0.f };
	return {1.f, healthRatio * 2.f, 0.f};
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

const ClientClass* SSDK::CBaseEntity::GetClientClass() const
{
	typedef ClientClass* (__cdecl* GetClientClass_t)();

	// Get addr of fucntion with index  2 from vtable with index 2
	auto funcAdrr = ((GetClientClass_t**)this)[2][2];
	return funcAdrr();
}
