#include "CSettingsWindow.h"

CSettingsWindow::CSettingsWindow(LPDIRECT3DDEVICE9 pDevice, HMODULE  hModule, SAllSettings* pAllSetting, bool* pShowKeyBinderDialog) : CBaseWindow(pDevice, hModule)
{
	m_pAllSettings          = pAllSetting;
	m_pShowKeyBinderDialog = pShowKeyBinderDialog;

	D3DXCreateTextureFromResourceA(m_pDevice, m_hModule, MAKEINTRESOURCE(IDB_BITMAP5), &m_pTextureIcon);
	D3DXCreateTextureFromResourceA(m_pDevice, m_hModule, MAKEINTRESOURCE(IDB_BITMAP9), &m_pTexureAimBotIcon);
	D3DXCreateTextureFromResourceA(m_pDevice, m_hModule, MAKEINTRESOURCE(IDB_BITMAP10), &m_pTexureEspIcon);
	D3DXCreateTextureFromResourceA(m_pDevice, m_hModule, MAKEINTRESOURCE(IDB_BITMAP11), &m_pTexureMiscIcon);
	D3DXCreateTextureFromResourceA(m_pDevice, m_hModule, MAKEINTRESOURCE(IDB_BITMAP8), &m_pTexureAtomaticColorIcon);
}
void CSettingsWindow::DrawTriggerBotConfiguration(TriggerBotSettings& triggerBotSettings)
{

	ImGui::Text(xorstr("Trigger bot"));
	ImGui::Checkbox(xorstr("Active"), &triggerBotSettings.m_bActive);
	ImGui::SameLine();

	POLY_MARKER

		ImGui::Checkbox(xorstr("Rage"), &triggerBotSettings.m_bRageMode);
	ImGui::SliderInt(xorstr("Delay"), &triggerBotSettings.m_iDelay, 0, 1000);
}
void CSettingsWindow::DrawAimbotConfiguration(AimBotSettings& aimBotSettings)
{


	ImGui::Text(xorstr("Automatic Target Acquisition System"));
	const char* hitboxes[] = { "Head", "Body", "Legs" };

	POLY_MARKER;

	ImGui::BeginChild(xorstr("###General"), ImVec2(232, 166), true, m_iImGuiStyle);
	{
		ImGui::PushItemWidth(112.f);
		ImGui::Combo(xorstr("Hit-Box"), &aimBotSettings.m_iSelectedHitBox, hitboxes, IM_ARRAYSIZE(hitboxes));
		DrawToolTip(xorstr("Set target Hit-Box."));

		const char* priorities[] = { "FoV", "Distnace" };
		ImGui::Combo(xorstr("Priority"), &aimBotSettings.m_iPriorityType, priorities, IM_ARRAYSIZE(priorities));
		DrawToolTip(xorstr("Defines the target priority.\n\nFOV: The enemy closest to the crosshair is chosen first.\nDistance : The enemy closest to you is chosen first."));
		ImGui::InputFloat(xorstr("FoV"), &aimBotSettings.m_fFov);
		DrawToolTip(xorstr("Define the field of view.\n\nNote: Enemy will be force-ignore if\nhe not in selected fov.\nSet FoV to 360 to disable it."));

		if (GlobalVars::client->pLocalPlayer != nullptr and ImGui::IsItemHovered())
		{
			auto screenSize = ImGui::GetMainViewport()->Size;

			float fovScreenRatio = sqrtf(screenSize.x * screenSize.x + screenSize.y * screenSize.y) / (float)GlobalVars::client->pLocalPlayer->m_iDefaultFOV / 2.f;

			ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(screenSize.x / 2.f, screenSize.y / 2.f),
				fovScreenRatio * m_pAllSettings->m_AimBotSettings.m_fFov,
				(ImColor)ImGui::GetStyle().Colors[ImGuiCol_Border]);

		}

		ImGui::InputFloat(xorstr("Smooth Factor"), &aimBotSettings.m_fSmooth);
		ImGui::PopItemWidth();
		DrawToolTip(xorstr("Make aimbot act more like human.\n\nNote: Set \"Smooth\" value to \"0\" if\nyou want to completely disable it."));


		ImGui::Checkbox(xorstr("Auto shoot"), &aimBotSettings.m_bAutoShot);
		DrawToolTip(xorstr("Provide automatic shoot when aimbot\naimed on enemy."));

		ImGui::Checkbox(xorstr("Active"), &aimBotSettings.m_bActive);
		ImGui::EndChild();
	}
	ImGui::SameLine();
	ImGui::BeginChild(xorstr("###Binds"), ImVec2(232, 166), true, m_iImGuiStyle);
	{
		ImGui::Checkbox(xorstr("Activate on key"), &aimBotSettings.m_bOnKey);
		DrawToolTip(xorstr("Set AimBot avtivation key."));
		ImGui::SameLine();
		if (ImGui::Button(xorstr("Set Key")))
		{
			CBindListener(&aimBotSettings.m_iBindKey, m_pShowKeyBinderDialog).Listen();
		}
		ImGui::Text(xorstr("Binded to: %s"), VirtualKeyNumberToString(aimBotSettings.m_iBindKey).c_str());

		ImGui::EndChild();
	}
}

void CSettingsWindow::Render()
{
	ImGui::Begin(xorstr("###Settings"), NULL, m_iImGuiStyle);
	{
		DrawCloseWindowButton();
		ImGui::SetWindowSize(ImVec2(555, 252));

		if (ImGui::Button(xorstr("AIMBOT"), ImVec2(102, 30)))
			m_iTab = TAB::AimBot;

		POLY_MARKER

			ImGui::SameLine();
		if (ImGui::Button(xorstr("TRIGGER BOT"), ImVec2(102, 30)))
			m_iTab = TAB::TriggerBot;

		POLY_MARKER

			ImGui::SameLine();
		if (ImGui::Button(xorstr("VISUALS"), ImVec2(102, 30)))
			m_iTab = TAB::Visuals;

		POLY_MARKER

			ImGui::SameLine();
		if (ImGui::Button(xorstr("MISC"), ImVec2(102, 30)))
			m_iTab = TAB::Misc;

		ImGui::SameLine();
		if (ImGui::Button(xorstr("MENU/CFG"), ImVec2(102, 30)))
			m_iTab = TAB::Menu;
		// Render selected tab
		switch (m_iTab)
		{
		case TAB::AimBot:
			DrawAimbotConfiguration(m_pAllSettings->m_AimBotSettings);
			break;
		case TAB::TriggerBot:
			DrawTriggerBotConfiguration(m_pAllSettings->m_TriggerBotSettings);
			break;
		case TAB::Visuals:
			DrawVisualsConfiguration(m_pAllSettings->m_SnapLinesSettings, m_pAllSettings->m_BoxEspSettings,
				m_pAllSettings->m_LabelEspSettings, m_pAllSettings->m_BarEspSettings,
				m_pAllSettings->m_RadarSettings);
			break;
		case TAB::Misc:
			DrawMisceleniusConfiguration(m_pAllSettings->m_MsicSettings);
			break;
		case TAB::Menu:
			DrawMenuAndCfgConfiguration(m_pAllSettings);
			break;

		}


		KeepWindowInSreenArea();
		ImGui::End();
	}
}

void CSettingsWindow::DrawVisualsConfiguration(SnapLinesSettings& snapLinesSettings, BoxEspSetting& boxEspSettings, CLabelEspSettings& labelEspSettings,
	BarEspSettings& barEspSettings, CRadarSettings& radarSettings)
{
	ImGui::SetWindowSize(ImVec2(555, 500));

	POLY_MARKER;

	ImGui::Image(m_pTexureEspIcon, ImVec2(16, 16));
	ImGui::SameLine();
	ImGui::Text(xorstr("Extra Sensory Perception"));

	const char* hitboxes[3] = { "Head", "Body", "Legs" };

	const char* drawOptions[] = { "Custom", "Health" };

	ImGui::BeginChild(xorstr("###SnapLinesESP"), ImVec2(170, 145), true);
	{
		ImGui::Text(xorstr("Snap Lines"));
		ImGui::ColorEdit4(xorstr("###lineColor"), (float*)&snapLinesSettings.m_Color, ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Checkbox(xorstr("Active###Drawlines"), &snapLinesSettings.m_bActive);

		ImGui::InputInt(xorstr("###lineThickness"), &snapLinesSettings.m_iThickness);
		ImGui::Combo(xorstr("###LinePoint"), &snapLinesSettings.m_iSelectedBone, hitboxes, IM_ARRAYSIZE(hitboxes));
		ImGui::Combo(xorstr("###LineEspDrawMode"), &snapLinesSettings.m_iDrawMode, drawOptions, IM_ARRAYSIZE(drawOptions));
		ImGui::EndChild();
	}

	POLY_MARKER;

	ImGui::SameLine();
	ImGui::BeginChild(xorstr("###Boxes"), ImVec2(170, 145), true);
	{
		ImGui::Text(xorstr("Box ESP"));
		ImGui::ColorEdit4(xorstr("###boxcolor"), (float*)&boxEspSettings.m_Color, ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Checkbox(xorstr("Active###Draw boxes"), &boxEspSettings.m_bActive);

		ImGui::InputInt(xorstr("###boxThickness"), &boxEspSettings.m_iThickness);
		ImGui::Combo(xorstr("###BoxEspDrawMode"), &boxEspSettings.m_iDrawMode, drawOptions, IM_ARRAYSIZE(drawOptions));
		ImGui::EndChild();
	}

	ImGui::SameLine();
	ImGui::BeginChild(xorstr("###LabelEsp"), ImVec2(170, 145), true);
	{
		ImGui::Text(xorstr("Label ESP"));
		ImGui::ColorEdit4(xorstr("###NameLabelColor"), (float*)&labelEspSettings.m_NameLabelColor, ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Checkbox(xorstr("Name"), &labelEspSettings.m_bDrawName);

		ImGui::Image(m_pTexureAtomaticColorIcon, ImVec2(21, 21));
		ImGui::SameLine();
		ImGui::Checkbox(xorstr("Health"), &labelEspSettings.m_bDrawHealth);

		ImGui::ColorEdit4(xorstr("###ArmorLabelColor"), (float*)&labelEspSettings.m_ArmorLabelColor, ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Checkbox(xorstr("Armor"), &labelEspSettings.m_bDrawArmor);

		POLY_MARKER

			ImGui::ColorEdit4(xorstr("###DistanceLabelColor"), (float*)&labelEspSettings.m_DistanceLabelColor, ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Checkbox(xorstr("Distance"), &labelEspSettings.m_bDrawDistance);

		ImGui::ColorEdit4(xorstr("###Visibility"), (float*)&labelEspSettings.m_VisibilityLabelColor, ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Checkbox(xorstr("Visibility"), &labelEspSettings.m_bDrawVisibility);
		ImGui::ColorEdit4(xorstr("###Gloves"), (float*)&labelEspSettings.m_GlovesColor, ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::InputInt("Index Min", &labelEspSettings.m_iIndexMin);
		ImGui::InputInt("Index Max", &labelEspSettings.m_iIndexMax);
		ImGui::EndChild();
	}

	ImGui::BeginChild(xorstr("###BaResp"), ImVec2(170, 145), true);
	{
		ImGui::Text(xorstr("Bar ESP"));
		ImGui::Image(m_pTexureAtomaticColorIcon, ImVec2(21, 21));
		ImGui::SameLine();
		ImGui::Checkbox(xorstr("Health bar"), &barEspSettings.m_bDrawHealthBar);

		ImGui::ColorEdit4(xorstr("###ArmorBarColor"), (float*)&barEspSettings.m_ArmorColor, ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Checkbox(xorstr("Armor bar"), &barEspSettings.m_bDrawArmorBar);
		ImGui::InputInt(xorstr("###barsthiccness"), &barEspSettings.m_iThickness);
		ImGui::EndChild();
	}

	ImGui::SameLine();
	ImGui::BeginChild(xorstr("###Radar"), ImVec2(170, 145), true);
	{
		ImGui::Text(xorstr("Radar"));
		ImGui::Checkbox(xorstr("Active"), &radarSettings.m_bActive);

		ImGui::ColorEdit4(xorstr("Inactive Color"), (float*)&radarSettings.m_InactiveFeatureColor, ImGuiColorEditFlags_NoInputs);
		ImGui::ColorEdit4(xorstr("Active Color"), (float*)&radarSettings.m_ActiveFeatureColor, ImGuiColorEditFlags_NoInputs);
		ImGui::ColorEdit4(xorstr("Border Color"), (float*)&radarSettings.m_CyrcleBorderColor, ImGuiColorEditFlags_NoInputs);
		ImGui::ColorEdit4(xorstr("Cross Color"), (float*)&radarSettings.m_CrossColor, ImGuiColorEditFlags_NoInputs);
		ImGui::ColorEdit4(xorstr("Background Color"), (float*)&radarSettings.m_BackGroundColor, ImGuiColorEditFlags_NoInputs);
		ImGui::EndChild();
	}
}
void DrawMisceleniusConfiguration(MiscSettings& miscSettings)
{

}