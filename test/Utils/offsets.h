#pragma once
#include <Windows.h>
#include "xorstr.h"


#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;}

#define WINDOW_NAME xorstr("Counter-Strike: Global Offensive - Direct3D 9")
#define VERSION  xorstr("0.0.10.0")



namespace netvars {
	const DWORD cs_gamerules_data = 0x0;
	const DWORD m_ArmorValue = 0x117CC;
	const DWORD m_Collision = 0x320;
	const DWORD m_CollisionGroup = 0x474;
	const DWORD m_Local = 0x2FCC;
	const DWORD m_MoveType = 0x25C;
	const DWORD m_OriginalOwnerXuidHigh = 0x31D4;
	const DWORD m_OriginalOwnerXuidLow = 0x31D0;
	const DWORD m_SurvivalGameRuleDecisionTypes = 0x1328;
	const DWORD m_SurvivalRules = 0xD00;
	const DWORD m_aimPunchAngle = 0x303C;
	const DWORD m_aimPunchAngleVel = 0x3048;
	const DWORD m_angEyeAnglesX = 0x117D0;
	const DWORD m_angEyeAnglesY = 0x117D4;
	const DWORD m_bBombDefused = 0x29C0;
	const DWORD m_bBombPlanted = 0x9A5;
	const DWORD m_bBombTicking = 0x2990;
	const DWORD m_bFreezePeriod = 0x20;
	const DWORD m_bGunGameImmunity = 0x9990;
	const DWORD m_bHasDefuser = 0x117DC;
	const DWORD m_bHasHelmet = 0x117C0;
	const DWORD m_bInReload = 0x32B5;
	const DWORD m_bIsDefusing = 0x997C;
	const DWORD m_bIsQueuedMatchmaking = 0x74;
	const DWORD m_bIsScoped = 0x9974;
	const DWORD m_bIsValveDS = 0x7C;
	const DWORD m_bSpotted = 0x93D;
	const DWORD m_bSpottedByMask = 0x980;
	const DWORD m_bStartedArming = 0x3400;
	const DWORD m_bUseCustomAutoExposureMax = 0x9D9;
	const DWORD m_bUseCustomAutoExposureMin = 0x9D8;
	const DWORD m_bUseCustomBloomScale = 0x9DA;
	const DWORD m_clrRender = 0x70;
	const DWORD m_dwBoneMatrix = 0x26A8;
	const DWORD m_fAccuracyPenalty = 0x3340;
	const DWORD m_fFlags = 0x104;
	const DWORD m_flC4Blow = 0x29A0;
	const DWORD m_flCustomAutoExposureMax = 0x9E0;
	const DWORD m_flCustomAutoExposureMin = 0x9DC;
	const DWORD m_flCustomBloomScale = 0x9E4;
	const DWORD m_flDefuseCountDown = 0x29BC;
	const DWORD m_flDefuseLength = 0x29B8;
	const DWORD m_flFallbackWear = 0x31E0;
	const DWORD m_flFlashDuration = 0x10470;
	const DWORD m_flFlashMaxAlpha = 0x1046C;
	const DWORD m_flLastBoneSetupTime = 0x2928;
	const DWORD m_flLowerBodyYawTarget = 0x9ADC;
	const DWORD m_flNextAttack = 0x2D80;
	const DWORD m_flNextPrimaryAttack = 0x3248;
	const DWORD m_flSimulationTime = 0x268;
	const DWORD m_flTimerLength = 0x29A4;
	const DWORD m_hActiveWeapon = 0x2F08;
	const DWORD m_hBombDefuser = 0x29C4;
	const DWORD m_hMyWeapons = 0x2E08;
	const DWORD m_hObserverTarget = 0x339C;
	const DWORD m_hOwner = 0x29DC;
	const DWORD m_hOwnerEntity = 0x14C;
	const DWORD m_hViewModel = 0x3308;
	const DWORD m_iAccountID = 0x2FD8;
	const DWORD m_iClip1 = 0x3274;
	const DWORD m_iCompetitiveRanking = 0x1A84;
	const DWORD m_iCompetitiveWins = 0x1B88;
	const DWORD m_iCrosshairId = 0x11838;
	const DWORD m_iDefaultFOV = 0x333C;
	const DWORD m_iEntityQuality = 0x2FBC;
	const DWORD m_iFOV = 0x31F4;
	const DWORD m_iFOVStart = 0x31F8;
	const DWORD m_iGlowIndex = 0x10488;
	const DWORD m_iHealth = 0x100;
	const DWORD m_iItemDefinitionIndex = 0x2FBA;
	const DWORD m_iItemIDHigh = 0x2FD0;
	const DWORD m_iMostRecentModelBoneCounter = 0x2690;
	const DWORD m_iObserverMode = 0x3388;
	const DWORD m_iShotsFired = 0x103E0;
	const DWORD m_iState = 0x3268;
	const DWORD m_iTeamNum = 0xF4;
	const DWORD m_lifeState = 0x25F;
	const DWORD m_nBombSite = 0x2994;
	const DWORD m_nFallbackPaintKit = 0x31D8;
	const DWORD m_nFallbackSeed = 0x31DC;
	const DWORD m_nFallbackStatTrak = 0x31E4;
	const DWORD m_nForceBone = 0x268C;
	const DWORD m_nTickBase = 0x3440;
	const DWORD m_nViewModelIndex = 0x29D0;
	const DWORD m_rgflCoordinateFrame = 0x444;
	const DWORD m_szCustomName = 0x304C;
	const DWORD m_szLastPlaceName = 0x35C4;
	const DWORD m_thirdPersonViewAngles = 0x31E8;
	const DWORD m_vecOrigin = 0x138;
	const DWORD m_vecVelocity = 0x114;
	const DWORD m_vecViewOffset = 0x108;
	const DWORD m_viewPunchAngle = 0x3030;
	const DWORD m_zoomLevel = 0x33E0;
} // namespace netvars
namespace signatures {
	const DWORD anim_overlays = 0x2990;
	const DWORD clientstate_choked_commands = 0x4D30;
	const DWORD clientstate_delta_ticks = 0x174;
	const DWORD clientstate_last_outgoing_command = 0x4D2C;
	const DWORD clientstate_net_channel = 0x9C;
	const DWORD convar_name_hash_table = 0x2F0F8;
	const DWORD dwClientState = 0x58BFC4;
	const DWORD dwClientState_GetLocalPlayer = 0x180;
	const DWORD dwClientState_IsHLTV = 0x4D48;
	const DWORD dwClientState_Map = 0x28C;
	const DWORD dwClientState_MapDirectory = 0x188;
	const DWORD dwClientState_MaxPlayer = 0x388;
	const DWORD dwClientState_PlayerInfo = 0x52C0;
	const DWORD dwClientState_State = 0x108;
	const DWORD dwClientState_ViewAngles = 0x4D90;
	const DWORD dwEntityList = 0x4DD0E6C;
	const DWORD dwForceAttack = 0x3201380;
	const DWORD dwForceAttack2 = 0x320138C;
	const DWORD dwForceBackward = 0x320132C;
	const DWORD dwForceForward = 0x32013B0;
	const DWORD dwForceJump = 0x527AD90;
	const DWORD dwForceLeft = 0x3201338;
	const DWORD dwForceRight = 0x3201344;
	const DWORD dwGameDir = 0x62A880;
	const DWORD dwGameRulesProxy = 0x52EDDEC;
	const DWORD dwGetAllClasses = 0xDDF17C;
	const DWORD dwGlobalVars = 0x58BCC8;
	const DWORD dwGlowObjectManager = 0x5319260;
	const DWORD dwInput = 0x5222440;
	const DWORD dwInterfaceLinkList = 0x967FB4;
	const DWORD dwLocalPlayer = 0xDB55DC;
	const DWORD dwMouseEnable = 0xDBB2E8;
	const DWORD dwMouseEnablePtr = 0xDBB2B8;
	const DWORD dwPlayerResource = 0x31FF6D0;
	const DWORD dwRadarBase = 0x5205BE4;
	const DWORD dwSensitivity = 0xDBB184;
	const DWORD dwSensitivityPtr = 0xDBB158;
	const DWORD dwSetClanTag = 0x8A340;
	const DWORD dwViewMatrix = 0x4DC2784;
	const DWORD dwWeaponTable = 0x5222F08;
	const DWORD dwWeaponTableIndex = 0x326C;
	const DWORD dwYawPtr = 0xDBAF48;
	const DWORD dwZoomSensitivityRatioPtr = 0xDC1158;
	const DWORD dwbSendPackets = 0xD94C2;
	const DWORD dwppDirect3DDevice9 = 0xA5050;
	const DWORD find_hud_element = 0x279349F0;
	const DWORD force_update_spectator_glow = 0x3BB05A;
	const DWORD interface_engine_cvar = 0x3E9EC;
	const DWORD is_c4_owner = 0x3C8110;
	const DWORD m_bDormant = 0xED;
	const DWORD m_flSpawnTime = 0x103C0;
	const DWORD m_pStudioHdr = 0x2950;
	const DWORD m_pitchClassPtr = 0x5205E80;
	const DWORD m_yawClassPtr = 0xDBAF48;
	const DWORD model_ambient_min = 0x58F03C;
	const DWORD set_abs_angles = 0x1E5330;
	const DWORD set_abs_origin = 0x1E5170;
} // namespace signatures