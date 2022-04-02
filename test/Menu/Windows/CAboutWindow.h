#pragma once
#include "CBaseWindow.h"

namespace UI
{
	class CAboutWindow : public CBaseWindow
	{
	public:
		CAboutWindow(LPDIRECT3DDEVICE9 pDevice, HMODULE  hModule);
		virtual void Render();
		PDIRECT3DTEXTURE9 m_pTexureCheatLogo = nullptr;

		virtual ~CAboutWindow();
	};
}