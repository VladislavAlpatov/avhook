#include "../CSettingsWindow.h"
#include "../../../Globals/Settings.h"

void UI::CSettingsWindow::DrawMiscChild()
{
	ImGui::SetWindowSize(ImVec2(555, 400));
	const auto pSettings = &GlobalVars::g_AllSettings.m_MiscSettings;

	ImGui::Checkbox(xorstr("Bunny hop"), &GlobalVars::g_AllSettings.m_BunnyHopSettings.m_bActive);
	DrawToolTip(xorstr("Provide an automatic bunny hop.\n\nNote: Use to gain more speed than 250 hu/s."));

	ImGui::SliderInt(xorstr("Field of view"), &pSettings->m_iCustomFov, 1, 120);

	ImGui::BeginChild(xorstr("###Crosshair"), ImVec2(190, 200), true, m_iImGuiStyle);
	{

		const auto pCrosshairSettings = &GlobalVars::g_AllSettings.m_CrosshairSettings;
		ImGui::Text(xorstr("Crosshair"));
		ImGui::Checkbox(xorstr("Active"),  &pCrosshairSettings->m_bActive);
		ImGui::Checkbox(xorstr("Sensors"), &pCrosshairSettings->m_bDrawSensors)
			
			;
		ImGui::ColorEdit4(xorstr("Crosshair Color"), (float*)&pCrosshairSettings->m_Color,       ImGuiColorEditFlags_NoInputs);
		ImGui::ColorEdit4(xorstr("Speed Bar Color"), (float*)&pCrosshairSettings->m_SpeedBarCol, ImGuiColorEditFlags_NoInputs);


		ImGui::SliderInt(xorstr("Size"),     &pCrosshairSettings->m_iSize,     1, 20);
		ImGui::SliderInt(xorstr("Distance"), &pCrosshairSettings->m_iDistance, 1, 300);

		ImGui::EndChild();
	}
}