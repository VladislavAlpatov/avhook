#include "CTextureOverride.h"
#include <d3dx9.h>
#include "../../../Globals/DirectX9.h"

using namespace Esp;


CTextureOverride::CTextureOverride(const int uid, const ImColor& col, const std::string& name, bool enableZ)
{
	m_bEnableZ = enableZ;
	m_iUid = uid;
	m_Color = col;
	m_sName = name;

	GenerateColoredTexture(&m_pTexture, m_Color);
}
bool CTextureOverride::GenerateColoredTexture(IDirect3DTexture9** pTexture, const ImColor& color)
{

	HRESULT hr = GlobalVars::pDevice->CreateTexture(8, 8, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, pTexture, NULL);

	if (FAILED(hr))
	{
		return false;
	}

	D3DLOCKED_RECT d3dlr;
	(*pTexture)->LockRect(0, &d3dlr, 0, 0);

	BYTE* pDstRow = (BYTE*)d3dlr.pBits;



	// Override color bytes
	// Use 8 cuz of D3DFMT_A8R8G8B8

	auto dxColor = D3DCOLOR_ARGB((int)(color.Value.w * 255), (int)(color.Value.x * 255), (int)(color.Value.y * 255), (int)(color.Value.z * 255));

	for (int rowIndex = 0; rowIndex < 8; rowIndex++)
	{
		// Calculating pointer for current row
		auto pCurrentRow = (DWORD*)(pDstRow + rowIndex * d3dlr.Pitch);


		for (int x = 0; x < 8; x++)
			pCurrentRow[x] = dxColor;
	}

	(*pTexture)->UnlockRect(0);

	return true;
}
void CTextureOverride::UpdateColor(const ImColor& newColor)
{
	if (m_Color == newColor)
		return;
	m_Color = newColor;

	m_pTexture->Release();
	GenerateColoredTexture(&m_pTexture, m_Color);
}

void CTextureOverride::OverrideColor()
{
	GlobalVars::pDevice->SetTexture(0, m_pTexture);
}

ImColor CTextureOverride::GetColor()
{
	return m_Color;
}

CTextureOverride::~CTextureOverride()
{
	if (!m_pTexture)
		m_pTexture->Release();
}
