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
		int     m_iUid;
		bool	m_bEnableZ = false;
		std::string m_sName;
		void UpdateColor(const ImColor& newColor);
		void OverrideColor();
		ImColor GetColor();
		~CTextureOverride();
	private:
		bool GenerateColoredTexture(IDirect3DTexture9** pTexture, const ImColor& color);
		ImColor            m_Color;
		IDirect3DTexture9* m_pTexture = NULL;
	};

}
