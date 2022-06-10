#pragma once
#include <Windows.h>
#include "../../Menu/COverlay.h"

namespace hooks
{
	inline uintptr_t		  oPresent;
	inline uintptr_t		  oDrawIndexedPrimitive;
	inline uintptr_t		  oNtQueryVirtualMemory;
	inline uintptr_t	      oWndProc;
	inline uintptr_t	      oCreateMove;
	inline uintptr_t          oOnKill;
	inline HMODULE		      hmodule;

	inline std::unique_ptr<COverlay> pOverlay;

	//int __stdcall  hDrawIndexedPrimitive(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE type, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount);
	void Attach(HMODULE ihModule);
	void Detach();
}