#include "../CSettingsWindow.h"
#include "../../../imgui/imgui_internal.h"
#include "../../../Globals/Settings.h"

#include <fmt/format.h>

void UI::CSettingsWindow::DrawESPChild()
{
	ImGui::SetWindowSize(ImVec2(555, 555));
	
	ImGui::Image(m_pTexureEspIcon, ImVec2(16, 16));
	ImGui::SameLine();
	ImGui::Text(xorstr("Extra Sensory Perception"));

	static const char* hitboxes[] = { "Head", "Body", "Legs" };
	static const char* drawOptions[] = { "Custom", "Health" };
	static const ImVec2 blockSize = ImVec2(140, 135);
	
	ImGui::BeginChild(xorstr("###SnapLinesESP"), blockSize, true);
	{
		auto pSettings = &GlobalVars::g_AllSettings.m_SnapLinesSettings;
		ImGui::Text(xorstr("Snap Lines"));
		ImGui::ColorEdit4(xorstr("###lineColor"), (float*)&pSettings->m_Color, ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Checkbox(xorstr("Active###Drawlines"), &pSettings->m_bActive);

		ImGui::InputInt(xorstr("###lineThickness"), &pSettings->m_iThickness);
		ImGui::Combo(xorstr("###LinePoint"),        &pSettings->m_iSelectedBone, hitboxes,    IM_ARRAYSIZE(hitboxes));
		ImGui::Combo(xorstr("###LineEspDrawMode"),  &pSettings->m_iDrawMode,     drawOptions, IM_ARRAYSIZE(drawOptions));
		ImGui::EndChild();
	}
	
	ImGui::SameLine();
	auto pos = ImGui::GetCursorPos();
	ImGui::NewLine();
	ImGui::BeginChild(xorstr("###Boxes"), blockSize, true);
	{
		auto pSettings = &GlobalVars::g_AllSettings.m_BoxEspSettings;
		static const char* styles[] = { "Solid", "Cornered" };
		ImGui::Text(xorstr("Boxes"));
		ImGui::ColorEdit4(xorstr("###boxcolor"), (float*)&pSettings->m_Color, ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Checkbox(xorstr("Active###Draw boxes"), &pSettings->m_bActive);

		ImGui::InputInt(xorstr("###boxThickness"), &pSettings->m_iThickness);
		ImGui::Combo(xorstr("###BoxEspDrawMode"),  &pSettings->m_iDrawMode, drawOptions, IM_ARRAYSIZE(drawOptions));
		ImGui::Combo(xorstr("###BoxStyle"),        &pSettings->m_iStyle, styles, IM_ARRAYSIZE(styles));
		ImGui::EndChild();
	}

	//ImGui::SameLine();
	ImGui::BeginChild(xorstr("###BaResp"), blockSize+ImVec2(0, 40), true);
	{
		static const char* styles[] = { "Flat", "Gradient" };
		static auto pSettings = &GlobalVars::g_AllSettings.m_BarEspSettings;
		ImGui::Text(xorstr("Bars"));
		ImGui::Image(m_pTexureAtomaticColorIcon, ImVec2(21, 21));
		ImGui::SameLine();
		ImGui::Checkbox(xorstr("Health"), &pSettings->m_bDrawHealthBar);

		ImGui::ColorEdit4(xorstr("###ArmorBarColor"), (float*)&pSettings->m_ArmorColor, ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Checkbox(xorstr("Arrmor"), &pSettings->m_bDrawArmorBar);

		ImGui::ColorEdit4(xorstr("###BgCol"), (float*)&pSettings->m_BackGroundColor, ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Text(xorstr("Fill"));

		ImGui::InputInt(xorstr("###barsthiccness"), &pSettings->m_iThickness);
		ImGui::Combo(xorstr("###BarStyle"), &pSettings->m_iStyle, styles, IM_ARRAYSIZE(styles));
		ImGui::EndChild();
	}
	ImGui::SameLine();
	ImGui::SetCursorPos(ImGui::GetCursorPos() - ImVec2(0, 30));
	ImGui::BeginChild(xorstr("###Radar"), blockSize + ImVec2(40, 80), true);
	{
		auto pSettings = &GlobalVars::g_AllSettings.m_RadarSettings;
		ImGui::Text(xorstr("Radar"));
		ImGui::Checkbox(xorstr("Active"), &pSettings->m_bActive);
		static const char* style[] = { "Embedded", "Custom" };

		ImGui::Combo(xorstr("Style###RStyle"), &pSettings->m_iStyle, style, IM_ARRAYSIZE(style));
		DrawToolTip(xorstr("Embedded - the standard game radar will be used.\nCustom - avhook radar will be used, which you can\ncustomize yourself, for example, change the color"));


		ImGui::ColorEdit4(xorstr("Inactive Color"),   (float*)&pSettings->m_InactiveFeatureColor, ImGuiColorEditFlags_NoInputs);
		ImGui::ColorEdit4(xorstr("Active Color"),     (float*)&pSettings->m_ActiveFeatureColor,   ImGuiColorEditFlags_NoInputs);
		ImGui::ColorEdit4(xorstr("Border Color"),     (float*)&pSettings->m_CyrcleBorderColor,    ImGuiColorEditFlags_NoInputs);
		ImGui::ColorEdit4(xorstr("Cross Color"),      (float*)&pSettings->m_CrossColor,           ImGuiColorEditFlags_NoInputs);
		ImGui::ColorEdit4(xorstr("Background Color"), (float*)&pSettings->m_BackGroundColor,      ImGuiColorEditFlags_NoInputs);
		ImGui::EndChild();
		
	}
	ImGui::SameLine();
	ImGui::BeginChild(xorstr("###Glow"), blockSize + ImVec2(60, 80), true);
	{
		auto& settings = GlobalVars::g_AllSettings.m_GlowEspSettings;
		ImGui::Text(xorstr("Glow Esp"));
		ImGui::Checkbox(xorstr("Active###GlowActive"), &settings.m_bActive);
		ImGui::ColorEdit3(xorstr("Color"), (float*)&settings.m_Color, ImGuiColorEditFlags_NoInputs);
		ImGui::InputFloat(xorstr("Size"), &settings.m_fGlowSize, 0.f, 0.f, "%.1f");

		if (settings.m_fGlowSize > 1.f)
			settings.m_fGlowSize = 1.f;
		
		static const char* styles[] = {"Blur", "Pusle Glass", "Rough", "Pulse Rough"};
		static const char* drawModes[] = { "Static", "Dynamic"};
		ImGui::Combo(xorstr("Style###GStyle"), &settings.m_iStyle, styles, IM_ARRAYSIZE(styles));
		ImGui::Combo(xorstr("Draw Mode###GDrawMode"), &settings.m_iDrawMode, drawModes, IM_ARRAYSIZE(drawModes));
		ImGui::InputInt(xorstr("Distance"), &settings.m_iMaxDistance, 0);
		
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
				if (ImGui::Button(xorstr(u8"Λ"), ImVec2(20, 20)) and i > 0)
				{
					GlobalVars::g_AllSettings.m_LabelEspSettings.m_Labels[i].swap(GlobalVars::g_AllSettings.m_LabelEspSettings.m_Labels[i - 1]);
				}
				ImGui::SameLine();
				if (ImGui::Button(xorstr(u8"V"), ImVec2(20, 20)) and i < GlobalVars::g_AllSettings.m_LabelEspSettings.m_Labels.size() - 1)
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
				auto  pCurrentTexture = pTexutreList->begin();
				std::advance(pCurrentTexture, i);
				ImGui::BeginChild((xorstr("###TextureChild") + pCurrentTexture->m_sName).c_str(), ImVec2(175, 25), true, m_iImGuiStyle);
				{

					auto tmpColor = pCurrentTexture->GetColor();
					ImGui::ColorEdit3((xorstr("###Texture") + pCurrentTexture->m_sName).c_str(), (float*)&tmpColor, ImGuiColorEditFlags_NoInputs);
					pCurrentTexture->UpdateColor(tmpColor);
					
					
					ImGui::SameLine();
					ImGui::Checkbox((xorstr("###checkBox") + pCurrentTexture->m_sName).c_str(), &pCurrentTexture->m_bEnableZ);
					DrawToolTip(xorstr("Make texture top-most. "));
					
					
					ImGui::SameLine();
					ImGui::Text(pCurrentTexture->m_sName.c_str());
					DrawToolTip(fmt::format(xorstr("Texture id: \"{}\" "), pCurrentTexture->m_iUid).c_str());


					ImGui::SameLine();
					ImGui::SetCursorPosX(152);
					if (ImGui::Button((xorstr("X###RemoveButton") + pCurrentTexture->m_sName).c_str(), ImVec2(21.f, 21.f)))
					{
			
						pTexutreList->erase(pCurrentTexture);
					}
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
			bool isAlreadyExist = false;
			for (const auto& texture : *pTexutreList)
			{
				isAlreadyExist = texture.m_sName == newTextureName;
			}
			if (not isAlreadyExist)
			{
				pTexutreList->push_back(Esp::CTextureOverride(newTextureId, col, newTextureName, false));
				ZeroMemory(newTextureName, sizeof(newTextureName));
				col = ImColor(255, 255, 255);
			}


		}
		style.WindowPadding = backUp;
		style.ItemSpacing = backUp2;

		ImGui::EndChild();

	}

}