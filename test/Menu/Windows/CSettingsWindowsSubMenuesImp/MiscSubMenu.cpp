#include "../CSettingsWindow.h"
#include "../../../Globals/Settings.h"

void UI::CSettingsWindow::DrawMiscChild()
{
	ImGui::Checkbox(xorstr("Bunny hop"), &GlobalVars::g_AllSettings.m_BunnyHopSettings.m_bActive);
	DrawToolTip(xorstr("Provide an automatic bunny hop.\n\nNote: Use to gain more speed than 250 hu/s."));

	ImGui::SliderInt(xorstr("Field of view"), &GlobalVars::g_AllSettings.m_MiscSettings.m_iCustomFov, 1, 120);
}