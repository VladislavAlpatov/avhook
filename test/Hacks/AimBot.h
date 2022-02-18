#pragma once
#include "hack.h"
#include "../SDK/CUserCMD.h"
#include "../Utils/Marker.h"

namespace Hacks
{
	class CAimBot : public CHackingFeature
	{
	public:
		CAimBot(AimBotSettings* settings, CUserCmd* pUsrCmd);
		virtual void Work();

	private:
		CUserCmd* m_pCUsrCmd;
		bool IfEntityInFov(const CBaseEntity* ent, const int bone) const;
		__forceinline int GetBoneIDBySelectedTab();
		ImVec3 CalcAimViewAngles(const CBaseEntity* pEntity, int bone) const;
		static ImVec3 ClampViewAngles(ImVec3 vecViewAngles);
		static ImVec3 NormalizeViewAngles(ImVec3 vecViewAngle);
		void AimSmooth(CBaseEntity* pEnt, int iBoneId);
		void AimPlain(CBaseEntity* pEnt, int iBoneId);
		CBaseEntity* GetClosestTargetByDistance(int bone);
		CBaseEntity* GetClosestTargetByFov(int bone);
		std::vector<CBaseEntity*> GetValidEntities(const int boneId) const;
	};
}