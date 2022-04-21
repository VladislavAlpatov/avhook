#pragma once

#include <d3d9.h>
#include <Windows.h>

class DX9ColorFix
{
public:
	DX9ColorFix(LPDIRECT3DDEVICE9 pDevice);
    void RemoveColorFilter();
    void RestoreColorFilter();
    void RestoreRenderState();
private:
    IDirect3DStateBlock9* m_pStateBlock = nullptr;

    LPDIRECT3DDEVICE9   m_pDevice      = nullptr;
    D3DRENDERSTATETYPE  m_BackUp[7]   = { D3DRS_COLORWRITEENABLE, D3DRS_SRGBWRITEENABLE, D3DRS_ALPHABLENDENABLE, D3DRS_SRCBLEND, D3DRS_DESTBLEND, D3DRS_BLENDOP, D3DRS_FOGENABLE };
    DWORD               m_OldBlock[7] = {0};

};

