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
		static ImVec3                    CalcAimViewAngles(const SSDK::CBaseEntity* pEntity, const int bone);
		
		static ImVec3                    CalcAimViewAngles(const ImVec3& origin, const ImVec3& target);
		bool						     IsEntityVisible(const SSDK::CBaseEntity* pEntity) const;
	private:
		SSDK::CUserCmd* m_pCUsrCmd = nullptr;

		bool                      		IfEntityInFov(const SSDK::CBaseEntity* pEntity) const;
		void                      		AimSmooth(const SSDK::CBaseEntity* pEntity) const;
		void                      		AimPlain(const SSDK::CBaseEntity* pEntity) const;

		SSDK::CBaseEntity*              GetClosestTargetByDistance() const;
		SSDK::CBaseEntity*              GetClosestTargetByFov() const;

		// Get All enemy entites that are Alive, In fov range and can be seen 
		std::vector<SSDK::CBaseEntity*> GetValidEntities() const;

		int						  GetBoneIdByEntityHealth(const SSDK::CBaseEntity* pEntity) const;
	};
}