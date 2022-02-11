#include "COverlay.h"


COverlay::COverlay(LPDIRECT3DDEVICE9 pDevice, HMODULE hModule, SAllSettings* pSettings)
{
	m_pDevice = pDevice;
	m_pAllSettings = pSettings;
	ImGui::CreateContext();
	ImGui_ImplWin32_Init(FindWindow(NULL, WINDOW_NAME));
	ImGui_ImplDX9_Init(m_pDevice);

	ImGui::GetStyle().AntiAliasedLinesUseTex = false;
	auto io = ImGui::GetIO();
	ImFontConfig cfg;
	cfg.FontBuilderFlags |= ImGuiFreeTypeBuilderFlags_Monochrome | ImGuiFreeTypeBuilderFlags_MonoHinting;

	POLY_MARKER

	m_pFontEsp  = io.Fonts->AddFontFromFileTTF(xorstr("C:\\Windows\\Fonts\\verdanab.ttf"), 13.f, &cfg);

	auto& style = ImGui::GetStyle();
	auto& theme = style.Colors;

	style.FrameBorderSize = 1;
	style.AntiAliasedLinesUseTex = false;
	style.AntiAliasedLines       = false;
	style.AntiAliasedFill        = false;

	theme[ImGuiCol_WindowBg] = ImColor(24, 31, 35, 255);
	theme[ImGuiCol_Button] = ImVec4(1.f, 0.372f, 0.372f, 1.f);
	theme[ImGuiCol_Tab] = ImVec4(1.f, 0.372f, 0.372f, 1.f);
	theme[ImGuiCol_SeparatorActive] = ImVec4(1.f, 0.372f, 0.372f, 1.f);
	theme[ImGuiCol_Border] = ImVec4(1.f, 0.372f, 0.372f, 1.f);
	theme[ImGuiCol_Text] = ImVec4(1.f, 1.f, 1.f, 1.f);
	theme[ImGuiCol_ButtonActive] = ImVec4(1.f, 0.57f, 0.57f, 1.f);
	theme[ImGuiCol_ButtonHovered] = ImVec4(1.f, 0.4f, 0.4f, 1.f);
	theme[ImGuiCol_CheckMark] = ImVec4(1.f, 0.372f, 0.372f, 1.f);
	theme[ImGuiCol_TextSelectedBg] = ImVec4(1.f, 0.372f, 0.372f, 1.f);
	theme[ImGuiCol_FrameBg] = ImVec4(0.31f, 0.31f, 0.31f, 1.f);
	theme[ImGuiCol_FrameBgActive] = ImVec4(1.f, 0.57f, 0.57f, 1.f);
	theme[ImGuiCol_FrameBgHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.f);
	theme[ImGuiCol_PopupBg] = ImColor(24, 31, 35, 255);
	theme[ImGuiCol_ScrollbarBg] = ImVec4(1.f, 0.372f, 0.372f, 0.f);
	theme[ImGuiCol_ScrollbarGrab] = ImVec4(1.f, 0.372f, 0.372f, 1.f);
	theme[ImGuiCol_SliderGrab] = ImVec4(1.f, 0.372f, 0.372f, 1.f);
	theme[ImGuiCol_SliderGrabActive] = ImVec4(1.f, 0.372f, 0.372f, 1.f);
	theme[ImGuiCol_TabHovered] = ImVec4(1.f, 0.57f, 0.57f, 1.f);
	theme[ImGuiCol_TabActive] = ImVec4(1.f, 0.372f, 0.372f, 1.f);


	m_vecWindows.push_back(new CAboutWindow(m_pDevice, hModule));
	m_vecWindows.push_back(new CSettingsWindow(m_pDevice, hModule, pSettings, &m_bShowKeyBindDialog));
	m_vecWindows.push_back(new CNetWorkWindow(m_pDevice, hModule));
	m_vecWindows.push_back(new CStartWindow(m_pDevice, hModule, m_vecWindows[0], m_vecWindows[2], m_vecWindows[1]));
	m_vecWindows.push_back(new CTaskBarWindow(pDevice, hModule, m_vecWindows[3], &pSettings->m_MiscSettings));

	m_vecEspPayload = {
		new CBoxEsp(&GlobalVars::settings.m_BoxEspSettings), 
		new CBarsEsp(&GlobalVars::settings.m_BarEspSettings),
		new CLabelEsp(&GlobalVars::settings.m_LabelEspSettings), 
		new CSnapLinesEsp(&GlobalVars::settings.m_SnapLinesSettings)
	};

	for (int i = 0; i < 100; ++i)
	{
		m_vecSnow.push_back(SnowFlake(ImVec2(0, 2), 1920));
	}
}

void COverlay::Render()
{
	POLY_MARKER;

	DX9ColorFix color_fix(m_pDevice);
	color_fix.RemoveColorFilter();

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	auto pDrawList = ImGui::GetBackgroundDrawList();

	POLY_MARKER

	if (GlobalVars::pIEngineClient->IsInGame() and GlobalVars::client->pLocalPlayer != nullptr)
	{

		for (int i = 1; i < 33; ++i)
		{
			auto pEntity = GlobalVars::pIEntityList->GetClientEntity(i);

			if (pEntity == nullptr or !pEntity->IsAlive() or pEntity->m_iTeamNum == GlobalVars::client->pLocalPlayer->m_iTeamNum or pEntity->m_bDormant)
				continue;

			for (auto pEsp : m_vecEspPayload)
			{
				if (pEsp->isActive())
					pEsp->RenderAt(pEntity);
			}
			
		}
	}

	if (m_bShowUI)
	{

		POLY_MARKER

		auto windowSize = ImGui::GetMainViewport()->Size;

		pDrawList->AddRectFilled(ImVec2(), windowSize, ImColor(0, 0, 0, 90));

		for (auto window : m_vecWindows)
		{
			window->Show();
		}

#ifdef DEV_BUILD
		drawList->AddText(ImVec2(), ImColor(255, 255, 255), xorstr("DEVELOPER BUILD"));
#endif // DEV_BUILD

		if (m_pAllSettings->m_MiscSettings.m_bSnowFlakes)
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

	if (m_bShowUI or GlobalVars::pIEngineClient->IsInGame())
	{
		m_pAllSettings->m_RadarSettings.m_bDrawBorders = m_bShowUI;
		CRadarWindow(&m_pAllSettings->m_RadarSettings).Show();
	}

	if (m_bShowKeyBindDialog)
	{
		CBindListenerOverlay(m_pFontEsp).Show();
	}

	POLY_MARKER

	ImGui::EndFrame();
	color_fix.RestoreRenderState();

	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	color_fix.RestoreColorFilter();
}
bool COverlay::IsShowUI()
{
	return m_bShowUI;
}
void COverlay::ToggleUI()
{
	m_bShowUI = !m_bShowUI;
}
void COverlay::Detach()
{
	for (auto pWindow : m_vecWindows)
	{
		delete pWindow;
	}
	for (auto pEsp : m_vecEspPayload)
	{
		delete pEsp;
	}
}