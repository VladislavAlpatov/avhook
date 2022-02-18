#pragma once

#include <Windows.h>
#include <vector>
#include <typeinfo>

#include "Windows/CAboutWindow.h"
#include "Windows/CSettingsWindow.h"
#include "Windows/CStartWindow.h"
#include "Windows/CTaskBarWindow.h"
#include "Windows/CNetWorkWindow.h"
#include "Windows/CRadarWindow.h"

#include "../Hacks/Esp/CBarsEsp.h"
#include "../Hacks/Esp/CBoxEsp.h"
#include "../Hacks/Esp/CLabelEsp.h"
#include "../Hacks/Esp/CSnapLinesEsp.h"

#include "Overlays/CBindListenerOverlay.h"

#include "../imgui/imgui_impl_win32.h"
#include "../imgui/imgui_impl_dx9.h"
#include "../imgui/misc/freetype/imgui_freetype.h"

#include "../DirctX/DX9ColorFix.h"
#include "SnowFlakes/SnowFlake.h"
#include "../Utils/Marker.h"

class COverlay
{
public:
	COverlay(LPDIRECT3DDEVICE9 pDevice, HMODULE hModule, SAllSettings* pSettings);
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

	SAllSettings* m_pAllSettings = nullptr;
	std::vector<Windows::CBaseWindow*> m_vecWindows;
	LPDIRECT3DDEVICE9 m_pDevice;
};