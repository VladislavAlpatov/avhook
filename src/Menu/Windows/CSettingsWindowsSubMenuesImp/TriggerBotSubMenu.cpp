#include "../CSettingsWindow.h"
#include "../../../Globals/Settings.h"

void UI::CSettingsWindow::DrawTriggerBotChild()
{
	ImGui::SetWindowSize(ImVec2(555, 400));

	ImGui::Checkbox(xorstr("Active"), &GlobalVars::g_AllSettings.m_TriggerBotSettings.m_bActive);

}
