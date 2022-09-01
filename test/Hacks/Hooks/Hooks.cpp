//========= Copyright Alpatov Softworks, All rights reserved. ============//
//
// Sets hooks to game functions
//
//===============================================================================


#include "Hooks.h"

#include "../../Utils/offsets.h"
#include "../../Utils/Marker.h"

#include "../../Hacks/AimBot.h"
#include "../../Hacks/TriggerBot.h"
#include "../../Hacks/bhop.h"
#include "../../Hacks/Esp/CGlowEsp.h"

#include "../../SDK/CUserCMD.h"
#include "../../SDK/Finder.h"

#include "../../Globals/Interfaces.h"
#include "../../Globals/DirectX9.h"
#include "../../Globals/Settings.h"

#include "../../RazerSDK/CRazer.h"

#include <stdexcept>
#include <array>
#include <Windows.h>


#include "../../Menu/COverlay.h"
#include "MinHook.h"


using namespace hooks;


static uintptr_t		  oPresent;
static uintptr_t		  oDrawIndexedPrimitive;
static uintptr_t		  oNtQueryVirtualMemory;
static uintptr_t	      oWndProc;
static uintptr_t	      oCreateMove;
static uintptr_t          oOnKill;
static uintptr_t		  oDoPostScreenEffects;
static uintptr_t		  oRenderGlowEffects;
static std::unique_ptr<UI::COverlay> pOverlay;

void SetWorldColor(const ImColor& col)
{
	static auto mat_ambient_light_r = GlobalVars::g_pCvarManager->FindVar("mat_ambient_light_r");
	static auto mat_ambient_light_g = GlobalVars::g_pCvarManager->FindVar("mat_ambient_light_g");
	static auto mat_ambient_light_b = GlobalVars::g_pCvarManager->FindVar("mat_ambient_light_b");


	mat_ambient_light_r->m_pParentCvar->SetValue(col.Value.x);
	mat_ambient_light_g->m_pParentCvar->SetValue(col.Value.y);
	mat_ambient_light_b->m_pParentCvar->SetValue(col.Value.z);

}
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
			auto res = reinterpret_cast<tDrawIndexedPrimitive>(oDrawIndexedPrimitive)(pDevice, type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
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
		pOverlay = std::unique_ptr<UI::COverlay>(new UI::COverlay(pDevice));
		GlobalVars::pDevice = pDevice;
	}

	if (GetAsyncKeyState(VK_INSERT) & 1)
		pOverlay->ToggleUI();
	pOverlay->Render();		

	typedef int(__stdcall* Present)(LPDIRECT3DDEVICE9, int, int, int, int);
	return reinterpret_cast<Present>(oPresent)(pDevice, a2, a3, a4, a5);
}

bool __stdcall hooks::hCreateMove(int fSampleTime, SSDK::CUserCmd* pUserCmd)
{
	typedef bool(__stdcall* tCreateMove)(int, SSDK::CUserCmd*);
	POLY_MARKER;

	auto pLocalPlayer = SSDK::ClientBase::GetLocalPlayer();
	// GlobalVars::pClient->pLocalPlayer->m_Index > 33 prevent from bug when you can peek team
	if (!pLocalPlayer or !pOverlay or pLocalPlayer->m_Index > 33 or !reinterpret_cast<tCreateMove>(oCreateMove)(fSampleTime, pUserCmd))
	{
		return false;
	}

	POLY_MARKER;
	
	pLocalPlayer->m_iDefaultFOV = GlobalVars::g_AllSettings.m_MiscSettings.m_iCustomFov;


	static auto pCrosshair = GlobalVars::g_pCvarManager->FindVar(xorstr("crosshair"));
	pCrosshair->m_pParentCvar->SetValue(GlobalVars::g_AllSettings.m_CrosshairSettings.m_Color.Value.w == 0.f or !GlobalVars::g_AllSettings.m_CrosshairSettings.m_bActive);
	//pLocalPlayer->m_iDefaultFOV = GlobalVars::g_AllSettings.m_MiscSettings.m_iCustomFov;

	// Looking for "visible" players
	for (const auto pEnt : GlobalVars::g_pIEntityList->GetEntityList())
	{

		if (pEnt->m_iTeamNum == pLocalPlayer->m_iTeamNum or !pEnt->IsAlive())
			continue;

		SSDK::CGameTrace   trace;
		SSDK::Ray_t        ray;
		SSDK::CTraceFilter tracefilter;
		tracefilter.pSkip = (void*)pLocalPlayer;

		ray.Init(pLocalPlayer->m_vecOrigin + pLocalPlayer->m_vecViewOffset, pEnt->GetBonePosition(Hacks::CAimBot::GetBoneIDBySelectedTab(GlobalVars::g_AllSettings.m_AimBotSettings.m_iSelectedHitBox)));

		GlobalVars::g_pIEngineTrace->TraceRay(ray, MASK_SHOT | CONTENTS_GRATE, &tracefilter, &trace);

		pEnt->m_IsVisible = trace.hit_entity == pEnt;
	}

	if (pOverlay->IsShowUI() or !pLocalPlayer->IsAlive())
	{
		return false;
	}

	std::array<std::unique_ptr<Hacks::CHackingFeature>, 2> features =
	{
		std::unique_ptr<Hacks::CHackingFeature>(new Hacks::CBunnyHop(pUserCmd, &GlobalVars::g_AllSettings.m_BunnyHopSettings)),
		std::unique_ptr<Hacks::CHackingFeature>(new Hacks::CAimBot(&GlobalVars::g_AllSettings.m_AimBotSettings, pUserCmd))
	};

	for (auto& pFeature : features)
	{
		pFeature->Work();
	}
	reinterpret_cast<tCreateMove>(oCreateMove)(fSampleTime, pUserCmd);

	return !GlobalVars::g_AllSettings.m_AimBotSettings.m_bSilent;
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

int __fastcall hooks::hRenderGlowEffects(SSDK::IGlowObjectManager* pThis, void* edx, int a2, int a3)
{
	typedef int(__fastcall* RenderGlowEffects_t)(void*, void*, int, int);


	POLY_MARKER;
	static auto glowEsp = Esp::CGlowEsp(&GlobalVars::g_AllSettings.m_GlowEspSettings);
	auto pLocalPlayer   = SSDK::ClientBase::GetLocalPlayer();

	if (!glowEsp.isActive() or !pLocalPlayer or !GlobalVars::g_pIEngineClient->IsInGame())
		return reinterpret_cast<RenderGlowEffects_t>(oRenderGlowEffects)(pThis, edx, a2, a3);

	POLY_MARKER;

	for (int i = 0; i < pThis->GetGlowEntitiesCount(); ++i)
	{

		auto glowObject = pThis->GetGlowObject(i);

		if (!glowObject->m_pEntity or glowObject->m_pEntity->GetClientClass()->m_iClassId != SSDK::ClassIndex::CCSPlayer or glowObject->IsUnused() or glowObject->m_pEntity->m_iTeamNum == pLocalPlayer->m_iTeamNum)
			continue;

		glowEsp.RenderAt(*glowObject);

	}
	POLY_MARKER;


	return reinterpret_cast<RenderGlowEffects_t>(oRenderGlowEffects)(pThis, edx, a2, a3);
}

void hooks::Attach()
{
	POLY_MARKER;
	MH_Initialize();
	
	MH_CreateHook((LPVOID)SSDK::FindPresent(),               &hkPresent,             (LPVOID*)&oPresent);
	MH_CreateHook((LPVOID*)SSDK::FindCreatemove(),           &hCreateMove,           (LPVOID*)&oCreateMove);
	MH_CreateHook((LPVOID*)SSDK::FindDrawIndexedPrimitive(), &hDrawIndexedPrimitive, (LPVOID*)&oDrawIndexedPrimitive);
	MH_CreateHook((LPVOID*)SSDK::FindRenderGlowEffects(),    &hRenderGlowEffects,    (LPVOID*)&oRenderGlowEffects);

	MH_EnableHook(MH_ALL_HOOKS);

	// Wait until overlay is ready for work.
	while (!pOverlay)
		Sleep(50);

	oWndProc = (uintptr_t)(SetWindowLongPtr(FindWindowA(NULL, WINDOW_NAME), GWL_WNDPROC, reinterpret_cast<LONG_PTR>(WndProc)));
	POLY_MARKER
}


void hooks::Detach()
{
	SetWindowLongPtr(FindWindowA(NULL, WINDOW_NAME), GWLP_WNDPROC, (LONG_PTR)(oWndProc));

	MH_DisableHook(MH_ALL_HOOKS);
	Sleep(100);
	MH_RemoveHook(MH_ALL_HOOKS);

	POLY_MARKER;

	MH_Uninitialize();
}