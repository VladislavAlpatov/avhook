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
#include "../../Globals/GlobalVars.h"

using namespace hooks;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int __stdcall  hkPresent(LPDIRECT3DDEVICE9 pDevice, int a2, int a3, int a4, int a5)
{
	POLY_MARKER;

	if (pOverlay == nullptr)
	{
		pOverlay = new COverlay(pDevice, hmodule, &GlobalVars::settings);
	}

	if (GetAsyncKeyState(VK_INSERT) & 1)
	{
		pOverlay->ToggleUI();
	}
	pOverlay->Render();		

	typedef int(__stdcall* Present)(LPDIRECT3DDEVICE9, int, int, int, int);
	return reinterpret_cast<Present>(hooks::oPresent)(pDevice, a2, a3, a4, a5);
}

bool __stdcall hCreateMove(int fSampleTime, SSDK::CUserCmd* pUserCmd)
{
	typedef bool(__stdcall* tCreateMove)(int, SSDK::CUserCmd*);

	// GlobalVars::pClient->pLocalPlayer->m_Index > 33 prevent from bug when you can peek team
	if (GlobalVars::pClient->pLocalPlayer == nullptr or pOverlay == nullptr or GlobalVars::pClient->pLocalPlayer->m_Index > 33)
	{
		return false;
	}
	GlobalVars::veLocalPlayerViewAngles = pUserCmd->viewangles;

	GlobalVars::pClient->pLocalPlayer->m_iDefaultFOV = GlobalVars::settings.m_MiscSettings.m_iCustomFov;

	// Looking for "visible" players
	for (int i = 1; i < 33; ++i)
	{
		SSDK::CBaseEntity* entity = reinterpret_cast<SSDK::CBaseEntity*>(GlobalVars::pIEntityList->GetClientEntity(i));

		if (!entity or entity->m_iTeamNum == GlobalVars::pClient->pLocalPlayer->m_iTeamNum or !entity->IsAlive())
			continue;

		auto pLocalPlayer = GlobalVars::pClient->pLocalPlayer;

		SSDK::CGameTrace   trace;
		SSDK::Ray_t        ray;
		SSDK::CTraceFilter tracefilter;
		tracefilter.pSkip = (void*)pLocalPlayer;

		ray.Init(pLocalPlayer->m_vecOrigin + pLocalPlayer->m_vecViewOffset, entity->GetBonePosition(Hacks::CAimBot::GetBoneIDBySelectedTab(GlobalVars::settings.m_AimBotSettings.m_iSelectedHitBox)));

		GlobalVars::pIEngineTrace->TraceRay(ray, MASK_SHOT | CONTENTS_GRATE, &tracefilter, &trace);

		entity->m_IsVisible = trace.hit_entity == entity;
	}

	if (pOverlay->IsShowUI() or !GlobalVars::pClient->pLocalPlayer->IsAlive())
	{
		return false;
	}

	Hacks::CHackingFeature* features[] = {
		new Hacks::CBunnyHop(&GlobalVars::settings.m_BunnyHopSettings),
		new Hacks::CAimBot(&GlobalVars::settings.m_AimBotSettings, pUserCmd)
	};

	for (int i = 0; i < IM_ARRAYSIZE(features); ++i)
	{
		features[i]->Work();
		delete features[i];
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

	auto  presentAddr = CMemory::FindPattern(xorstr("d3d9.dll"), xorstr("?? ?? ?? ?? ?? 83 E4 F8 51 51 56 8B 75 08 8B CE F7 D9 57 1B C9 8D 46 04 23 C8 6A ?? 51 8D 4C 24 10 E8 ?? ?? ?? ?? F7 46 ?? ?? ?? ?? ?? 74 07 BF ?? ?? ?? ?? EB 17"));
	MH_CreateHook((LPVOID)presentAddr, &hkPresent, reinterpret_cast<LPVOID*>(&hooks::oPresent));

	//Hook CreateMove
	auto createMoveAddr = CMemory::FindPattern(xorstr("client.dll"), xorstr("55 8B EC 56 8D 75 04 8B"));
	MH_CreateHook((LPVOID*)createMoveAddr, &hCreateMove, (LPVOID*)&oCreateMove);
	POLY_MARKER;
	uintptr_t DrawIndexedPrimitiveAddr = (uintptr_t)(GetModuleHandleA(xorstr("d3d9.dll"))) + 0x627b0;
	//MH_CreateHook((LPVOID*)DrawIndexedPrimitiveAddr, &hDrawIndexedPrimitive, (LPVOID*)&oDrawIndexedPrimitive);
	//MH_CreateHook(GetProcAddress(GetModuleHandle("ntdll"), xorstr("NtQueryVirtualMemory")), &hNtQueryVirtualMemory, (LPVOID*)&oNtQueryVirtualMemory);
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

	hooks::pOverlay->Detach();
	MH_Uninitialize();
}


HRESULT GenerateColoredTexture(IDirect3DDevice9* pDevice, IDirect3DTexture9** pTexture, DWORD dwColor) 
{

	HRESULT hr = pDevice->CreateTexture(8, 8, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, pTexture, NULL);

	if (FAILED(hr))
	{
		return hr;
	}

	D3DLOCKED_RECT d3dlr;
	(*pTexture)->LockRect(0, &d3dlr, 0, 0);

	BYTE* pDstRow = (BYTE*)d3dlr.pBits;

	// Override color bytes
	// Use 8 cuz of D3DFMT_A8R8G8B8
	for (int rowIndex = 0; rowIndex < 8; rowIndex++)
	{
		// Calculating pointer for current row
		auto pCurrentRow = (DWORD*)(pDstRow + rowIndex * d3dlr.Pitch);
		

		for (int x = 0; x < 8; x++)
			pCurrentRow[x] = dwColor;
	}

	(*pTexture)->UnlockRect(0);

	return S_OK;
}


/*int __stdcall hooks::hDrawIndexedPrimitive(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE type, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount)
{
	typedef bool(__stdcall* tDrawIndexedPrimitive)(LPDIRECT3DDEVICE9, D3DPRIMITIVETYPE, INT, UINT, UINT, UINT, UINT);
	if (NumVertices >= GlobalVars::settings.m_LabelEspSettings.m_iIndexMin and NumVertices <= GlobalVars::settings.m_LabelEspSettings.m_iIndexMax)
	{
		IDirect3DTexture9* text;
		auto color = GlobalVars::settings.m_LabelEspSettings.m_GlovesColor.Value;

		GenerateColoredTexture(pDevice, &text, D3DCOLOR_ARGB((int)(color.w * 255), (int)(color.x * 255), (int)(color.y * 255), (int)(color.z * 255)));

		pDevice->SetTexture(0, text);
		//pDevice->SetRenderState(D3DRS_ZENABLE, false);
		//return reinterpret_cast<tDrawIndexedPrimitive>(oDrawIndexedPrimitive)(pDevice, type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
		//pDevice->SetRenderState(D3DRS_ZENABLE, true);
		text->Release();
	}

	return reinterpret_cast<tDrawIndexedPrimitive>(oDrawIndexedPrimitive)(pDevice, type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
}*/