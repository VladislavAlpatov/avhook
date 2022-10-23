/*
 * Copyright (c) 2022.
 * Created by Alpatov Softworks with love in Russia.
 */


#pragma once
#include "hack.h"
#include "../SDK/CUserCMD.h"



namespace Hacks
{
	class CAimBot final : public CHackFeature
	{
	public:
		CAimBot(Settings::CAimBotSettings* settings, SSDK::CUserCmd* pUsrCmd);
		void Work() override;
		static int         GetBoneIDBySelectedTab(const int iTabIndex);
		static ImVec3                    CalcAimViewAngles(const SSDK::CBaseEntity* pEntity, const int bone);
		
		static ImVec3                    CalcAimViewAngles(const ImVec3& origin, const ImVec3& target);
	private:
		SSDK::CUserCmd* m_pCUsrCmd = nullptr;
		bool                      IfEntityInFov(const SSDK::CBaseEntity* pEntity, const int iBoneId) const;
		void                      AimSmooth(const SSDK::CBaseEntity* pEntity, int iBoneId) const;
		void                      AimPlain(const SSDK::CBaseEntity* pEntity, int iBoneId) const;
		SSDK::CBaseEntity*              GetClosestTargetByDistance(int bone) const;
		SSDK::CBaseEntity*              GetClosestTargetByFov(int bone) const;

		// Get All enemy entites that are Alive, In fov range and can be seen 
		std::vector<SSDK::CBaseEntity*> GetValidEntities(const int boneId) const;

		int						  GetBoneIdByEntityHealth(const SSDK::CBaseEntity* pEntity) const;
	};
}