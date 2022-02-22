#pragma once
#include <Windows.h>
#include <Mmsystem.h>

#include <d3d9.h>
#include <thread>

#include "MinHook.h"

#include "../../Utils/offsets.h"
#include "../../Utils/memory.h"
#include "../../Menu/COverlay.h"
#include "../../SDK/CUserCMD.h"
#include "../../Hacks/AimBot.h"
#include "../../RazerSDK/CRazer.h"
#include "../../Hacks/TriggerBot.h"
#include "../../Utils/Marker.h"
#include "../../Hacks/bhop.h"

typedef enum _MEMORY_INFORMATION_CLASS {
	MemoryBasicInformation
} MEMORY_INFORMATION_CLASS;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
namespace hooks
{
	inline DWORD		  oPresent;
	inline DWORD		  oDrawIndexedPrimitive;
	inline DWORD		  oNtQueryVirtualMemory;
	inline DWORD	      oWndProc;
	inline DWORD	      oCreateMove;
	inline DWORD          oOnKill;
	inline HMODULE		  hmodule;
	inline COverlay*      pOverlay = NULL;
	int __stdcall  hkPresent(LPDIRECT3DDEVICE9 pDevice, int a2, int a3, int a4, int a5);
	LRESULT WINAPI WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	bool __stdcall hCreateMove(int fSampleTime, SSDK::CUserCmd* pUserCmd);
	int __fastcall hOnkill(void* pThis, void* edx);
	int __stdcall  hDrawIndexedPrimitive(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE type, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount);
	NTSTATUS __stdcall hNtQueryVirtualMemory(HANDLE ProcessHandle, PVOID BaseAddress, MEMORY_INFORMATION_CLASS MemoryInformationClass, PVOID MemoryInformation, SIZE_T MemoryInformationLength, PSIZE_T ReturnLength);
	void Attach(HMODULE ihModule);
	void Detach();
}