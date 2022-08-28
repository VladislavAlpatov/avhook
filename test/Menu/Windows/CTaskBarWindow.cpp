#include "CTaskBarWindow.h"
#include <sstream>
#include "../../Globals/Settings.h"
#include "../../Utils/Marker.h"

UI::CTaskBarWindow::CTaskBarWindow(LPDIRECT3DDEVICE9 pDevice) : CBaseWindow(pDevice)
{
	POLY_MARKER;
	m_bForceShow = true;
}
void UI::CTaskBarWindow::Render()
{
	POLY_MARKER;
	ImGui::Begin(xorstr("taskbar"), NULL, m_iImGuiStyle | ImGuiWindowFlags_NoMove);
	{
		ImVec2 screenSize = ImGui::GetMainViewport()->Size;
		ImGui::SetWindowPos(ImVec2(0, 0));
		ImGui::SetWindowSize(ImVec2(screenSize.x, 20));

		ImGui::PushFont(m_pFontMediumBold.get());

		ImGui::SetCursorPosY(2);
		DrawTextCentered(xorstr("AVhook Project"));
		ImGui::PopFont();

		if (GlobalVars::g_AllSettings.m_MiscSettings.m_bShowTime)
		{
			std::string time = GetLocalTime();
			ImGui::PushFont(m_pFontMediumBold.get());
			ImGui::SetCursorPos(ImVec2(screenSize.x - ImGui::CalcTextSize(time.c_str()).x - 5, 2));
			ImGui::Text(time.c_str());
			ImGui::PopFont();
		}


		ImGui::End();
	}
}
std::string UI::CTaskBarWindow::GetLocalTime()
{
	POLY_MARKER;
	auto t  = time(nullptr);
	tm tm;

	localtime_s(&tm, &t);
	std::ostringstream oss;
	std::string timeString = "";
	oss << std::put_time(&tm, xorstr("%H:%M:%S"));
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