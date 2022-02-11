#pragma once
#include <Windows.h>

#include "../Utils/offsets.h"
#include "../Utils/Vec3.h"
#include "../imgui/imgui.h"


class CBaseEntity
{
public:

	union 
	{
		DEFINE_MEMBER_N(int, m_iTeamNum, netvars::m_iTeamNum);
		DEFINE_MEMBER_N(int, m_iHealth, netvars::m_iHealth);
		DEFINE_MEMBER_N(int, m_iTeamNum, netvars::m_iTeamNum);
		DEFINE_MEMBER_N(int, m_fFlags, netvars::m_fFlags);
		DEFINE_MEMBER_N(int, m_Index, 0x64);
		DEFINE_MEMBER_N(bool, m_IsVisible, 0x154);
		DEFINE_MEMBER_N(int, m_iDefaultFOV, netvars::m_iDefaultFOV);
		DEFINE_MEMBER_N(int, m_iGlowIndex, netvars::m_iGlowIndex);
		DEFINE_MEMBER_N(int, m_ArmorValue, netvars::m_ArmorValue);
		DEFINE_MEMBER_N(int, m_iCrosshairId, netvars::m_iCrosshairId);
		DEFINE_MEMBER_N(ImVec3, m_vecViewOffset, netvars::m_vecViewOffset);
		DEFINE_MEMBER_N(ImVec3, m_vecOrigin, netvars::m_vecOrigin);
		DEFINE_MEMBER_N(DWORD, boneMatrix, netvars::m_dwBoneMatrix);
		DEFINE_MEMBER_N(ImVec3, m_vecVelocity, netvars::m_vecVelocity);
		DEFINE_MEMBER_N(bool, m_bDormant, signatures::m_bDormant);

	};
	// Get position of bone like head, pelvis and etc...
	ImVec3 GetBonePosition(int bone);
	// Calc distance to entity
	float CalcDistaceToEntity(CBaseEntity* entity);
	//Get color based on entity health
	ImColor GetColorBasedOnHealth();
	// Get entity camera position
	ImVec3 GetCameraPosition();
	// Is player alive?
	bool IsAlive();

    enum Bone
	{
		HEAD = 8,
		BODY = 6,
		LEGS = 0,
	};
	enum Team : int
	{
		CT = 3,
		T = 4
	};
	enum FLAGS
	{
		ON_GROUND      = 257,
		ON_GROUND_DUCK = 263,
		IN_WATER       = 1287,
		IN_WATER_DUCK  = 1281,
		IN_AIR = 256,
		IN_AIR_DUCK = 262
	};
};