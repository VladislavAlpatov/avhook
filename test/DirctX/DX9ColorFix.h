#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>
#include "../Utils/Marker.h"


class DX9ColorFix
{
public:
	DX9ColorFix(LPDIRECT3DDEVICE9 pDevice);
    void RemoveColorFilter();
    void RestoreColorFilter();
    void RestoreRenderState();
private:
    IDirect3DStateBlock9* state_block = nullptr;

    LPDIRECT3DDEVICE9   pDevice      = nullptr;
    D3DRENDERSTATETYPE  back_up[7]   = { D3DRS_COLORWRITEENABLE, D3DRS_SRGBWRITEENABLE, D3DRS_ALPHABLENDENABLE, D3DRS_SRCBLEND, D3DRS_DESTBLEND, D3DRS_BLENDOP, D3DRS_FOGENABLE };
    DWORD               old_block[7] = {0};

};

