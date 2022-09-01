
//========= Copyright Alpatov Softworks, All rights reserved. ============//
//
// Emulate CSGO C_BaseEntity class.
//
//===============================================================================



#pragma once
#include "../Utils/offsets.h"
#include "../Utils/Vec3.h"
#include "../imgui/imgui.h"

namespace SSDK
{
	enum class ClassIndex : int
	{
		CAI_BaseNPC = 0,
		CAK47,
		CBaseAnimating,
		CBaseAnimatingOverlay,
		CBaseAttributableItem,
		CBaseButton,
		CBaseCombatCharacter,
		CBaseCombatWeapon,
		CBaseCSGrenade,
		CBaseCSGrenadeProjectile,
		CBaseDoor,
		CBaseEntity,
		CBaseFlex,
		CBaseGrenade,
		CBaseParticleEntity,
		CBasePlayer,
		CBasePropDoor,
		CBaseTeamObjectiveResource,
		CBaseTempEntity,
		CBaseToggle,
		CBaseTrigger,
		CBaseViewModel,
		CBaseVPhysicsTrigger,
		CBaseWeaponWorldModel,
		CBeam,
		CBeamSpotlight,
		CBoneFollower,
		CBRC4Target,
		CBreachCharge,
		CBreachChargeProjectile,
		CBreakableProp,
		CBreakableSurface,
		CBumpMine,
		CBumpMineProjectile,
		CC4,
		CCascadeLight,
		CChicken,
		CColorCorrection,
		CColorCorrectionVolume,
		CCSGameRulesProxy,
		CCSPlayer,
		CCSPlayerResource,
		CCSRagdoll,
		CCSTeam,
		CDangerZone,
		CDangerZoneController,
		CDEagle,
		CDecoyGrenade,
		CDecoyProjectile,
		CDrone,
		CDronegun,
		CDynamicLight,
		CDynamicProp,
		CEconEntity,
		CEconWearable,
		CEmbers,
		CEntityDissolve,
		CEntityFlame,
		CEntityFreezing,
		CEntityParticleTrail,
		CEnvAmbientLight,
		CEnvDetailController,
		CEnvDOFController,
		CEnvGasCanister,
		CEnvParticleScript,
		CEnvProjectedTexture,
		CEnvQuadraticBeam,
		CEnvScreenEffect,
		CEnvScreenOverlay,
		CEnvTonemapController,
		CEnvWind,
		CFEPlayerDecal,
		CFireCrackerBlast,
		CFireSmoke,
		CFireTrail,
		CFish,
		CFists,
		CFlashbang,
		CFogController,
		CFootstepControl,
		CFunc_Dust,
		CFunc_LOD,
		CFuncAreaPortalWindow,
		CFuncBrush,
		CFuncConveyor,
		CFuncLadder,
		CFuncMonitor,
		CFuncMoveLinear,
		CFuncOccluder,
		CFuncReflectiveGlass,
		CFuncRotating,
		CFuncSmokeVolume,
		CFuncTrackTrain,
		CGameRulesProxy,
		CGrassBurn,
		CHandleTest,
		CHEGrenade,
		CHostage,
		CHostageCarriableProp,
		CIncendiaryGrenade,
		CInferno,
		CInfoLadderDismount,
		CInfoMapRegion,
		CInfoOverlayAccessor,
		CItem_Healthshot,
		CItemCash,
		CItemDogtags,
		CKnife,
		CKnifeGG,
		CLightGlow,
		CMapVetoPickController,
		CMaterialModifyControl,
		CMelee,
		CMolotovGrenade,
		CMolotovProjectile,
		CMovieDisplay,
		CParadropChopper,
		CParticleFire,
		CParticlePerformanceMonitor,
		CParticleSystem,
		CPhysBox,
		CPhysBoxMultiplayer,
		CPhysicsProp,
		CPhysicsPropMultiplayer,
		CPhysMagnet,
		CPhysPropAmmoBox,
		CPhysPropLootCrate,
		CPhysPropRadarJammer,
		CPhysPropWeaponUpgrade,
		CPlantedC4,
		CPlasma,
		CPlayerPing,
		CPlayerResource,
		CPointCamera,
		CPointCommentaryNode,
		CPointWorldText,
		CPoseController,
		CPostProcessController,
		CPrecipitation,
		CPrecipitationBlocker,
		CPredictedViewModel,
		CProp_Hallucination,
		CPropCounter,
		CPropDoorRotating,
		CPropJeep,
		CPropVehicleDriveable,
		CRagdollManager,
		CRagdollProp,
		CRagdollPropAttached,
		CRopeKeyframe,
		CSCAR17,
		CSceneEntity,
		CSensorGrenade,
		CSensorGrenadeProjectile,
		CShadowControl,
		CSlideshowDisplay,
		CSmokeGrenade,
		CSmokeGrenadeProjectile,
		CSmokeStack,
		CSnowball,
		CSnowballPile,
		CSnowballProjectile,
		CSpatialEntity,
		CSpotlightEnd,
		CSprite,
		CSpriteOriented,
		CSpriteTrail,
		CStatueProp,
		CSteamJet,
		CSun,
		CSunlightShadowControl,
		CSurvivalSpawnChopper,
		CTablet,
		CTeam,
		CTeamplayRoundBasedRulesProxy,
		CTEArmorRicochet,
		CTEBaseBeam,
		CTEBeamEntPoint,
		CTEBeamEnts,
		CTEBeamFollow,
		CTEBeamLaser,
		CTEBeamPoints,
		CTEBeamRing,
		CTEBeamRingPoint,
		CTEBeamSpline,
		CTEBloodSprite,
		CTEBloodStream,
		CTEBreakModel,
		CTEBSPDecal,
		CTEBubbles,
		CTEBubbleTrail,
		CTEClientProjectile,
		CTEDecal,
		CTEDust,
		CTEDynamicLight,
		CTEEffectDispatch,
		CTEEnergySplash,
		CTEExplosion,
		CTEFireBullets,
		CTEFizz,
		CTEFootprintDecal,
		CTEFoundryHelpers,
		CTEGaussExplosion,
		CTEGlowSprite,
		CTEImpact,
		CTEKillPlayerAttachments,
		CTELargeFunnel,
		CTEMetalSparks,
		CTEMuzzleFlash,
		CTEParticleSystem,
		CTEPhysicsProp,
		CTEPlantBomb,
		CTEPlayerAnimEvent,
		CTEPlayerDecal,
		CTEProjectedDecal,
		CTERadioIcon,
		CTEShatterSurface,
		CTEShowLine,
		CTesla,
		CTESmoke,
		CTESparks,
		CTESprite,
		CTESpriteSpray,
		CTest_ProxyToggle_Networkable,
		CTestTraceline,
		CTEWorldDecal,
		CTriggerPlayerMovement,
		CTriggerSoundOperator,
		CVGuiScreen,
		CVoteController,
		CWaterBullet,
		CWaterLODControl,
		CWeaponAug,
		CWeaponAWP,
		CWeaponBaseItem,
		CWeaponBizon,
		CWeaponCSBase,
		CWeaponCSBaseGun,
		CWeaponCycler,
		CWeaponElite,
		CWeaponFamas,
		CWeaponFiveSeven,
		CWeaponG3SG1,
		CWeaponGalil,
		CWeaponGalilAR,
		CWeaponGlock,
		CWeaponHKP2000,
		CWeaponM249,
		CWeaponM3,
		CWeaponM4A1,
		CWeaponMAC10,
		CWeaponMag7,
		CWeaponMP5Navy,
		CWeaponMP7,
		CWeaponMP9,
		CWeaponNegev,
		CWeaponNOVA,
		CWeaponP228,
		CWeaponP250,
		CWeaponP90,
		CWeaponSawedoff,
		CWeaponSCAR20,
		CWeaponScout,
		CWeaponSG550,
		CWeaponSG552,
		CWeaponSG556,
		CWeaponShield,
		CWeaponSSG08,
		CWeaponTaser,
		CWeaponTec9,
		CWeaponTMP,
		CWeaponUMP45,
		CWeaponUSP,
		CWeaponXM1014,
		CWeaponZoneRepulsor,
		CWorld,
		CWorldVguiText,
		DustTrail,
		MovieExplosion,
		ParticleSmokeGrenade,
		RocketTrail,
		SmokeTrail,
		SporeExplosion,
		SporeTrail,
	};
	class ClientClass
	{
	public:
		union
		{
			DEFINE_MEMBER_N(char*, m_NetworkName, 0x14);
			DEFINE_MEMBER_N(ClassIndex, m_iClassId, 0x14);
		};
	};


	class CBaseEntity
	{
	public:

		union
		{
			DEFINE_MEMBER_N(int,    m_iTeamNum, netvars::m_iTeamNum);
			DEFINE_MEMBER_N(int,    m_iHealth, netvars::m_iHealth);
			DEFINE_MEMBER_N(int,    m_iTeamNum, netvars::m_iTeamNum);
			DEFINE_MEMBER_N(int,    m_fFlags, netvars::m_fFlags);
			DEFINE_MEMBER_N(int,    m_Index, 0x64);
			DEFINE_MEMBER_N(bool,   m_IsVisible, 0x154);
			DEFINE_MEMBER_N(int,    m_iDefaultFOV, netvars::m_iDefaultFOV);
			DEFINE_MEMBER_N(int,    m_iGlowIndex, netvars::m_iGlowIndex);
			DEFINE_MEMBER_N(int,    m_ArmorValue, netvars::m_ArmorValue);
			DEFINE_MEMBER_N(bool,   m_bSpotted, netvars::m_bSpotted);
			DEFINE_MEMBER_N(int,    m_iCrosshairId, netvars::m_iCrosshairId);
			DEFINE_MEMBER_N(int,    m_iMaxHealth, 0x3640);
			DEFINE_MEMBER_N(ImVec3, m_vecViewOffset, netvars::m_vecViewOffset);
			DEFINE_MEMBER_N(ImVec3, m_vecOrigin, netvars::m_vecOrigin);
			DEFINE_MEMBER_N(DWORD,  m_pBoneMatrix, netvars::m_dwBoneMatrix);
			DEFINE_MEMBER_N(ImVec3, m_vecVelocity, netvars::m_vecVelocity);
			DEFINE_MEMBER_N(ImVec3, m_vecViewAngles, 0x12C);
			DEFINE_MEMBER_N(bool,   m_bDormant, signatures::m_bDormant);
			DEFINE_MEMBER_N(ImVec3, m_vecAimPuchAngle, netvars::m_aimPunchAngle);

		};
		// Get position of bone like head, pelvis and etc...
		ImVec3 GetBonePosition(const int bone) const;
		// Calc distance to entity
		float CalcDistaceToEntity(const CBaseEntity* entity) const;
		//Get color based on entity health
		ImColor GetColorBasedOnHealth() const;
		// Get entity camera position
		ImVec3 GetCameraPosition() const;
		// Is player alive?
		bool IsAlive() const ;
		float GetHealthPercent() const;
		const ClientClass* GetClientClass() const;

		enum Bone
		{
			HEAD = 8,
			BODY = 6,
			LEGS = 0,
		};
		enum Team : int
		{
			CT = 3,
			T = 4
		};
		enum FLAGS
		{
			ON_GROUND = 257,
			ON_GROUND_DUCK = 263,
			IN_WATER = 1287,
			IN_WATER_DUCK = 1281,
			IN_AIR = 256,
			IN_AIR_DUCK = 262
		};
	};

}