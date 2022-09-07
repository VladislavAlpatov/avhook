#pragma once
#include "CBaseEntity.h"



class CMatrix4x4
{
public:
	float* operator[ ](const int iIndex)
	{
		return m_RawData[iIndex];
	}
	CMatrix4x4()
	{
		for (auto& column : m_RawData)
			for (auto& fVar : column)
				fVar = 0.f;
	}
	ImVec4 Multiply(const ImVec3& vec)
	{
		ImVec4 out;


	}

private:
	float m_RawData[4][4];
};
namespace SSDK
{

	namespace ClientBase
	{
		CMatrix4x4 GetViewMatrix();
		CBaseEntity* GetLocalPlayer();
	}
}