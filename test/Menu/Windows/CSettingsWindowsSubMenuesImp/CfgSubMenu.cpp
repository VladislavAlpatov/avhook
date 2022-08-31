#include "../CSettingsWindow.h"
#include "../../../Utils/CFGloader/CFGloader.h"
#include "../../../Globals/Settings.h"
#include <fmt/format.h>
#include <fstream>
#include "../../../imgui/imgui_internal.h"


void UI::CSettingsWindow::DrawCfgChild()
{
	ImGui::SetWindowSize(ImVec2(555, 450));
	
	ImGui::Text(xorstr("Manage configs & GUI style"));
	// Provide Cheat config dump
	ImGui::BeginChild(xorstr("###FeatureCfg"), ImVec2(180, 80), true, m_iImGuiStyle);
	{
		ImGui::Text(xorstr("Feature Config Section"));

		DrawInputTextWithTextOnBackGround(xorstr("###Fname"), xorstr("<Config name>"), (char*)GlobalVars::g_AllSettings.m_Name.c_str(), GlobalVars::g_AllSettings.m_Name.size());
		if (ImGui::Button(xorstr("Import###fi")))
		{
			CConfigLoader cfg(GlobalVars::g_AllSettings.m_Name.c_str(), &GlobalVars::g_AllSettings);

			if (cfg.LoadConfigFile(GlobalVars::g_AllSettings.m_Name.c_str()))
				m_pMessageLineList->Add(fmt::format(xorstr("Loaded settings config: \"{}\""), GlobalVars::g_AllSettings.m_Name.c_str()), 2000);
			else
				m_pMessageLineList->Add(fmt::format(xorstr("\"{}\" does not exist."), GlobalVars::g_AllSettings.m_Name.c_str()), 2000);

		}
		ImGui::SameLine();
		if (ImGui::Button(xorstr("Export###fb")))
		{
			if (!GlobalVars::g_AllSettings.m_Name.empty())
			{
				CConfigLoader cfgOnSave = CConfigLoader(GlobalVars::g_AllSettings.m_Name.c_str(), &GlobalVars::g_AllSettings);
				cfgOnSave.DumpConfigFile(GlobalVars::g_AllSettings.m_Name.c_str());
				m_pMessageLineList->Add(xorstr("Config successfully imported."), 2000);

			}
			else
			{
				m_pMessageLineList->Add(xorstr("Enter the name of the config!"), 2000, ImColor(255, 0, 0));
			}
		}
		ImGui::EndChild();
	}
	ImGui::BeginChild(xorstr("###VisualCfg"), ImVec2(180, 80), true, m_iImGuiStyle);
	{
		ImGui::Text(xorstr("Menu Config Section"));

		DrawInputTextWithTextOnBackGround(xorstr("###Vaname"), xorstr("<Config name>"), m_pMenuCfgName, 32);

		if (ImGui::Button(xorstr("Import###fin")))
		{
			if (m_pMenuCfgName[0] != NULL)
			{
				std::ifstream file(std::string(m_pMenuCfgName) + xorstr(".avmcfg"), std::ios::binary);

				if (file.is_open())
				{
					file.read((char*)ImGui::GetStyle().Colors, sizeof(ImGui::GetStyle().Colors));
					m_pMessageLineList->Add(fmt::format(xorstr("Loaded menu config: \"{}\""), m_pMenuCfgName), 2000);

				}
				else
				{
					m_pMessageLineList->Add(fmt::format(xorstr("\"{}.avmcfg\" does not exist."), m_pMenuCfgName), 2000);
				}
			}
			else
			{
				m_pMessageLineList->Add(xorstr("Enter the file name."), 2000, ImColor(255, 0, 0));
			}
		}
		ImGui::SameLine();
		if (ImGui::Button(xorstr("Export###fex")))
		{
			if (m_pMenuCfgName[0] != NULL)
			{

				std::ofstream file(std::string(m_pMenuCfgName) + xorstr(".avmcfg"), std::ios::binary);
				file.write((const char*)ImGui::GetStyle().Colors, sizeof(ImGui::GetStyle().Colors));
				file.close();
				m_pMessageLineList->Add(xorstr("Config successfully exported."), 2000, ImColor(0, 255, 0));
			}
			else
			{
				m_pMessageLineList->Add(xorstr("Enter the file name."), 2000, ImColor(255, 0, 0));
			}
		}
		ImGui::EndChild();
	}

	ImGui::BeginChild(xorstr("###MiscCfg"), ImVec2(180, 112), true, m_iImGuiStyle);
	{
		ImGui::Text(xorstr("Misc Settings"));

		ImGui::Checkbox(xorstr("Snow"), &GlobalVars::g_AllSettings.m_MiscSettings.m_bSnowFlakes);
		DrawToolTip(xorstr("Draw snowflakes while menu is opened."));

		ImGui::Checkbox(xorstr("Wallpaper"), &GlobalVars::g_AllSettings.m_MiscSettings.m_bWallPaper);

		ImGui::Checkbox(xorstr("Local Time"), &GlobalVars::g_AllSettings.m_MiscSettings.m_bShowTime);
		DrawToolTip(xorstr("Show local time."));

		ImGui::EndChild();
	}
	ImGui::SameLine();
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 84 * 2);
	auto guiColorTheme = ImGui::GetStyle().Colors;

	ImGui::BeginChild(xorstr("###MenuColors"), ImVec2(170, 360), true, m_iImGuiStyle);
	{
		ImGui::Text(xorstr("UI Colors"));
		ImGui::ColorEdit4(xorstr("###1"), (float*)&guiColorTheme[ImGuiCol_Text], ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Text(xorstr("Text"));

		ImGui::ColorEdit4(xorstr("###2"), (float*)&guiColorTheme[ImGuiCol_TextDisabled], ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Text(xorstr("Text (Invactive)"));

		ImGui::ColorEdit4(xorstr("###3"), (float*)&guiColorTheme[ImGuiCol_WindowBg], ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Text(xorstr("Background"));

		ImGui::ColorEdit4(xorstr("###4"), (float*)&guiColorTheme[ImGuiCol_ChildBg], ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Text(xorstr("Background child"));

		ImGui::ColorEdit4(xorstr("###5"), (float*)&guiColorTheme[ImGuiCol_PopupBg], ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Text(xorstr("Background popup"));

		ImGui::ColorEdit4(xorstr("###6"), (float*)&guiColorTheme[ImGuiCol_Border], ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Text(xorstr("Border"));

		ImGui::ColorEdit4(xorstr("###7"), (float*)&guiColorTheme[ImGuiCol_BorderShadow], ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Text(xorstr("Border (Shadow)"));

		ImGui::ColorEdit4(xorstr("###8"), (float*)&guiColorTheme[ImGuiCol_FrameBg], ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Text(xorstr("Frame"));

		ImGui::ColorEdit4(xorstr("###9"), (float*)&guiColorTheme[ImGuiCol_FrameBgHovered], ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Text(xorstr("Frame (hovered)"));

		ImGui::ColorEdit4(xorstr("###10"), (float*)(&guiColorTheme[ImGuiCol_FrameBgActive]), ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Text(xorstr("Frame (Active)"));

		ImGui::ColorEdit4(xorstr("###Header"), (float*)(&guiColorTheme[ImGuiCol_Header]), ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Text(xorstr("Header"));

		ImGui::ColorEdit4(xorstr("###HeaderActive"), (float*)(&guiColorTheme[ImGuiCol_HeaderActive]), ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Text(xorstr("Header (Active)"));

		ImGui::ColorEdit4(xorstr("###HeaderActiveHovered"), (float*)(&guiColorTheme[ImGuiCol_HeaderHovered]), ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Text(xorstr("Header (Hovered)"));


		ImGui::EndChild();
	}

	ImGui::SameLine();
	ImGui::BeginChild(xorstr("###MenuColors2"), ImVec2(170, 360), true, m_iImGuiStyle);
	{
		ImGui::Text(xorstr("UI Colors 2"));
		ImGui::ColorEdit4(xorstr("###11"), reinterpret_cast<float*>(&guiColorTheme[ImGuiCol_CheckMark]), ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Text(xorstr("Check mark"));

		ImGui::ColorEdit4(xorstr("###12"), reinterpret_cast<float*>(&guiColorTheme[ImGuiCol_Button]), ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Text(xorstr("Button"));

		ImGui::ColorEdit4(xorstr("###13"), reinterpret_cast<float*>(&guiColorTheme[ImGuiCol_ButtonHovered]), ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Text(xorstr("Button (Hovered)"));

		ImGui::ColorEdit4(xorstr("###18"), reinterpret_cast<float*>(&guiColorTheme[ImGuiCol_ButtonActive]), ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Text(xorstr("Button (Active)"));

		ImGui::ColorEdit4(xorstr("###14"), reinterpret_cast<float*>(&guiColorTheme[ImGuiCol_TextSelectedBg]), ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Text(xorstr("Text (Selected)"));

		ImGui::ColorEdit4(xorstr("##21"), reinterpret_cast<float*>(&guiColorTheme[ImGuiCol_SliderGrab]), ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Text(xorstr("Slider grab"));

		ImGui::ColorEdit4(xorstr("##22"), reinterpret_cast<float*>(&guiColorTheme[ImGuiCol_SliderGrabActive]), ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Text(xorstr("Slider grab (Active)"));

		ImGui::ColorEdit4(xorstr("##ScrollActive"), reinterpret_cast<float*>(&guiColorTheme[ImGuiCol_ScrollbarGrabActive]), ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Text(xorstr("Scroll bar (Active)"));

		ImGui::ColorEdit4(xorstr("##Scroll"), reinterpret_cast<float*>(&guiColorTheme[ImGuiCol_ScrollbarGrab]), ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Text(xorstr("Scroll bar"));

		ImGui::EndChild();
	}
}
