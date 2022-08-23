#pragma once
#include <d3d9.h>
#include "../../SDK/CUserCMD.h"

namespace hooks
{

	int __stdcall hDrawIndexedPrimitive(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE type, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount);
	int __stdcall  hkPresent(LPDIRECT3DDEVICE9 pDevice, int a2, int a3, int a4, int a5);
	bool __stdcall hCreateMove(int fSampleTime, SSDK::CUserCmd* pUserCmd);
	int __fastcall DoPostScreenSpaceEffects(void* pThis, void* edx, void* pView);
	void Attach();
	void Detach();
}