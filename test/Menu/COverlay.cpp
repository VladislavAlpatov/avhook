#pragma once

#include "COverlay.h"
#include "../Utils/Marker.h"

#include "Windows/CAboutWindow.h"
#include "Windows/CSettingsWindow.h"
#include "Windows/CDockWindow.h"
#include "Windows/CTaskBarWindow.h"
#include "Windows/CNetWorkWindow.h"
#include "Windows/CRadarWindow.h"
#include "Windows/CConsoleWindow.h"


#include "../Hacks/Esp/CBarsEsp.h"
#include "../Hacks/Esp/CBoxEsp.h"
#include "../Hacks/Esp/CLabelEsp.h"
#include "../Hacks/Esp/CSnapLinesEsp.h"

#include "../imgui/imgui_impl_win32.h"
#include "../imgui/imgui_impl_dx9.h"
#include "../imgui/misc/freetype/imgui_freetype.h"

#include "../DirectX/DX9ColorFix.h"

#include "Overlays/CBindListenerOverlay.h"
#include "Overlays/CCrosshairOverlay.h"


#include <d3dx9.h>
#include <fmt/format.h>
#include "../Web/CAVhookServerApi.h"
#include "../Globals/Settings.h"
#include "../Globals/Interfaces.h"
#include "../imgui/imgui_internal.h"

std::string GetCurrentWindowsUserName()
{
	DWORD buffSize = MAX_PATH;
	auto buffer = std::unique_ptr<char[]>(new char[buffSize]);
	GetUserNameA(buffer.get(), &buffSize);
	
	return std::string(buffer.get());
}

UI::COverlay::COverlay(LPDIRECT3DDEVICE9 pDevice)
{
	POLY_MARKER;
	m_pDevice      = pDevice;
	ImGui::CreateContext();
	ImGui_ImplWin32_Init(FindWindowA(NULL, WINDOW_NAME));
	ImGui_ImplDX9_Init(m_pDevice);

	ImGui::GetStyle().AntiAliasedLinesUseTex = false;
	auto& io = ImGui::GetIO();
	
	ImFontConfig cfg;
	cfg.FontBuilderFlags |= ImGuiFreeTypeBuilderFlags_Monochrome | ImGuiFreeTypeBuilderFlags_MonoHinting;
	static ImWchar ranges[] = { 0x1, 0xFFFD, 0 };


	m_pFontEsp  = std::unique_ptr<ImFont>(io.Fonts->AddFontFromFileTTF(xorstr("C:\\Windows\\Fonts\\verdanab.ttf"), 13.f, &cfg, ranges));
	auto& style = ImGui::GetStyle();
	auto& theme = style.Colors;

	style.FrameBorderSize         = 1;
	style.AntiAliasedLinesUseTex = false;
	style.AntiAliasedLines       = false;
	style.AntiAliasedFill        = true;
	style.ScrollbarRounding      = 0.f;
	style.WindowMinSize          = ImVec2(10, 10);

	POLY_MARKER;
	
	theme[ImGuiCol_Text]                     = ImColor(255, 255, 255);
	theme[ImGuiCol_TextDisabled]             = ImColor(199, 199, 199);
	theme[ImGuiCol_WindowBg]				 = ImColor(19, 19, 19);
	theme[ImGuiCol_ChildBg]                  = ImColor();
	theme[ImGuiCol_PopupBg]			         = ImColor(19, 19, 19);
	theme[ImGuiCol_Border]			         = ImColor(255, 95, 95);
	theme[ImGuiCol_BorderShadow]	         = ImColor();
	theme[ImGuiCol_FrameBg]                  = ImColor();
	theme[ImGuiCol_FrameBgHovered]		     = ImColor(255,102,102, 90);
	theme[ImGuiCol_FrameBgActive]            = ImColor(255, 255, 255, 90);
	theme[ImGuiCol_Header]			         = ImColor(255, 95, 95);
	theme[ImGuiCol_HeaderActive]             = ImColor(255, 255, 255, 90);
	theme[ImGuiCol_HeaderHovered]            = ImColor(255, 102, 102, 90);
	theme[ImGuiCol_CheckMark]			     = ImColor(255, 95, 95);
	theme[ImGuiCol_Button]		             = ImColor();
	theme[ImGuiCol_ButtonHovered]	         = ImColor(255, 102, 102, 90);
	theme[ImGuiCol_ButtonActive]			 = ImColor(255, 255, 255, 90);
	theme[ImGuiCol_TextSelectedBg]           = ImColor(255, 95, 95);
	theme[ImGuiCol_SliderGrab]		         = ImColor(255, 95, 95);
	theme[ImGuiCol_SliderGrabActive]		 = ImColor(255, 255, 255, 90);
	theme[ImGuiCol_ScrollbarGrabActive]		 = ImColor(255, 255, 255, 90);
	theme[ImGuiCol_ScrollbarGrab]		     = ImColor(255, 95, 95);

	POLY_MARKER;

	m_vecWindows.push_back(std::shared_ptr<UI::CBaseWindow>(new UI::CAboutWindow(m_pDevice)));
	m_vecWindows.push_back(std::shared_ptr<UI::CBaseWindow>(new UI::CSettingsWindow(m_pDevice, &m_MessageLineList, &m_bShowKeyBindDialog)));
	m_vecWindows.push_back(std::shared_ptr<UI::CBaseWindow>(new UI::CNetWorkWindow(m_pDevice,  &m_MessageLineList)));
	m_vecWindows.push_back(std::shared_ptr<UI::CBaseWindow>(new UI::CConsoleWindow(m_pDevice)));
	m_vecWindows.push_back(std::shared_ptr<UI::CBaseWindow>(new UI::CDockWindow(m_pDevice, {m_vecWindows[0], m_vecWindows[1], m_vecWindows[2], m_vecWindows[3] })));
	m_vecWindows.push_back(std::shared_ptr<UI::CBaseWindow>(new UI::CTaskBarWindow(pDevice)));

	POLY_MARKER;

	m_vecEspPayload = {
		std::shared_ptr<Esp::CUIEsp>(new Esp::CBoxEsp(&GlobalVars::g_AllSettings.m_BoxEspSettings)), 
		std::shared_ptr<Esp::CUIEsp>(new Esp::CBarsEsp(&GlobalVars::g_AllSettings.m_BarEspSettings)),
		std::shared_ptr<Esp::CUIEsp>(new Esp::CLabelEsp(&GlobalVars::g_AllSettings.m_LabelEspSettings)),
		std::shared_ptr<Esp::CUIEsp>(new Esp::CSnapLinesEsp(&GlobalVars::g_AllSettings.m_SnapLinesSettings))
	};

	for (int i = 0; i < 100; ++i)
	{
		m_vecSnow.push_back(SnowFlake(ImVec2(0, 2), 1920));
	}


	std::string pathToWallpaper = fmt::format(xorstr("C:\\Users\\{}\\AppData\\Roaming\\Microsoft\\Windows\\Themes\\TranscodedWallpaper"), GetCurrentWindowsUserName());
	D3DXCreateTextureFromFileA(m_pDevice, pathToWallpaper.c_str(), &m_pWallpaper);

	POLY_MARKER;

	m_MessageLineList.Add(fmt::format(xorstr("{}, the systems are yours. \nWe are stronger united."), WebApi::CAVHookServerApi().GetUserInfo().m_sName ), 3000);
}

UI::COverlay::~COverlay()
{
	POLY_MARKER;

	if (m_pWallpaper)
		m_pWallpaper->Release();
}

void UI::COverlay::Render()
{
	POLY_MARKER;
	DX9ColorFix color_fix(m_pDevice);
	color_fix.RemoveColorFilter();

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	auto pDrawList    = ImGui::GetBackgroundDrawList();
	auto pLocalPlayer = SSDK::ClientBase::GetLocalPlayer();


	if (GlobalVars::g_pIEngineClient->IsInGame() and pLocalPlayer)
	{
		std::vector<SSDK::CBaseEntity*> validEntities;

		for (int i = 1; i < 33; ++i)
		{
			auto pEntity = GlobalVars::g_pIEntityList->GetClientEntity(i);

			if (!pEntity or !pEntity->IsAlive() or pEntity->m_iTeamNum == pLocalPlayer->m_iTeamNum or pEntity->m_bDormant)
				continue;

			validEntities.push_back(pEntity);
			
		}
		// sort by distance
		std::sort(validEntities.begin(), validEntities.end(),

			[pLocalPlayer](const SSDK::CBaseEntity* first,const SSDK::CBaseEntity* second)
			{
				return pLocalPlayer->CalcDistaceToEntity(first) > pLocalPlayer->CalcDistaceToEntity(second);
			});


		// Render Esp
		for (auto pEntity : validEntities)
		{
			for (auto pEsp : m_vecEspPayload)
			{
				if (pEsp->isActive())
					pEsp->RenderAt(pEntity);
			}
		}
	}

	if (m_bShowUI)
	{

		POLY_MARKER;

		auto windowSize = ImGui::GetMainViewport()->Size;

		if (GlobalVars::g_AllSettings.m_MiscSettings.m_bWallPaper)
			pDrawList->AddImage(m_pWallpaper, ImVec2(), ImGui::GetMainViewport()->Size);
		else
			pDrawList->AddRectFilled(ImVec2(), windowSize, ImColor(0, 0, 0, 90));

		for (auto window : m_vecWindows)
		{
			window->Show();
		}

		if (GlobalVars::g_AllSettings.m_MiscSettings.m_bSnowFlakes)
		{

			for (auto& snowflake : m_vecSnow)
			{
				auto sfOriging = snowflake.GetOrigin();

				if (sfOriging.y > 0)
					pDrawList->AddText(sfOriging, ImColor(255, 255, 255), xorstr("*"));

				snowflake.Update();
				if (sfOriging.x > windowSize.x or sfOriging.y > 150)
					snowflake.RegenerateOrigin();
			}
		}
	}
	m_MessageLineList.Render(ImVec2());

	if (m_bShowUI or GlobalVars::g_pIEngineClient->IsInGame())
	{
		GlobalVars::g_AllSettings.m_RadarSettings.m_bDrawBorders = m_bShowUI;
		UI::CRadarWindow(&GlobalVars::g_AllSettings.m_RadarSettings).Show();
	}

	if (m_bShowKeyBindDialog)
	{
		UI::CBindListenerOverlay(m_pFontEsp.get()).Show();
	}

	if (GlobalVars::g_AllSettings.m_CrosshairSettings.m_bActive and GlobalVars::g_pIEngineClient->IsInGame())
	{
		CCrosshairOverlay().Show();
	}

	POLY_MARKER;

	color_fix.RestoreRenderState();

	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	color_fix.RestoreColorFilter();
}
bool UI::COverlay::IsShowUI()
{
	return m_bShowUI;
}
void UI::COverlay::ToggleUI()
{
	m_bShowUI = !m_bShowUI;
}