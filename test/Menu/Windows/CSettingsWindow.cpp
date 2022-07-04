#pragma once

#include "CSettingsWindow.h"
#include "../../imgui/imgui_internal.h"
#include "../../Globals/Settings.h"
#include "../../Globals/Interfaces.h"

#include "../../Utils/CFGloader/CFGloader.h"
#include <fmt/format.h>
#include "../../RawData/Images.h"

#include <fstream>
#include <d3dx9.h>


UI::CSettingsWindow::CSettingsWindow(LPDIRECT3DDEVICE9 pDevice, CMessageLineList* pMessageLineList, bool* pShowKeyBinderDialog) : CBaseWindow(pDevice)
{
	m_pShowKeyBinderDialog  = pShowKeyBinderDialog;
	m_pMessageLineList      = pMessageLineList;
	m_BindListener          = Routines::CBindListener(&GlobalVars::g_AllSettings.m_AimBotSettings.m_iBindKey, m_pShowKeyBinderDialog);
	
	D3DXCreateTextureFromFileInMemory(m_pDevice, Images::SettingsIcon,  sizeof(Images::SettingsIcon),  &m_pTextureIcon);
	D3DXCreateTextureFromFileInMemory(m_pDevice, Images::AimbotIcon,    sizeof(Images::AimbotIcon),    &m_pTexureAimBotIcon);
	D3DXCreateTextureFromFileInMemory(m_pDevice, Images::EspIcon,       sizeof(Images::EspIcon),       &m_pTexureEspIcon);
	D3DXCreateTextureFromFileInMemory(m_pDevice, Images::AutoColorIcon, sizeof(Images::AutoColorIcon), &m_pTexureAtomaticColorIcon);
}
std::string UI::CSettingsWindow::VirtualKeyNumberToString(int keyNumber)
{
	switch (keyNumber)
	{
	case VK_LBUTTON:
		return xorstr("Left Mouse Button");
		break;
	case VK_RBUTTON:
		return xorstr("Right Mouse Button");
		break;

	case VK_XBUTTON1:
		return xorstr("Mouse4 Button");
		break;

	case VK_XBUTTON2:
		return xorstr("Mouse5 Button");
		break;

	}

	char name[32] = { 0 };
	UINT scanCode = MapVirtualKeyW(keyNumber, MAPVK_VK_TO_VSC);
	LONG lParamValue = (scanCode << 16);
	int result = GetKeyNameTextA(lParamValue, name, 32);

	return std::string(name);
}
void UI::CSettingsWindow::Render()
{
	ImGui::Begin(xorstr("###Setting"), NULL, m_iImGuiStyle);
	{
		ImGui::SetWindowSize(ImVec2(555, 252));
		DrawIconAndTittle(xorstr("AVhook"));
		DrawCloseWindowButton();

		const ImVec2 buttonSize = ImVec2(102, 30);
		
		if (ImGui::Button(xorstr("AIM BOT"), buttonSize))
			m_iTab = TAB::AimBot;

		ImGui::SameLine();
		if (ImGui::Button(xorstr("TRIGGER BOT"), buttonSize))
			m_iTab = TAB::TriggerBot;

		ImGui::SameLine();
		if (ImGui::Button(xorstr("VISUALS"), buttonSize))
			m_iTab = TAB::Visuals;

		ImGui::SameLine();
		if (ImGui::Button(xorstr("MISC"), buttonSize))
			m_iTab = TAB::Misc;
		ImGui::SameLine();
		if (ImGui::Button(xorstr("MENU/CFG"), buttonSize))
			m_iTab = TAB::Menu;

		switch (m_iTab)
		{
		case TAB::AimBot:
			DrawAimbotChild();
			break;
		case TAB::TriggerBot:
			break;
		case TAB::Visuals:
			DrawEspChild();
			break;
		case TAB::Misc:
			DrawMiscChild();
			break;
		case TAB::Menu:
			DrawCfgChild();
			break;
		default:
			break;
		}
		KeepWindowInSreenArea();
		ImGui::End();
	}
}
std::string UI::CSettingsWindow::GetAlias()
{
	return xorstr("Settings");
}
void UI::CSettingsWindow::DrawAimbotChild()
{
	ImGui::SetWindowSize(ImVec2(555, 400));
	static const char* hitboxes[]      = { "Head",   "Chest", "Pelvis" };
	static const char* priorities[]    = { "FoV",    "Distance" };
	static const char* hitboxFilters[] = { "Static", "Dynamic" };

	ImGui::Text(xorstr("Automatic Target Acquisition System"));

	ImGui::BeginChild(xorstr("###General"), ImVec2(230, 235), true, m_iImGuiStyle);
	{
		ImGui::PushItemWidth(112.f);
		ImGui::Combo(xorstr("Hit-Box"), &GlobalVars::g_AllSettings.m_AimBotSettings.m_iSelectedHitBox, hitboxes, IM_ARRAYSIZE(hitboxes));
		DrawToolTip(xorstr("Set target Hit-Box."));

		ImGui::Combo(xorstr("Priority"), &GlobalVars::g_AllSettings.m_AimBotSettings.m_iPriorityType, priorities, IM_ARRAYSIZE(priorities));
		DrawToolTip(xorstr("Defines the target priority.\n\nFOV: The enemy closest to the crosshair is chosen first.\nDistance : The enemy closest to you is chosen first."));

		ImGui::Combo(xorstr("Hitbox filter"), &GlobalVars::g_AllSettings.m_AimBotSettings.m_iHitBoxFilterMode, hitboxFilters, IM_ARRAYSIZE(hitboxFilters));
		DrawToolTip(xorstr("Static: Aimbot will only aim at the hitbox of the player that you have chosen yourself.\n\nDynamic: Aimbot will change the target hitbox depending on the opponent's health percentage."));

		ImGui::InputInt(xorstr("Health border"), &GlobalVars::g_AllSettings.m_AimBotSettings.m_iHealthBorder);
		ImGui::InputFloat(xorstr("FoV"), &GlobalVars::g_AllSettings.m_AimBotSettings.m_fFov);
		DrawToolTip(xorstr("Define the field of view.\n\nNote: Enemy will be force-ignore if\nhe not in selected fov.\nSet FoV to 360 to disable it."));

		if (GlobalVars::g_pClient->pLocalPlayer != nullptr and ImGui::IsItemHovered())
		{
			auto screenSize = ImGui::GetMainViewport()->Size;
			float fovScreenRatio = std::hypotf(screenSize.x, screenSize.y) / (float)GlobalVars::g_pClient->pLocalPlayer->m_iDefaultFOV / 2.f;

			ImGui::GetBackgroundDrawList()->AddCircle(screenSize / 2.f,
				fovScreenRatio * GlobalVars::g_AllSettings.m_AimBotSettings.m_fFov,
				(ImColor)ImGui::GetStyle().Colors[ImGuiCol_Border]);

		}
		
		ImGui::InputFloat(xorstr("Smooth Factor"), &GlobalVars::g_AllSettings.m_AimBotSettings.m_fSmooth);
		ImGui::PopItemWidth();
		DrawToolTip(xorstr("Make aimbot act more like human.\n\nNote: Set \"Smooth\" value to \"0\" if\nyou want to completely disable it."));

		ImGui::Checkbox(xorstr("Auto Recoil Control"), &GlobalVars::g_AllSettings.m_AimBotSettings.m_bRcsControle);
		DrawToolTip(xorstr("Provide automatic recoil control when aimbot\naimed on enemy."));

		ImGui::Checkbox(xorstr("Auto shoot"), &GlobalVars::g_AllSettings.m_AimBotSettings.m_bAutoShot);
		DrawToolTip(xorstr("Provide automatic shoot when aimbot\naimed on enemy."));

		ImGui::Checkbox(xorstr("Active"), &GlobalVars::g_AllSettings.m_AimBotSettings.m_bActive);
		ImGui::EndChild();
	}
	ImGui::SameLine();
	ImGui::BeginChild(xorstr("###Binds"), ImVec2(232, 55), true, m_iImGuiStyle);
	{
		ImGui::Checkbox(xorstr("Activate on key"), &GlobalVars::g_AllSettings.m_AimBotSettings.m_bOnKey);
		DrawToolTip(xorstr("Set AimBot avtivation key."));
		ImGui::SameLine();
		if (ImGui::Button(xorstr("Set Key")))
		{
			m_BindListener.Listen();
		}
		ImGui::Text(xorstr("Binded to: %s"), VirtualKeyNumberToString(GlobalVars::g_AllSettings.m_AimBotSettings.m_iBindKey).c_str());

		ImGui::EndChild();
	}
}

void UI::CSettingsWindow::DrawEspChild()
{
	ImGui::SetWindowSize(ImVec2(555, 500));

	ImGui::Image(m_pTexureEspIcon, ImVec2(16, 16));
	ImGui::SameLine();
	ImGui::Text(xorstr("Extra Sensory Perception"));

	static const char* hitboxes[3] = { "Head", "Body", "Legs" };
	static const char* drawOptions[] = { "Custom", "Health" };
	static const ImVec2 blockSize = ImVec2(140, 135);

	ImGui::BeginChild(xorstr("###SnapLinesESP"), blockSize, true);
	{
		ImGui::Text(xorstr("Snap Lines"));
		ImGui::ColorEdit4(xorstr("###lineColor"), (float*)&GlobalVars::g_AllSettings.m_SnapLinesSettings.m_Color, ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Checkbox(xorstr("Active###Drawlines"), &GlobalVars::g_AllSettings.m_SnapLinesSettings.m_bActive);

		ImGui::InputInt(xorstr("###lineThickness"), &GlobalVars::g_AllSettings.m_SnapLinesSettings.m_iThickness);
		ImGui::Combo(xorstr("###LinePoint"), &GlobalVars::g_AllSettings.m_SnapLinesSettings.m_iSelectedBone, hitboxes, IM_ARRAYSIZE(hitboxes));
		ImGui::Combo(xorstr("###LineEspDrawMode"), &GlobalVars::g_AllSettings.m_SnapLinesSettings.m_iDrawMode, drawOptions, IM_ARRAYSIZE(drawOptions));
		ImGui::EndChild();
	}

	ImGui::SameLine();
	auto pos = ImGui::GetCursorPos();
	ImGui::NewLine();
	ImGui::BeginChild(xorstr("###Boxes"), blockSize, true);
	{
		static const char* styles[] = { "Solid", "Cornered" };
		ImGui::Text(xorstr("Boxes"));
		ImGui::ColorEdit4(xorstr("###boxcolor"), (float*)&GlobalVars::g_AllSettings.m_BoxEspSettings.m_Color, ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Checkbox(xorstr("Active###Draw boxes"), &GlobalVars::g_AllSettings.m_BoxEspSettings.m_bActive);

		ImGui::InputInt(xorstr("###boxThickness"), &GlobalVars::g_AllSettings.m_BoxEspSettings.m_iThickness);
		ImGui::Combo(xorstr("###BoxEspDrawMode"), &GlobalVars::g_AllSettings.m_BoxEspSettings.m_iDrawMode, drawOptions, IM_ARRAYSIZE(drawOptions));
		ImGui::Combo(xorstr("###BoxStyle"), &GlobalVars::g_AllSettings.m_BoxEspSettings.m_iStyle, styles, IM_ARRAYSIZE(styles));
		ImGui::EndChild();
	}

	//ImGui::SameLine();
	ImGui::BeginChild(xorstr("###BaResp"), blockSize, true);
	{
		ImGui::Text(xorstr("Bars"));
		ImGui::Image(m_pTexureAtomaticColorIcon, ImVec2(21, 21));
		ImGui::SameLine();
		ImGui::Checkbox(xorstr("Health bar"), &GlobalVars::g_AllSettings.m_BarEspSettings.m_bDrawHealthBar);

		ImGui::ColorEdit4(xorstr("###ArmorBarColor"), (float*)&GlobalVars::g_AllSettings.m_BarEspSettings.m_ArmorColor, ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Checkbox(xorstr("Armor bar"), &GlobalVars::g_AllSettings.m_BarEspSettings.m_bDrawArmorBar);

		ImGui::ColorEdit4(xorstr("###BgCol"), (float*)&GlobalVars::g_AllSettings.m_BarEspSettings.m_BackGroundColor, ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Text(xorstr("Background fill"));

		ImGui::InputInt(xorstr("###barsthiccness"), &GlobalVars::g_AllSettings.m_BarEspSettings.m_iThickness);
		ImGui::EndChild();
	}

	ImGui::BeginChild(xorstr("###Radar"), blockSize + ImVec2(0, 80), true);
	{
		ImGui::Text(xorstr("Radar"));
		ImGui::Checkbox(xorstr("Active"), &GlobalVars::g_AllSettings.m_RadarSettings.m_bActive);
		static const char* style[] = { "Embedded", "Custom" };

		ImGui::Combo(xorstr("Style###RStyle"), &GlobalVars::g_AllSettings.m_RadarSettings.m_iStyle, style, IM_ARRAYSIZE(style));
		DrawToolTip(xorstr("Embedded - the standard game radar will be used.\nCustom - avhook radar will be used, which you can\ncustomize yourself, for example, change the color"));


		ImGui::ColorEdit4(xorstr("Inactive Color"), (float*)&GlobalVars::g_AllSettings.m_RadarSettings.m_InactiveFeatureColor, ImGuiColorEditFlags_NoInputs);
		ImGui::ColorEdit4(xorstr("Active Color"), (float*)&GlobalVars::g_AllSettings.m_RadarSettings.m_ActiveFeatureColor, ImGuiColorEditFlags_NoInputs);
		ImGui::ColorEdit4(xorstr("Border Color"), (float*)&GlobalVars::g_AllSettings.m_RadarSettings.m_CyrcleBorderColor, ImGuiColorEditFlags_NoInputs);
		ImGui::ColorEdit4(xorstr("Cross Color"), (float*)&GlobalVars::g_AllSettings.m_RadarSettings.m_CrossColor, ImGuiColorEditFlags_NoInputs);
		ImGui::ColorEdit4(xorstr("Background Color"), (float*)&GlobalVars::g_AllSettings.m_RadarSettings.m_BackGroundColor, ImGuiColorEditFlags_NoInputs);
		ImGui::EndChild();
	}
	ImGui::SetCursorPos(pos);
	ImGui::BeginChild(xorstr("###LabelEsp"), blockSize + ImVec2(40, 105), true, m_iImGuiStyle);
	{
		ImGui::Text(xorstr("Labels"));

		static const char* positions[] = { "Left alligned", "Top alligned" };
		ImGui::Combo(xorstr("###LabelDrawPos"), &GlobalVars::g_AllSettings.m_LabelEspSettings.m_iDrawPos, positions, IM_ARRAYSIZE(positions));
		DrawToolTip(xorstr("Determine where the labels will be displayed."));

		ImGui::InputInt(xorstr("Limit"), &GlobalVars::g_AllSettings.m_LabelEspSettings.m_iMaxDrawDistance, 0);
		DrawToolTip(xorstr("Determine the distance the minimum distance\nwhen the labels should be displayed."));

		auto& style = ImGui::GetStyle();
		auto backUp = style.WindowPadding;
		auto backUp2 = style.ItemSpacing;

		style.WindowPadding = ImVec2(2, 2);
		style.ItemSpacing = ImVec2(2, 2);

		for (int i = 0; i < GlobalVars::g_AllSettings.m_LabelEspSettings.m_Labels.size(); ++i)
		{
			auto& pCurrentLabel = GlobalVars::g_AllSettings.m_LabelEspSettings.m_Labels[i];
			ImGui::BeginChild((std::string(xorstr("###Child")) + pCurrentLabel->m_sName).c_str(), ImVec2(160, 25), true, m_iImGuiStyle);
			{
				ImGui::ColorEdit4((std::string(xorstr("###Color")) + pCurrentLabel->m_sName).c_str(), (float*)&pCurrentLabel->m_Color, ImGuiColorEditFlags_NoInputs);
				ImGui::SameLine();
				if (ImGui::Button(u8"Λ", ImVec2(20, 20)) and i > 0)
				{
					GlobalVars::g_AllSettings.m_LabelEspSettings.m_Labels[i].swap(GlobalVars::g_AllSettings.m_LabelEspSettings.m_Labels[i - 1]);
				}
				ImGui::SameLine();
				if (ImGui::Button(u8"V", ImVec2(20, 20)) and i < GlobalVars::g_AllSettings.m_LabelEspSettings.m_Labels.size() - 1)
				{
					GlobalVars::g_AllSettings.m_LabelEspSettings.m_Labels[i].swap(GlobalVars::g_AllSettings.m_LabelEspSettings.m_Labels[i + 1]);
				}
				ImGui::SameLine();
				ImGui::Checkbox(pCurrentLabel->m_sName.c_str(), &pCurrentLabel->m_bActive);

				ImGui::EndChild();

			}
		}
		style.WindowPadding = backUp;
		style.ItemSpacing = backUp2;

		ImGui::EndChild();
	}
	ImGui::SameLine();
	ImGui::BeginChild(xorstr("###TextureOverrideEsp"), blockSize + ImVec2(60, 105), true, m_iImGuiStyle);
	{
		static ImColor col = ImColor(255, 255, 255);
		static char newTextureName[128] = { NULL };
		static int newTextureId = 0;
		ImGui::Text(xorstr("Texture override"));

		auto& style = ImGui::GetStyle();
		auto backUp = style.WindowPadding;
		auto backUp2 = style.ItemSpacing;

		style.WindowPadding = ImVec2(2, 2);
		style.ItemSpacing = ImVec2(2, 2);

		auto pTexutreList = &GlobalVars::g_AllSettings.m_TextureOverrideSettings.m_overridedTextures;

		ImGui::BeginChild(xorstr("###Textures"), ImVec2(180, 180), true, m_iImGuiStyle);
		{

			for (int i = 0; i < pTexutreList->size(); ++i)
			{
				auto  textureListBegin = GlobalVars::g_AllSettings.m_TextureOverrideSettings.m_overridedTextures;
				auto  pCurrentLabel = pTexutreList->begin();
				std::advance(pCurrentLabel, i);
				ImGui::BeginChild((xorstr("###TextureChild") + pCurrentLabel->m_sName).c_str(), ImVec2(160, 25), true, m_iImGuiStyle);
				{
					auto tmpColor = pCurrentLabel->GetColor();
					ImGui::ColorEdit4( (xorstr("###Txt") + pCurrentLabel->m_sName).c_str(), (float*)&tmpColor, ImGuiColorEditFlags_NoInputs);
					ImGui::SameLine();
					ImGui::Text(fmt::format(xorstr("[{}] {}"),pCurrentLabel->m_iUid, pCurrentLabel->m_sName).c_str());


					ImGui::EndChild();
				}
			}
			ImGui::EndChild();

		}
		ImGui::ColorEdit3(xorstr("###NewTexureColor"), (float*)&col, ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::PushItemWidth(40);
		ImGui::InputInt(xorstr("###newuid"), &newTextureId, 0);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushItemWidth(80);
		DrawInputTextWithTextOnBackGround(xorstr("###newtext"), xorstr("<name>"), newTextureName, sizeof(newTextureName));
		ImGui::PopItemWidth();

		ImGui::SameLine();
		if (ImGui::Button(xorstr("ADD")))
		{
			pTexutreList->push_back(Esp::CTextureOverride(newTextureId, col, newTextureName, false));
			
		}
		style.WindowPadding = backUp;
		style.ItemSpacing   = backUp2;

		ImGui::EndChild();

	}

}

void UI::CSettingsWindow::DrawMiscChild()
{
	ImGui::Checkbox(xorstr("Bunny hop"), &GlobalVars::g_AllSettings.m_BunnyHopSettings.m_bActive);
	DrawToolTip(xorstr("Provide an automatic bunny hop.\n\nNote: Use to gain more speed than 250 hu/s."));

	ImGui::SliderInt(xorstr("Field of view"), &GlobalVars::g_AllSettings.m_MiscSettings.m_iCustomFov, 1, 120);
}
void UI::CSettingsWindow::DrawCfgChild()
{
	ImGui::SetWindowSize(ImVec2(555, 450));

	ImGui::Text(xorstr("Menu configuration"));
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
					m_pMessageLineList->Add( fmt::format( xorstr("\"{}.avmcfg\" does not exist."), m_pMenuCfgName), 2000);
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

		ImGui::ColorEdit4(xorstr("###19"), reinterpret_cast<float*>(&GlobalVars::g_AllSettings.m_ChromaSettings.m_KillGlowColor), ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Text(xorstr("Kill glow (chroma)"));

		ImGui::ColorEdit4(xorstr("##21"), reinterpret_cast<float*>(&guiColorTheme[ImGuiCol_SliderGrab]), ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Text(xorstr("Slider grab"));

		ImGui::ColorEdit4(xorstr("##22"), reinterpret_cast<float*>(&guiColorTheme[ImGuiCol_SliderGrabActive]), ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Text(xorstr("Slider grab (Active)"));

		ImGui::ColorEdit4(xorstr("##ScrollActive"), reinterpret_cast<float*>(&guiColorTheme[ImGuiCol_ScrollbarGrabActive]), ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Text(xorstr("Slider grab (Active)"));

		ImGui::ColorEdit4(xorstr("##Scroll"), reinterpret_cast<float*>(&guiColorTheme[ImGuiCol_ScrollbarGrab]), ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Text(xorstr("Scroll bar"));

		ImGui::EndChild();
	}
}