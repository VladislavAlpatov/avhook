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
#include "../SDK/ClientBase.h"

UI::COverlay::COverlay(LPDIRECT3DDEVICE9 pDevice)
{
	POLY_MARKER;
	m_pDevice      = pDevice;
	ImGui::CreateContext();
	ImGui_ImplWin32_Init(FindWindowA(nullptr, WINDOW_NAME));
	ImGui_ImplDX9_Init(m_pDevice);

	const auto& io = ImGui::GetIO();
	
	ImFontConfig cfg;
	cfg.FontBuilderFlags |= ImGuiFreeTypeBuilderFlags_Monochrome | ImGuiFreeTypeBuilderFlags_MonoHinting;
	static ImWchar ranges[] = { 0x1, 0xFFFD, 0 };


	m_pFontEsp  = std::unique_ptr<ImFont>(io.Fonts->AddFontFromFileTTF(xorstr("C:\\Windows\\Fonts\\verdanab.ttf"), 13.f, &cfg, ranges));


	SetImGuiAVhookTheme();

	POLY_MARKER;

	m_vecWindows.push_back(std::make_shared<UI::CAboutWindow>(m_pDevice));
	m_vecWindows.push_back(std::make_shared<UI::CSettingsWindow>(m_pDevice, &m_MessageLineList, &m_bShowKeyBindDialog));
	m_vecWindows.push_back(std::make_shared<UI::CNetWorkWindow>(m_pDevice,  &m_MessageLineList));
	m_vecWindows.push_back(std::make_shared<UI::CConsoleWindow>(m_pDevice));

	const std::vector dockWindows= { m_vecWindows[0], m_vecWindows[1], m_vecWindows[2], m_vecWindows[3] };

	m_vecWindows.push_back(std::make_shared<UI::CDockWindow>(m_pDevice, dockWindows));
	m_vecWindows.push_back(std::make_shared<UI::CTaskBarWindow>(pDevice));

	POLY_MARKER;

	m_vecEspPayload = {
		std::make_shared<Esp::CBoxEsp>(&GlobalVars::g_AllSettings.m_BoxEspSettings),
		std::make_shared<Esp::CBarsEsp>(&GlobalVars::g_AllSettings.m_BarEspSettings),
		std::make_shared<Esp::CLabelEsp>(&GlobalVars::g_AllSettings.m_LabelEspSettings),
		std::make_shared<Esp::CSnapLinesEsp>(&GlobalVars::g_AllSettings.m_SnapLinesSettings)
	};

	for (int i = 0; i < 100; ++i)
	{
		m_vecSnow.emplace_back(ImVec2(0, 2), 1920);
	}
	
	D3DXCreateTextureFromFileA(m_pDevice, GetPathToCurrentWallpaper().c_str(), &m_pWallpaper);

	POLY_MARKER;

#ifdef CLOUD_SUPPORT
	m_MessageLineList.Add(fmt::format(xorstr("{}, the systems are yours. \nWe are stronger united."), WebApi::CAVHookServerApi().GetUserInfo().m_sName ), 3000);
#else
	m_MessageLineList.Add(xorstr("nullifiedvlad, the systems are yours. \nWe are stronger united."), 3000);
#endif

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

	if (auto pLocalPlayer = SSDK::ClientBase::GetLocalPlayer(); GlobalVars::g_pIEngineClient->IsInGame() and pLocalPlayer)
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
				return pLocalPlayer->CalcDistanceToEntity(first) > pLocalPlayer->CalcDistanceToEntity(second);
			});
		DrawPlayerEsp(validEntities);

	}

	if (m_bShowUI)
	{
		POLY_MARKER;
		DrawMenuBackground();
		ShowWindows();

		if (GlobalVars::g_AllSettings.m_MiscSettings.m_bSnowFlakes)
			DrawSnowflakes();
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
bool UI::COverlay::IsShowUI() const
{
	return m_bShowUI;
}
void UI::COverlay::ToggleUI()
{
	m_bShowUI = !m_bShowUI;
}

void UI::COverlay::SetImGuiAVhookTheme()
{
	auto& style = ImGui::GetStyle();
	auto& theme = style.Colors;

	style.FrameBorderSize = 1;
	style.AntiAliasedLinesUseTex = false;
	style.AntiAliasedLines = false;
	style.AntiAliasedFill = true;
	style.ScrollbarRounding = 0.f;
	style.WindowMinSize = ImVec2(10, 10);

	POLY_MARKER;

	theme[ImGuiCol_Text] = ImColor(255, 255, 255);
	theme[ImGuiCol_TextDisabled] = ImColor(199, 199, 199);
	theme[ImGuiCol_WindowBg] = ImColor(19, 19, 19);
	theme[ImGuiCol_ChildBg] = ImColor();
	theme[ImGuiCol_PopupBg] = ImColor(19, 19, 19);
	theme[ImGuiCol_Border] = ImColor(255, 95, 95);
	theme[ImGuiCol_BorderShadow] = ImColor();
	theme[ImGuiCol_FrameBg] = ImColor();
	theme[ImGuiCol_FrameBgHovered] = ImColor(255, 102, 102, 90);
	theme[ImGuiCol_FrameBgActive] = ImColor(255, 255, 255, 90);
	theme[ImGuiCol_Header] = ImColor(255, 95, 95);
	theme[ImGuiCol_HeaderActive] = ImColor(255, 255, 255, 90);
	theme[ImGuiCol_HeaderHovered] = ImColor(255, 102, 102, 90);
	theme[ImGuiCol_CheckMark] = ImColor(255, 95, 95);
	theme[ImGuiCol_Button] = ImColor();
	theme[ImGuiCol_ButtonHovered] = ImColor(255, 102, 102, 90);
	theme[ImGuiCol_ButtonActive] = ImColor(255, 255, 255, 90);
	theme[ImGuiCol_TextSelectedBg] = ImColor(255, 95, 95);
	theme[ImGuiCol_SliderGrab] = ImColor(255, 95, 95);
	theme[ImGuiCol_SliderGrabActive] = ImColor(255, 255, 255, 90);
	theme[ImGuiCol_ScrollbarGrabActive] = ImColor(255, 255, 255, 90);
	theme[ImGuiCol_ScrollbarGrab] = ImColor(255, 95, 95);
}

void UI::COverlay::DrawMenuBackground() const
{
	const auto windowSize = ImGui::GetMainViewport()->Size;
	const auto pDrawList        = ImGui::GetBackgroundDrawList();

	if (GlobalVars::g_AllSettings.m_MiscSettings.m_bWallPaper)
	{
		pDrawList->AddImage(m_pWallpaper, ImVec2(), ImGui::GetMainViewport()->Size);
		return;
	}

	pDrawList->AddRectFilled(ImVec2(), windowSize, ImColor(0, 0, 0, 90));

}

void UI::COverlay::DrawSnowflakes()
{

	const auto windowSize = ImGui::GetMainViewport()->Size;
	const auto pDrawList = ImGui::GetBackgroundDrawList();

	for (auto& snowflake : m_vecSnow)
	{
		auto vecOrigin = snowflake.GetOrigin();

		if (vecOrigin.y > 0)
			pDrawList->AddText(vecOrigin, ImColor(255, 255, 255), xorstr("*"));

		snowflake.Update();
		if (vecOrigin.x > windowSize.x or vecOrigin.y > 150)
			snowflake.RegenerateOrigin();
	}
}

void UI::COverlay::ShowWindows() const
{
	for (const auto& window : m_vecWindows)
		window->Show();
}

void UI::COverlay::DrawPlayerEsp(const std::vector<SSDK::CBaseEntity*>& entities) const
{
	for (const auto& pEntity : entities)
		for (const auto& pEsp : m_vecEspPayload)
			if (pEsp->isActive())
				pEsp->RenderAt(pEntity);
}

std::string UI::COverlay::GetPathToCurrentWallpaper() const
{
	DWORD nameBufferSize = MAX_PATH;
	const auto pNameBuffer = std::unique_ptr<char[]>(new char[nameBufferSize]);
	GetUserNameA(pNameBuffer.get(), &nameBufferSize);


	return fmt::format(xorstr("C:\\Users\\{}\\AppData\\Roaming\\Microsoft\\Windows\\Themes\\TranscodedWallpaper"), pNameBuffer.get());
}
