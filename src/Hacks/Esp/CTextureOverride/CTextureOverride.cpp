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
Esp::CTextureOverride::CTextureOverride(const CTextureOverride& other)
{
	m_bEnableZ = other.m_bEnableZ;
	m_iUid = other.m_iUid;
	m_sName = other.m_sName;
	m_Color = other.m_Color;

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

CTextureOverride& Esp::CTextureOverride::operator=(const CTextureOverride& other)
{
	if (this == &other)
		return *this;

	m_bEnableZ = other.m_bEnableZ;
	m_iUid     = other.m_iUid;
	m_sName    = other.m_sName;

	UpdateColor(other.m_Color);

	return *this;
}

ImColor CTextureOverride::GetColor() const
{
	return m_Color;
}

CTextureOverride::~CTextureOverride()
{
	if (m_pTexture)
		m_pTexture->Release();
}
