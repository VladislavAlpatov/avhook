#pragma once

#include <Windows.h>
#include <vector>

#include <d3d9.h>

#include "../Hacks/Esp/CBaseEsp.h"
#include "Windows/CBaseWindow.h"

#include "SnowFlakes/SnowFlake.h"
#include "MessageLine/CMessageLine.h"

namespace UI
{
	class COverlay
	{
	public:

		COverlay(LPDIRECT3DDEVICE9 pDevice);
		~COverlay();
		void Render();
		bool IsShowUI();
		void ToggleUI();
	private:
		std::vector<SnowFlake> m_vecSnow;
		std::vector<std::shared_ptr<Esp::CUIEsp>> m_vecEspPayload;
		PDIRECT3DTEXTURE9 m_pWallpaper = NULL;
		std::unique_ptr<ImFont> m_pFontEsp;
		bool    m_bShowUI = false;
		bool    m_bShowKeyBindDialog = false;

		std::vector<std::shared_ptr<UI::CBaseWindow>> m_vecWindows;
		UI::CMessageLineList	      m_MessageLineList;

		LPDIRECT3DDEVICE9 m_pDevice;
	};
}