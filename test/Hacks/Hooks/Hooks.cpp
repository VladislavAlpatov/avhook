#pragma once
#include "Hooks.h"

#include "../../Utils/offsets.h"
#include "../../Utils/memory.h"
#include "../../Hacks/AimBot.h"
#include "../../RazerSDK/CRazer.h"
#include "../../Hacks/TriggerBot.h"
#include "../../Utils/Marker.h"
#include "../../Hacks/bhop.h"

#include "../../SDK/CUserCMD.h"

#include "MinHook.h"
#include "../../Globals/Interfaces.h"
#include "../../Globals/DirectX9.h"
#include "../../Globals/Settings.h"

#include <stdexcept>
#include <array>


using namespace hooks;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int __stdcall hDrawIndexedPrimitive(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE type, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount)
{
	/*if (NumVertices >= GlobalVars::settings.m_LabelEspSettings.m_iIndexMin and NumVertices <= GlobalVars::settings.m_LabelEspSettings.m_iIndexMax)
	{
		IDirect3DTexture9* text;
		auto color = GlobalVars::settings.m_LabelEspSettings.m_GlovesColor.Value;

		GenerateColoredTexture(pDevice, &text, D3DCOLOR_ARGB((int)(color.w * 255), (int)(color.x * 255), (int)(color.y * 255), (int)(color.z * 255)));

		pDevice->SetTexture(0, text);
		//pDevice->SetRenderState(D3DRS_ZENABLE, false);
		//return reinterpret_cast<tDrawIndexedPrimitive>(oDrawIndexedPrimitive)(pDevice, type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
		//pDevice->SetRenderState(D3DRS_ZENABLE, true);
		text->Release();
	}*/

	

	typedef bool(__stdcall* tDrawIndexedPrimitive)(LPDIRECT3DDEVICE9, D3DPRIMITIVETYPE, INT, UINT, UINT, UINT, UINT);
	return reinterpret_cast<tDrawIndexedPrimitive>(oDrawIndexedPrimitive)(pDevice, type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
}

int __stdcall  hkPresent(LPDIRECT3DDEVICE9 pDevice, int a2, int a3, int a4, int a5)
{
	POLY_MARKER;

	if (!pOverlay)
	{
		pOverlay = std::unique_ptr<COverlay>(new COverlay(pDevice));
		GlobalVars::pDevice = pDevice;
	}

	if (GetAsyncKeyState(VK_INSERT) & 1)
		pOverlay->ToggleUI();
	pOverlay->Render();		

	typedef int(__stdcall* Present)(LPDIRECT3DDEVICE9, int, int, int, int);
	return reinterpret_cast<Present>(hooks::oPresent)(pDevice, a2, a3, a4, a5);
}

bool __stdcall hCreateMove(int fSampleTime, SSDK::CUserCmd* pUserCmd)
{
	typedef bool(__stdcall* tCreateMove)(int, SSDK::CUserCmd*);

	// GlobalVars::pClient->pLocalPlayer->m_Index > 33 prevent from bug when you can peek team
	if (!GlobalVars::g_pClient->pLocalPlayer or !pOverlay or GlobalVars::g_pClient->pLocalPlayer->m_Index > 33)
	{
		return false;
	}

	POLY_MARKER;


	GlobalVars::g_pClient->pLocalPlayer->m_iDefaultFOV = GlobalVars::g_AllSettings.m_MiscSettings.m_iCustomFov;

	// Looking for "visible" players
	for (const auto pEnt : GlobalVars::g_pIEntityList->GetEntityList())
	{

		if (pEnt->m_iTeamNum == GlobalVars::g_pClient->pLocalPlayer->m_iTeamNum or !pEnt->IsAlive())
			continue;

		auto pLocalPlayer = GlobalVars::g_pClient->pLocalPlayer;

		SSDK::CGameTrace   trace;
		SSDK::Ray_t        ray;
		SSDK::CTraceFilter tracefilter;
		tracefilter.pSkip = (void*)pLocalPlayer;

		ray.Init(pLocalPlayer->m_vecOrigin + pLocalPlayer->m_vecViewOffset, pEnt->GetBonePosition(Hacks::CAimBot::GetBoneIDBySelectedTab(GlobalVars::g_AllSettings.m_AimBotSettings.m_iSelectedHitBox)));

		GlobalVars::g_pIEngineTrace->TraceRay(ray, MASK_SHOT | CONTENTS_GRATE, &tracefilter, &trace);

		pEnt->m_IsVisible = trace.hit_entity == pEnt;
	}

	if (pOverlay->IsShowUI() or !GlobalVars::g_pClient->pLocalPlayer->IsAlive())
	{
		return false;
	}

	std::array<std::unique_ptr<Hacks::CHackingFeature>, 2> features =
	{
		std::unique_ptr<Hacks::CHackingFeature>(new Hacks::CBunnyHop(&GlobalVars::g_AllSettings.m_BunnyHopSettings)),
		std::unique_ptr<Hacks::CHackingFeature>(new Hacks::CAimBot(&GlobalVars::g_AllSettings.m_AimBotSettings, pUserCmd))
	};

	for (auto& pFeature : features)
	{
		pFeature->Work();
	}

	return reinterpret_cast<tCreateMove>(oCreateMove)(fSampleTime, pUserCmd);
}

LRESULT WINAPI WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	POLY_MARKER;
	if (pOverlay->IsShowUI())
	{
		POLY_MARKER;

		ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
		return TRUE;
	}
	typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
	return CallWindowProc((WNDPROC)hooks::oWndProc, hWnd, uMsg, wParam, lParam);
}

void hooks::Attach(HMODULE ihModule)
{
	POLY_MARKER;

	hooks::hmodule = ihModule;
	MH_Initialize();

	auto  presentAddr = Memory::FindPattern(xorstr("d3d9.dll"), xorstr("?? ?? ?? ?? ?? 83 E4 F8 51 51 56 8B 75 08 8B CE F7 D9 57 1B C9 8D 46 04 23 C8 6A ?? 51 8D 4C 24 10 E8 ?? ?? ?? ?? F7 46 ?? ?? ?? ?? ?? 74 07 BF ?? ?? ?? ?? EB 17"));
	
	if (!presentAddr)
		throw std::runtime_error(xorstr("DirectX 9 initialization failure"));
	
	MH_CreateHook((LPVOID)presentAddr, &hkPresent, reinterpret_cast<LPVOID*>(&hooks::oPresent));

	POLY_MARKER;

	//Hook CreateMove
	auto createMoveAddr = Memory::FindPattern(xorstr("client.dll"), xorstr("55 8B EC 56 8D 75 04 8B"));

	if (!createMoveAddr)
		throw std::runtime_error(xorstr("CSGO initialization failure"));

	MH_CreateHook((LPVOID*)createMoveAddr, &hCreateMove, (LPVOID*)&oCreateMove);
	POLY_MARKER;

	uintptr_t DrawIndexedPrimitiveAddr = Memory::FindPattern(xorstr("d3d9.dll"), xorstr("8B FF 55 8B EC 6A FF 68 ? ? ? ? 64 A1 ? ? ? ? 50 83 EC 20 53 56 57 A1 ? ? ? ? 33 C5 50 8D 45 F4 64 A3 ? ? ? ? 89 65 F0 8B 75 08 85 F6 0F 84 ? ? ? ? 8D 5E 04 89 5D EC 89 5D D4 C7 45 ? ? ? ? ? 83 7B 18 00 0F 85 ? ? ? ? C7 45 ? ? ? ? ? F7 46 ? ? ? ? ? 0F 85 ? ? ? ? 81 8E ? ? ? ? ? ? ? ?"));

	MH_CreateHook((LPVOID*)DrawIndexedPrimitiveAddr, &hDrawIndexedPrimitive, (LPVOID*)&oDrawIndexedPrimitive);
	// MH_CreateHook(GetProcAddress(GetModuleHandle("ntdll"), xorstr("NtQueryVirtualMemory")), &hNtQueryVirtualMemory, (LPVOID*)&oNtQueryVirtualMemory);

	MH_EnableHook(MH_ALL_HOOKS);
	// Wait until overlay is ready for work.
	while (!pOverlay)
		Sleep(50);

	oWndProc = (uintptr_t)(SetWindowLongPtr(FindWindowA(NULL, WINDOW_NAME), GWL_WNDPROC, reinterpret_cast<LONG_PTR>(WndProc)));
	POLY_MARKER
}


void hooks::Detach()
{
	SetWindowLongPtr(FindWindowA(NULL, WINDOW_NAME), GWLP_WNDPROC, (LONG_PTR)(hooks::oWndProc));

	MH_DisableHook(MH_ALL_HOOKS);
	Sleep(100);
	MH_RemoveHook(MH_ALL_HOOKS);

	POLY_MARKER;

	MH_Uninitialize();
}