#include "CTaskBarWindow.h"
#include <sstream>
#include "../../Globals/GlobalVars.h"


UI::CTaskBarWindow::CTaskBarWindow(LPDIRECT3DDEVICE9 pDevice, HMODULE  hModule) : CBaseWindow(pDevice, hModule)
{
	m_bForceShow = true;
}
void UI::CTaskBarWindow::Render()
{
	ImGui::Begin(xorstr("taskbar"), NULL, m_iImGuiStyle | ImGuiWindowFlags_NoMove);
	{
		ImVec2 screenSize = ImGui::GetMainViewport()->Size;
		ImGui::SetWindowPos(ImVec2(0, 0));
		ImGui::SetWindowSize(ImVec2(screenSize.x, 20));

		ImGui::PushFont(m_pFontMediumBold);

		ImGui::SetCursorPosY(2);
		DrawTextCentered("AVhook Project");
		ImGui::PopFont();

		if (GlobalVars::settings.m_MiscSettings.m_bShowTime)
		{
			std::string time = GetLocalTime();
			ImGui::PushFont(m_pFontMediumBold);
			ImGui::SetCursorPos(ImVec2(screenSize.x - ImGui::CalcTextSize(time.c_str()).x - 5, 2));
			ImGui::Text(time.c_str());
			ImGui::PopFont();
		}


		ImGui::End();
	}
}
std::string UI::CTaskBarWindow::GetLocalTime()
{
	auto t  = time(nullptr);
	tm tm;

	localtime_s(&tm, &t);
	std::ostringstream oss;
	std::string timeString = "";
	oss << std::put_time(&tm, "%H:%M:%S");
	return oss.str();
}

/*
ImGui::Begin(xorstr("taskbar"), NULL, m_iImGuiStyle | ImGuiWindowFlags_NoMove);
	ImVec2 windowSize = ImGui::GetMainViewport()->Size;
	ImGui::SetWindowSize(ImVec2(500, 40));
	ImGui::SetWindowPos(ImVec2( (windowSize.x - ImGui::GetWindowWidth()) / 2.f, windowSize.y - ImGui::GetWindowHeight()));

	ImGui::SetCursorPos(ImVec2(3, 5));
	if (ImGui::Button(xorstr("START"), ImVec2(45, 23)))
		m_pStartWindow->Toggle();

	if (m_pMiscSetting->m_bShowTime)
	{
		ImGui::SetCursorPos(ImVec2(windowSize.x - 70, 7));
		ImGui::Text(GetLocalTime().c_str());
	}

	ImGui::End();
*/