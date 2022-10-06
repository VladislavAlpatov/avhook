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

		enum CommandButtons : int
		{
			IN_ATTACK = (1 << 0),
			IN_JUMP = (1 << 1),
			IN_DUCK = (1 << 2),
			IN_FORWARD = (1 << 3),
			IN_BACK = (1 << 4),
			IN_USE = (1 << 5),
			IN_CANCEL = (1 << 6),
			IN_LEFT = (1 << 7),
			IN_RIGHT = (1 << 8),
			IN_MOVELEFT = (1 << 9),
			IN_MOVERIGHT = (1 << 10),
			IN_SECOND_ATTACK = (1 << 11),
			IN_RUN = (1 << 12),
			IN_RELOAD = (1 << 13),
			IN_LEFT_ALT = (1 << 14),
			IN_RIGHT_ALT = (1 << 15),
			IN_SCORE = (1 << 16),
			IN_SPEED = (1 << 17),
			IN_WALK = (1 << 18),
			IN_ZOOM = (1 << 19),
			IN_FIRST_WEAPON = (1 << 20),
			IN_SECOND_WEAPON = (1 << 21),
			IN_BULLRUSH = (1 << 22),
			IN_FIRST_GRENADE = (1 << 23),
			IN_SECOND_GRENADE = (1 << 24),
			IN_MIDDLE_ATTACK = (1 << 25)
		};
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