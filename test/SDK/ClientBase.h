#pragma once
#include <Windows.h>

#include "../Utils/offsets.h"
#include "CBaseEntity.h"



class matrix4x4
{
public:
	float* operator[ ](int index)
	{
		return m_RawData[index];
	}

private:
	float m_RawData[4][4];
};
namespace SSDK
{
	class ClientBase
	{
	public:
		union
		{
			DEFINE_MEMBER_N(int, dwForceJump, signatures::dwForceJump);
			DEFINE_MEMBER_N(int, dwForceAttack, signatures::dwForceAttack);
			DEFINE_MEMBER_N(matrix4x4, dwViewmatrix, signatures::dwViewMatrix);
			DEFINE_MEMBER_N(CBaseEntity*, pLocalPlayer, signatures::dwLocalPlayer);
			DEFINE_MEMBER_N(DWORD, dwGlowObjectManager, signatures::dwGlowObjectManager);
		};
		// Make local player jump
		void SendJumpCode()
		{
			this->dwForceJump = 6;
		}
		// Make local player attack
		void SendAttackCode()
		{
			this->dwForceAttack = 6;
		}
		matrix4x4 GetViewMatrix();
		CBaseEntity* GetLocalPlayer();

	};
}