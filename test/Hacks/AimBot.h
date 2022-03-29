#pragma once
#include "hack.h"
#include "../SDK/CUserCMD.h"
#include "../Utils/Marker.h"

namespace Hacks
{
	class CAimBot : public CHackingFeature
	{
	public:
		CAimBot(Settings::CAimBotSettings* settings, CUserCmd* pUsrCmd);
		virtual void Work();
		static int         GetBoneIDBySelectedTab(const int iTabIndex);
	private:
		CUserCmd* m_pCUsrCmd = nullptr;

		bool                      IfEntityInFov(const CBaseEntity* pEntity, const int bone) const;
		ImVec3                    CalcAimViewAngles(const CBaseEntity* pEntity, const int bone) const;
		static ImVec3             ClampViewAngles(ImVec3 vecViewAngles);
		static ImVec3             NormalizeViewAngles(ImVec3 vecViewAngle);
		void                      AimSmooth(const CBaseEntity* pEntity, int iBoneId);
		void                      AimPlain(const  CBaseEntity* pEntity, int iBoneId);
		CBaseEntity*              GetClosestTargetByDistance(int bone);
		CBaseEntity*              GetClosestTargetByFov(int bone);

		// Get All enemy entites that are Alive, In fov range and can be seen 
		std::vector<CBaseEntity*> GetValidEntities(const int boneId) const;

		int						  GetBoneIdByEntityHealth(const CBaseEntity* pEntity) const;
	};
}