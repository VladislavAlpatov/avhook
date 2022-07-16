#include "../CSettingsWindow.h"
#include "../../../Globals/Settings.h"

void UI::CSettingsWindow::DrawMiscChild()
{
	ImGui::SetWindowSize(ImVec2(555, 400));

	ImGui::Checkbox(xorstr("Bunny hop"), &GlobalVars::g_AllSettings.m_BunnyHopSettings.m_bActive);
	DrawToolTip(xorstr("Provide an automatic bunny hop.\n\nNote: Use to gain more speed than 250 hu/s."));

	ImGui::SliderInt(xorstr("Field of view"), &GlobalVars::g_AllSettings.m_MiscSettings.m_iCustomFov, 1, 120);

	ImGui::BeginChild(xorstr("###Crosshair"), ImVec2(160, 160), true, m_iImGuiStyle);
	{
		ImGui::Text(xorstr("Crosshair"));
		ImGui::Checkbox(xorstr("Active"),  &GlobalVars::g_AllSettings.m_CrosshairSettings.m_bActive);
		ImGui::ColorEdit4(xorstr("Color"), (float*)&GlobalVars::g_AllSettings.m_CrosshairSettings.m_Color, ImGuiColorEditFlags_NoInputs);


		ImGui::SliderInt(xorstr("Size"),     &GlobalVars::g_AllSettings.m_CrosshairSettings.m_iSize, 1, 20);
		ImGui::SliderInt(xorstr("Distance"), &GlobalVars::g_AllSettings.m_CrosshairSettings.m_iDistance, 1, 300);

		ImGui::EndChild();
	}

}