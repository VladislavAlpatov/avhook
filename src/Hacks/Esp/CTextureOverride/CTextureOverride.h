#pragma once
#include "../../../imgui/imgui.h"
#include <string>
#include <d3d9.h>


namespace Esp
{
	class CTextureOverride
	{
	public:
		CTextureOverride(const int uid, const ImColor& col, const std::string& name, bool enableZ);

		CTextureOverride(const CTextureOverride& other);
		int     m_iUid;
		bool	m_bEnableZ = false;
		std::string m_sName;
		void UpdateColor(const ImColor& newColor);
		CTextureOverride& operator=(const CTextureOverride& other);
		ImColor GetColor() const;
		IDirect3DTexture9* m_pTexture = NULL;
		~CTextureOverride();
	private:
		bool GenerateColoredTexture(IDirect3DTexture9** pTexture, const ImColor& color);
		ImColor            m_Color;
	};

}
