#include "CStartWindow.h"

UI::CStartWindow::CStartWindow(LPDIRECT3DDEVICE9 pDevice, HMODULE  hModule, CBaseWindow* pAboutWindow, CBaseWindow* pPlayerListWindow, CBaseWindow* pSettingsWindow) : CBaseWindow(pDevice, hModule)
{
	m_pPlayerListWindow = pPlayerListWindow;
	m_pAboutWindow      = pAboutWindow;
	m_pSettingsWindow   = pSettingsWindow;

}
void UI::CStartWindow::Render()
{
	ImGui::Begin(xorstr("###Start"), NULL, m_iImGuiStyle | ImGuiWindowFlags_NoMove);
	{
		ImVec2 windowSize = ImGui::GetMainViewport()->Size;
		ImGui::SetWindowPos(ImVec2(0, windowSize.y - 373));
		ImGui::SetWindowSize(ImVec2(300, 342));

		if (ImGui::Button(xorstr("NETWORK"), ImVec2(100, 25)))
			m_pPlayerListWindow->Toggle();

		if (ImGui::Button(xorstr("SETTINGS"),    ImVec2(100, 25)))
			m_pSettingsWindow->Toggle();

		if (ImGui::Button(xorstr("ABOUT"),       ImVec2(100, 25)))
			m_pAboutWindow->Toggle();

		ImGui::End();
	}
}