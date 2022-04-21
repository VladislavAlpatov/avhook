#pragma once

#include <Windows.h>
#include <vector>

#include <d3d9.h>

#include "../Hacks/Esp/CBaseEsp.h"
#include "Windows/CBaseWindow.h"

#include "SnowFlakes/SnowFlake.h"
#include "MessageLine/CMessageLine.h"

class COverlay
{
public:
	
	COverlay(LPDIRECT3DDEVICE9 pDevice, HMODULE hModule, Settings::CAllSettings* pSettings);
	void Render();
	bool IsShowUI();
	void ToggleUI();
	void Detach();
private:
	std::vector<SnowFlake> m_vecSnow;
	std::vector<Esp::CBaseEsp*> m_vecEspPayload;

	ImFont* m_pFontMenu;
	ImFont* m_pFontEsp;
	bool    m_bShowUI            = false;
	bool    m_bShowKeyBindDialog = false;

	Settings::CAllSettings*       m_pAllSettings = nullptr;
	std::vector<UI::CBaseWindow*> m_vecWindows;
	UI::CMessageLineList	      m_MessageLineList;

	LPDIRECT3DDEVICE9 m_pDevice;
};