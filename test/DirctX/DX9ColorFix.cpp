#include "DX9ColorFix.h"



DX9ColorFix::DX9ColorFix(LPDIRECT3DDEVICE9 pDevice)
{
    this->pDevice = pDevice;
}
void DX9ColorFix::RemoveColorFilter()
{
    this->pDevice->CreateStateBlock(D3DSBT_ALL, &this->state_block);

    for (byte i = 0; i < 7; i++)
    {
        this->pDevice->GetRenderState(this->back_up[i], &this->old_block[i]);

    }
    this->state_block->Capture();
}

void DX9ColorFix::RestoreRenderState()
{
    this->pDevice->SetVertexShader(nullptr);
    this->pDevice->SetPixelShader(nullptr);

    this->pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

    this->pDevice->SetRenderState(D3DRS_LIGHTING,                 FALSE);
    this->pDevice->SetRenderState(D3DRS_FOGENABLE,                FALSE);
    this->pDevice->SetRenderState(D3DRS_SCISSORTESTENABLE,        TRUE);
    this->pDevice->SetRenderState(D3DRS_ZWRITEENABLE,             FALSE);
    this->pDevice->SetRenderState(D3DRS_STENCILENABLE,            FALSE);
    this->pDevice->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS,     TRUE);
    this->pDevice->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE,    TRUE);
    this->pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,         TRUE);
    this->pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,          FALSE);
    this->pDevice->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, TRUE);
    this->pDevice->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS,     FALSE);
    this->pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE,          FALSE);
    this->pDevice->SetRenderState(D3DRS_SRCBLEND,                 D3DBLEND_SRCALPHA);
    this->pDevice->SetRenderState(D3DRS_SRCBLENDALPHA,            D3DBLEND_INVDESTALPHA);
    this->pDevice->SetRenderState(D3DRS_DESTBLEND,                D3DBLEND_INVSRCALPHA);
    this->pDevice->SetRenderState(D3DRS_DESTBLENDALPHA,           D3DBLEND_ONE);
    this->pDevice->SetRenderState(D3DRS_CULLMODE,                 D3DCULL_NONE);
    this->pDevice->SetRenderState(D3DRS_FILLMODE,                 D3DFILL_SOLID);
    this->pDevice->SetRenderState(D3DRS_ZENABLE,                  D3DZB_FALSE);

    this->pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_ALPHA);
}

void DX9ColorFix::RestoreColorFilter()
{
    this->state_block->Apply();
    this->state_block->Release();

    for (byte i = 0; i < 7; i++)
    {
        this->pDevice->SetRenderState(this->back_up[i], this->old_block[i]);
    }
}
