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

	namespace ClientBase
	{
		matrix4x4 GetViewMatrix();
		CBaseEntity* GetLocalPlayer();
	}
}