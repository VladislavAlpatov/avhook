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
	ImGui::Begin(xorstr("taskbar"), nullptr, m_iImGuiStyle | ImGuiWindowFlags_NoMove);
	{
		const ImVec2 screenSize = ImGui::GetMainViewport()->Size;
		ImGui::SetWindowPos(ImVec2(0, 0));
		ImGui::SetWindowSize(ImVec2(screenSize.x, 20));

		ImGui::PushFont(m_pFontMediumBold.get());

		ImGui::SetCursorPosY(2);
		DrawTextCentered(xorstr("AVhook Project"));
		ImGui::PopFont();

		if (GlobalVars::g_AllSettings.m_MiscSettings.m_bShowTime)
		{
			const std::string time = GetLocalTime();
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
	const auto t  = time(nullptr);
	tm timeData;

	localtime_s(&timeData, &t);
	std::ostringstream oss;
	std::string        timeString;
	oss << std::put_time(&timeData, xorstr("%H:%M:%S"));
	return oss.str();
}