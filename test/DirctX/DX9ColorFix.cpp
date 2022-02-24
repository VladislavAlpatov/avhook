#include "DX9ColorFix.h"



DX9ColorFix::DX9ColorFix(LPDIRECT3DDEVICE9 pDevice)
{
    m_pDevice = pDevice;
}
void DX9ColorFix::RemoveColorFilter()
{
    m_pDevice->CreateStateBlock(D3DSBT_ALL, &m_pStateBlock);

    for (byte i = 0; i < 7; i++)
    {
        m_pDevice->GetRenderState(m_BackUp[i], &m_OldBlock[i]);

    }
    m_pStateBlock->Capture();
}

void DX9ColorFix::RestoreRenderState()
{
    m_pDevice->SetVertexShader(nullptr);
    m_pDevice->SetPixelShader(nullptr);

    m_pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

    m_pDevice->SetRenderState(D3DRS_LIGHTING,                 FALSE);
    m_pDevice->SetRenderState(D3DRS_FOGENABLE,                FALSE);
    m_pDevice->SetRenderState(D3DRS_SCISSORTESTENABLE,        TRUE);
    m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE,             FALSE);
    m_pDevice->SetRenderState(D3DRS_STENCILENABLE,            FALSE);
    m_pDevice->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS,     TRUE);
    m_pDevice->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE,    TRUE);
    m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,         TRUE);
    m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,          FALSE);
    m_pDevice->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, TRUE);
    m_pDevice->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS,     FALSE);
    m_pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE,          FALSE);
    m_pDevice->SetRenderState(D3DRS_SRCBLEND,                 D3DBLEND_SRCALPHA);
    m_pDevice->SetRenderState(D3DRS_SRCBLENDALPHA,            D3DBLEND_INVDESTALPHA);
    m_pDevice->SetRenderState(D3DRS_DESTBLEND,                D3DBLEND_INVSRCALPHA);
    m_pDevice->SetRenderState(D3DRS_DESTBLENDALPHA,           D3DBLEND_ONE);
    m_pDevice->SetRenderState(D3DRS_CULLMODE,                 D3DCULL_NONE);
    m_pDevice->SetRenderState(D3DRS_FILLMODE,                 D3DFILL_SOLID);
    m_pDevice->SetRenderState(D3DRS_ZENABLE,                  D3DZB_FALSE);

    m_pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_ALPHA);
}

void DX9ColorFix::RestoreColorFilter()
{
    m_pStateBlock->Apply();
    m_pStateBlock->Release();

    for (byte i = 0; i < 7; i++)
    {
        m_pDevice->SetRenderState(m_BackUp[i], m_OldBlock[i]);
    }
}
