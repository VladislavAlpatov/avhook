#pragma once
#include "../Utils/Vec3.h"
namespace SSDK
{
	class CUserCmd
	{
	public:

		int pad;
		int command_number;
		int tick_count;
		ImVec3 viewangles;
		ImVec3 aimdirection;
		float forwardmove;
		float sidemove;
		float upmove;
		int buttons;
		char impulse;
		int weaponselect;
		int weaponsubtype;
		int randomseed;
		__int16 mousedx;
		__int16 mousedy;
		bool hasbeenpredicted;
	};
}