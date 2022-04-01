#include "CTaskBarWindow.h"
#include <time.h>
UI::CTaskBarWindow::CTaskBarWindow(LPDIRECT3DDEVICE9 pDevice, HMODULE  hModule, CBaseWindow* startWindow, Settings::MiscSettings* pMiscSettings) : CBaseWindow(pDevice, hModule)
{
	m_pStartWindow = startWindow;
	m_pMiscSetting = pMiscSettings;
	m_bForceShow = true;
}
void UI::CTaskBarWindow::Render()
{
	ImGui::Begin(xorstr("taskbar"), NULL, m_iImGuiStyle | ImGuiWindowFlags_NoMove);
	ImVec2 windowSize = ImGui::GetMainViewport()->Size;
	ImGui::SetWindowPos(ImVec2(0, windowSize.y - 32));
	ImGui::SetWindowSize(ImVec2(windowSize.x, 20));

	ImGui::SetCursorPos(ImVec2(3, 5));
	if (ImGui::Button(xorstr("START"), ImVec2(45, 23)))
		m_pStartWindow->Toggle();

	if (m_pMiscSetting->m_bShowTime)
	{
		ImGui::SetCursorPos(ImVec2(windowSize.x - 70, 7));
		ImGui::Text(GetLocalTime().c_str());
	}

	ImGui::End();
}
std::string UI::CTaskBarWindow::GetLocalTime()
{
	time_t now = time(NULL);
	tm  tstruct;
	char buf[80]; localtime_s(&tstruct, &now); strftime(buf, sizeof(buf), xorstr("%X"), &tstruct);
	return std::string(buf);
}