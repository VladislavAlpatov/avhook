//========= Copyright Alpatov Softworks, All rights reserved. ============//
//
// Sets hooks to game functions
//
//===============================================================================


#include "Hooks.h"

#include "../../Utils/Marker.h"

#include "../../Hacks/AimBot.h"
#include "../../Hacks/TriggerBot.h"
#include "../../Hacks/bhop.h"
#include "../../Hacks/Esp/CGlowEsp.h"

#include "../../SDK/Finder.h"
#include "../../SDK/ClientBase.h"
#include "../../Globals/Interfaces.h"
#include "../../Globals/DirectX9.h"
#include "../../Globals/Settings.h"

#include <array>
#include "../../Menu/COverlay.h"
#include "MinHook.h"
#include "../../Utils/memory.h"

static uintptr_t		  oPresent;
static uintptr_t		  oDrawIndexedPrimitive;
static uintptr_t	      oWndProc;
static uintptr_t	      oCreateMove;
static uintptr_t		  oRenderGlowEffects;

static std::unique_ptr<UI::COverlay> pOverlay;
static std::map<PVOID, memory::CFunctionHook> mapWithHooks;

int __stdcall hooks::hDrawIndexedPrimitive(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE type, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount)
{
	POLY_MARKER;
	typedef bool(__stdcall* tDrawIndexedPrimitive)(LPDIRECT3DDEVICE9, D3DPRIMITIVETYPE, INT, UINT, UINT, UINT, UINT);
	for (const auto& texture : GlobalVars::g_AllSettings.m_TextureOverrideSettings.m_overridedTextures)
	{
		if (NumVertices != texture.m_iUid)
			continue;


		pDevice->SetTexture(0, texture.m_pTexture);
		if (texture.m_bEnableZ)
		{
			pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
			const auto res = reinterpret_cast<tDrawIndexedPrimitive>(oDrawIndexedPrimitive)(pDevice, type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
			pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
			return res;
		}
		break;
	}
	return reinterpret_cast<tDrawIndexedPrimitive>(oDrawIndexedPrimitive)(pDevice, type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
}

int __stdcall  hooks::hkPresent(LPDIRECT3DDEVICE9 pDevice, int a2, int a3, int a4, int a5)
{
	POLY_MARKER;

	if (!pOverlay)
	{
		pOverlay = std::make_unique<UI::COverlay>(pDevice);
		GlobalVars::pDevice = pDevice;
	}

	if (GetAsyncKeyState(VK_INSERT) & 1)
		pOverlay->ToggleUI();
	pOverlay->Render();		

	typedef int(__stdcall* Present)(LPDIRECT3DDEVICE9, int, int, int, int);
	return reinterpret_cast<Present>(oPresent)(pDevice, a2, a3, a4, a5);
}

bool __stdcall hooks::hCreateMove(const int fSampleTime, SSDK::CUserCmd* pUserCmd)
{
	typedef bool(__stdcall* tCreateMove)(int, SSDK::CUserCmd*);
	POLY_MARKER;
	const auto pLocalPlayer = SSDK::ClientBase::GetLocalPlayer();

	// DON'T REMOVE THIS IF STATEMENT ITS FIX, IT FIX A BUG WHEN YOU CANT PEEK A TEAM
	if (!pLocalPlayer || !pOverlay || pLocalPlayer->m_Index > 33 || !reinterpret_cast<tCreateMove>(oCreateMove)(fSampleTime, pUserCmd))
		return false;

	POLY_MARKER;
	
	pLocalPlayer->m_iDefaultFOV = GlobalVars::g_AllSettings.m_MiscSettings.m_iCustomFov;


	static SSDK::ConVar* pCrosshair = GlobalVars::g_pCvarManager->FindVar(xorstr("crosshair"));
	pCrosshair->m_pParentCvar->SetValue(GlobalVars::g_AllSettings.m_CrosshairSettings.m_Color.Value.w == 0.f || !GlobalVars::g_AllSettings.m_CrosshairSettings.m_bActive);

	// Looking for "visible" players
	for (const auto pEnt : GlobalVars::g_pIEntityList->GetEntityList())
	{

		if (pEnt->m_iTeamNum == pLocalPlayer->m_iTeamNum || !pEnt->IsAlive())
			continue;

		SSDK::CGameTrace   trace;
		SSDK::Ray_t        ray;
		SSDK::CTraceFilter tracefilter;
		tracefilter.m_pSkip = static_cast<void*>(pLocalPlayer);

		ray.Init(pLocalPlayer->m_vecOrigin + pLocalPlayer->m_vecViewOffset, pEnt->GetBonePosition(Hacks::CAimBot::GetBoneIDBySelectedTab(GlobalVars::g_AllSettings.m_AimBotSettings.m_iSelectedHitBox)));

		GlobalVars::g_pIEngineTrace->TraceRay(ray, MASK_SHOT | CONTENTS_GRATE, &tracefilter, &trace);

		pEnt->m_IsVisible = trace.m_pHitEntity == pEnt;
	}

	if (!pLocalPlayer->IsAlive())
		return false;

	const std::array<std::unique_ptr<Hacks::CHackFeature>, 3> features =
	{
		std::make_unique<Hacks::CBunnyHop>(pUserCmd, &GlobalVars::g_AllSettings.m_BunnyHopSettings),
		std::make_unique<Hacks::CAimBot>(&GlobalVars::g_AllSettings.m_AimBotSettings, pUserCmd),
		std::make_unique<Hacks::TriggerBot>(&GlobalVars::g_AllSettings.m_TriggerBotSettings, pUserCmd),
	};


	// ===Create Move Fix===
	// BUG: If silent aimbot is active it cause wrong movement for local player
	SSDK::fix_usercmd guard(pUserCmd);

	for (const auto& pFeature : features)
		pFeature->Work();

	return !GlobalVars::g_AllSettings.m_AimBotSettings.m_bSilent;
}

int __fastcall hooks::hRenderGlowEffects(SSDK::IGlowObjectManager* pThis, void* edx, int a2, int a3)
{
	typedef int(__fastcall* RenderGlowEffects_t)(void*, void*, int, int);


	POLY_MARKER;
	static auto glowEsp = Esp::CGlowEsp(&GlobalVars::g_AllSettings.m_GlowEspSettings);
	const auto pLocalPlayer   = SSDK::ClientBase::GetLocalPlayer();

	if (!glowEsp.isActive() || !pLocalPlayer || !GlobalVars::g_pIEngineClient->IsInGame())
		return reinterpret_cast<RenderGlowEffects_t>(oRenderGlowEffects)(pThis, edx, a2, a3);

	POLY_MARKER;

	for (int i = 0; i < pThis->GetGlowEntitiesCount(); ++i)
	{
		const auto glowObject = pThis->GetGlowObject(i);

		if (!glowObject->m_pEntity || glowObject->m_pEntity->GetClientClass()->m_iClassId != SSDK::ClassIndex::CCSPlayer || glowObject->IsUnused() || glowObject->m_pEntity->m_iTeamNum == pLocalPlayer->m_iTeamNum)
			continue;

		glowEsp.RenderAt(*glowObject);

	}
	POLY_MARKER;


	return reinterpret_cast<RenderGlowEffects_t>(oRenderGlowEffects)(pThis, edx, a2, a3);
}

LRESULT WINAPI WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	POLY_MARKER;
	if (pOverlay->IsShowUI())
	{
		POLY_MARKER;
		extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
		return TRUE;
	}
	typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
	return CallWindowProc((WNDPROC)oWndProc, hWnd, uMsg, wParam, lParam);
}

void hooks::Attach()
{
	POLY_MARKER;
	MH_Initialize();
	mapWithHooks[hCreateMove] = memory::CFunctionHook((LPVOID)SSDK::FindPresent(), hCreateMove, 7);

	MH_CreateHook((LPVOID)SSDK::FindPresent(),               hkPresent,             (LPVOID*)&oPresent);
	MH_CreateHook((LPVOID*)SSDK::FindCreatemove(),           hCreateMove,           (LPVOID*)&oCreateMove);
	MH_CreateHook((LPVOID*)SSDK::FindDrawIndexedPrimitive(), hDrawIndexedPrimitive, (LPVOID*)&oDrawIndexedPrimitive);
	MH_CreateHook((LPVOID*)SSDK::FindRenderGlowEffects(),    hRenderGlowEffects,    (LPVOID*)&oRenderGlowEffects);

	MH_EnableHook(MH_ALL_HOOKS);

	// Wait until overlay is ready for work.
	while (!pOverlay)
		Sleep(50);

	oWndProc = (uintptr_t)(SetWindowLongPtr(FindWindowA(nullptr, WINDOW_NAME), GWL_WNDPROC, reinterpret_cast<LONG_PTR>(WndProc)));
	POLY_MARKER;
}


void hooks::Detach()
{
	SetWindowLongPtr(FindWindowA(nullptr, WINDOW_NAME), GWLP_WNDPROC, (LONG_PTR)(oWndProc));

	MH_DisableHook(MH_ALL_HOOKS);
	Sleep(100);
	MH_RemoveHook(MH_ALL_HOOKS);

	POLY_MARKER;

	MH_Uninitialize();
}