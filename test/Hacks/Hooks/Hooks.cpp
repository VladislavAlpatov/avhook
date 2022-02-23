#include "Hooks.h"

int __stdcall  hooks::hkPresent(LPDIRECT3DDEVICE9 pDevice, int a2, int a3, int a4, int a5)
{
	POLY_MARKER

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
void KillKeyBoardEffect()
{
	CRazer razer = CRazer();
	RZEFFECTID onKillEffectId;
	RZEFFECTID clearEffectId;
	ChromaSDK::Keyboard::STATIC_EFFECT_TYPE clearEffect;
	clearEffect.Color = RGB(255, 255, 255);

	ChromaSDK::Keyboard::STATIC_EFFECT_TYPE onKillEffect;


	onKillEffect.Color = GlobalVars::settings.m_ChromaSettings.m_KillGlowColor.ToRgbColorRef();


	POLY_MARKER


	razer.CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_STATIC, &onKillEffect, &onKillEffectId);
	razer.CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_STATIC, &clearEffect, &clearEffectId);
	razer.SetEffect(onKillEffectId);
	Sleep(200);
	razer.SetEffect(clearEffectId);

	razer.DeleteEffect(clearEffectId);
	razer.DeleteEffect(onKillEffectId);
}
void hooks::Attach(HMODULE ihModule)
{
	hooks::hmodule = ihModule;
	MH_Initialize();

	POLY_MARKER
	// Hooking and also remove other hooks from CBaseDevice::Present fucntion

	DWORD presentAddr = (DWORD)(GetModuleHandle(xorstr("d3d9.dll"))) + 0xE5880;

	MH_CreateHook((LPVOID)presentAddr, &hkPresent, reinterpret_cast<LPVOID*>(&hooks::oPresent));
	POLY_MARKER
	// Hook on kill function
	auto onKillAddr = CMemory::FindPattern(xorstr("server.dll"), xorstr("\x55\x8B\xEC\x81\xEC\x00\x00\x00\x00\x53\x8B\xD9\xC7\x05\x4C"), xorstr("xxxxx????xxxxxx"));
	MH_CreateHook((LPVOID*)onKillAddr, &hOnkill, (LPVOID*)&oOnKill);
	POLY_MARKER
	//Hook CreateMove
	auto createMoveAddr = CMemory::FindPattern(xorstr("client.dll"), xorstr("\x55\x8B\xEC\x56\x8D\x75\x04\x8B"), xorstr("xxxxxxxx"));
	MH_CreateHook((LPVOID*)createMoveAddr, &hCreateMove, (LPVOID*)&oCreateMove);

	DWORD DrawIndexedPrimitiveAddr = (DWORD)(GetModuleHandle(xorstr("d3d9.dll"))) + 0x627b0;
	MH_CreateHook((LPVOID*)DrawIndexedPrimitiveAddr, &hDrawIndexedPrimitive, (LPVOID*)&oDrawIndexedPrimitive);
	MH_CreateHook(GetProcAddress(GetModuleHandle("ntdll"), xorstr("NtQueryVirtualMemory")), &hNtQueryVirtualMemory, (LPVOID*)&oNtQueryVirtualMemory);
	MH_EnableHook(MH_ALL_HOOKS);
	// Wait until overlay is ready for work.
	while (!hooks::pOverlay)
		Sleep(50);

	oWndProc = (DWORD)(SetWindowLongPtr(FindWindowA(NULL, WINDOW_NAME), GWL_WNDPROC, reinterpret_cast<LONG_PTR>(WndProc)));
	POLY_MARKER
}

LRESULT WINAPI hooks::WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	POLY_MARKER
	if (hooks::pOverlay->IsShowUI())
	{
		POLY_MARKER

		ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
		return TRUE;
	}
	typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
	return CallWindowProc((WNDPROC)hooks::oWndProc, hWnd, uMsg, wParam, lParam);
}

void hooks::Detach()
{
	SetWindowLongPtr(FindWindowA(NULL, WINDOW_NAME), GWLP_WNDPROC, (LONG_PTR)(hooks::oWndProc));

	MH_DisableHook(MH_ALL_HOOKS);
	Sleep(100);
	MH_RemoveHook(MH_ALL_HOOKS);

	POLY_MARKER

	hooks::pOverlay->Detach();
	MH_Uninitialize();
}

int  __fastcall hooks::hOnkill(void* pThis, void* edx)
{
	POLY_MARKER

	if (GlobalVars::bChromaSupport)
		std::thread(KillKeyBoardEffect).detach();

	if (GlobalVars::settings.m_MiscSettings.m_bKillSound and GlobalVars::settings.m_MiscSettings.killSoundPath[0] == NULL)
	{
		//PlaySound(MAKEINTRESOURCE(IDR_WAVE3), GlobalVars::hModule, SND_RESOURCE | SND_ASYNC);
	}
	else if (GlobalVars::settings.m_MiscSettings.m_bKillSound)
	{
		PlaySound(GlobalVars::settings.m_MiscSettings.killSoundPath, GlobalVars::hModule, SND_ASYNC);
	}

	typedef int(__fastcall* tOnkill)(void*, void* edx);
	return reinterpret_cast<tOnkill>(oOnKill)(pThis, edx);
}

bool __stdcall hooks::hCreateMove(int fSampleTime, SSDK::CUserCmd* pUserCmd)
{
	POLY_MARKER;
	if (GlobalVars::client->pLocalPlayer == nullptr or pOverlay == nullptr)
	{
		typedef bool(__stdcall* tCreateMove)(int, SSDK::CUserCmd*);
		return reinterpret_cast<tCreateMove>(oCreateMove)(fSampleTime, pUserCmd);
	}
	GlobalVars::veLocalPlayerViewAngles = pUserCmd->viewangles;
	
	// Overrige fov
	GlobalVars::client->pLocalPlayer->m_iDefaultFOV = GlobalVars::settings.m_MiscSettings.m_iCustomFov;

	// Looking for "visible" players
	for (int i = 1; i < 33; ++i)
	{
		SSDK::CBaseEntity* entity = reinterpret_cast<SSDK::CBaseEntity*>(GlobalVars::pIEntityList->GetClientEntity(i));

		if (!entity or entity->m_iTeamNum == GlobalVars::client->pLocalPlayer->m_iTeamNum or !entity->IsAlive())
			continue;

		auto pLocalPlayer = GlobalVars::client->pLocalPlayer;

		SSDK::CGameTrace   trace;
		SSDK::Ray_t        ray;
		SSDK::CTraceFilter tracefilter;
		tracefilter.pSkip = (void*)pLocalPlayer;

		ray.Init(pLocalPlayer->m_vecOrigin + pLocalPlayer->m_vecViewOffset, entity->GetBonePosition(8));

		GlobalVars::pIEngineTrace->TraceRay(ray, MASK_SHOT | CONTENTS_GRATE, &tracefilter, &trace);

		entity->m_IsVisible = trace.hit_entity == entity;
	}

	if (pOverlay->IsShowUI())
	{
		typedef bool(__stdcall* tCreateMove)(int, SSDK::CUserCmd*);
		return reinterpret_cast<tCreateMove>(oCreateMove)(fSampleTime, pUserCmd);
	}

	Hacks::CHackingFeature* features[] = {
		new Hacks::BunnyHop(&GlobalVars::settings.m_BunnyHopSettings),
		new Hacks::CAimBot(&GlobalVars::settings.m_AimBotSettings, pUserCmd)
	};

	for (int i = 0; i < IM_ARRAYSIZE(features); ++i)
	{
		features[i]->Work();
		delete features[i];
	}
	
	typedef bool(__stdcall* tCreateMove)(int, SSDK::CUserCmd*);
	return reinterpret_cast<tCreateMove>(oCreateMove)(fSampleTime, pUserCmd);
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


int __stdcall hooks::hDrawIndexedPrimitive(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE type, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount)
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
}
NTSTATUS __stdcall hooks::hNtQueryVirtualMemory(HANDLE ProcessHandle, PVOID BaseAddress, MEMORY_INFORMATION_CLASS MemoryInformationClass, PVOID MemoryInformation, SIZE_T MemoryInformationLength, PSIZE_T ReturnLength)
{
	MODULEINFO modInfol;
	GetModuleInformation(GetCurrentProcess(), GlobalVars::hModule, &modInfol, sizeof(MODULEINFO));
	if (BaseAddress >= modInfol.lpBaseOfDll and ((uintptr_t)modInfol.lpBaseOfDll + (uintptr_t)modInfol.SizeOfImage) >= (uintptr_t)BaseAddress)
	{
		return 0x80;
	}


	typedef NTSTATUS(__stdcall* tNtQueryVirtualMemory)(HANDLE, PVOID, MEMORY_INFORMATION_CLASS, PVOID, SIZE_T, PSIZE_T);
	return reinterpret_cast<tNtQueryVirtualMemory>(oNtQueryVirtualMemory)(ProcessHandle, BaseAddress, MemoryInformationClass, MemoryInformation, MemoryInformationLength, ReturnLength);

}