//========= Copyright Alpatov Softworks, All rights reserved. ============//
//
// Purpose: Provide automatic target aquesition system
//
//===============================================================================


#pragma once
#include "hack.h"
#include "../SDK/CUserCMD.h"



namespace Hacks
{
	class CAimBot final : public CHackingFeature
	{
	public:
		CAimBot(Settings::CAimBotSettings* settings, CUserCmd* pUsrCmd);
		void Work() override;
		static int         GetBoneIDBySelectedTab(const int iTabIndex);
		static ImVec3                    CalcAimViewAngles(const CBaseEntity* pEntity, const int bone);
		
		static ImVec3                    CalcAimViewAngles(const ImVec3& origin, const ImVec3& target);
	private:
		CUserCmd* m_pCUsrCmd = nullptr;
		bool                      IfEntityInFov(const CBaseEntity* pEntity, const int bone) const;
		void                      AimSmooth(const CBaseEntity* pEntity, int iBoneId);
		void                      AimPlain(const  CBaseEntity* pEntity, int iBoneId);
		CBaseEntity*              GetClosestTargetByDistance(int bone);
		CBaseEntity*              GetClosestTargetByFov(int bone);

		// Get All enemy entites that are Alive, In fov range and can be seen 
		std::vector<CBaseEntity*> GetValidEntities(const int boneId) const;

		int						  GetBoneIdByEntityHealth(const CBaseEntity* pEntity) const;
	};
}