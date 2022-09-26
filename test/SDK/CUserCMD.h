#pragma once
#include "../Utils/Vec3.h"

namespace SSDK
{
	class CUserCmd
	{
	public:

		int    pad;
		int     command_number;
		int     m_iTickCount;
		ImVec3  m_vecViewAngles;
		ImVec3  m_vecAimDirection;
		float   m_fForwardMove;
		float   m_fSideMove;
		float   m_fUpMove;
		int     m_iButtons;
		char    m_Impulse;
		int     m_iWeaponSelect;
		int     m_iWeaponType;
		int     m_iRandomSeed;
		__int16 m_i16Mousedx;
		__int16 m_i16MouseDy;
		bool    m_bHasBeenPredicted;
	};


	
	class  fix_usercmd
	{
	/// <summary>
	/// Fix movement for overrided CUserCmd
	/// </summary>
	public:
		fix_usercmd(CUserCmd* pUserCmd);
		~fix_usercmd();


	private:
		CUserCmd* m_pUserCmd{};
		CUserCmd  m_oldUserCmd;

	};
}