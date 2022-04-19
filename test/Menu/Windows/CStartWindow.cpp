#include "CStartWindow.h"

UI::CStartWindow::CStartWindow(LPDIRECT3DDEVICE9 pDevice, HMODULE  hModule, CBaseWindow* pAboutWindow, CBaseWindow* pPlayerListWindow, CBaseWindow* pSettingsWindow) : CBaseWindow(pDevice, hModule)
{
	m_bForceShow        = true;
	m_pPlayerListWindow = pPlayerListWindow;
	m_pAboutWindow      = pAboutWindow;
	m_pSettingsWindow   = pSettingsWindow;

}
void UI::CStartWindow::Render()
{
	ImGui::Begin(xorstr("###Start"), NULL, m_iImGuiStyle | ImGuiWindowFlags_NoMove);
	{
		ImVec2 screenSize = ImGui::GetMainViewport()->Size;
		ImGui::SetWindowPos(ImVec2( (screenSize.x - ImGui::GetWindowWidth()) / 2.f , screenSize.y - ImGui::GetWindowHeight()));

		if (ImGui::Button(xorstr("NETWORK"), ImVec2(100, 25)))
			m_pPlayerListWindow->Toggle();
		ImGui::SameLine();
		if (ImGui::Button(xorstr("SETTINGS"),    ImVec2(100, 25)))
			m_pSettingsWindow->Toggle();
		ImGui::SameLine();
		if (ImGui::Button(xorstr("ABOUT"),       ImVec2(100, 25)))
			m_pAboutWindow->Toggle();

		ImGui::End();
	}
}