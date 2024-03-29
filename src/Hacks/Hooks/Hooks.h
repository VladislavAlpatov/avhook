#pragma once
#include <d3d9.h>
#include "../../SDK/CUserCMD.h"
#include "../../SDK/IGlowObjectManager.h"


namespace hooks
{

	int __stdcall hDrawIndexedPrimitive(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE type, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount);
	int __stdcall  hkPresent(LPDIRECT3DDEVICE9 pDevice, int a2, int a3, int a4, int a5);
	bool __stdcall hCreateMove(int fSampleTime, SSDK::CUserCmd* pUserCmd);
	int __fastcall hRenderGlowEffects(SSDK::IGlowObjectManager* pThis, void* edx, int a2, int a3);
	void Attach();
	void Detach();
}