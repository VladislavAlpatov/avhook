#include "CSettingsWindow.h"

CSettingsWindow::CSettingsWindow(LPDIRECT3DDEVICE9 pDevice, HMODULE  hModule, SAllSettings* pAllSetting, bool* pShowKeyBinderDialog) : CBaseWindow(pDevice, hModule)
{
	m_pAllSettings          = pAllSetting;
	m_pShowKeyBinderDialog = pShowKeyBinderDialog;
	D3DXCreateTextureFromResourceA(m_pDevice, m_hModule, MAKEINTRESOURCE(IDB_BITMAP5),  &m_pTextureIcon);
	D3DXCreateTextureFromResourceA(m_pDevice, m_hModule, MAKEINTRESOURCE(IDB_BITMAP9),  &m_pTexureAimBotIcon);
	D3DXCreateTextureFromResourceA(m_pDevice, m_hModule, MAKEINTRESOURCE(IDB_BITMAP10), &m_pTexureEspIcon);
	D3DXCreateTextureFromResourceA(m_pDevice, m_hModule, MAKEINTRESOURCE(IDB_BITMAP11), &m_pTexureMiscIcon);
	D3DXCreateTextureFromResourceA(m_pDevice, m_hModule, MAKEINTRESOURCE(IDB_BITMAP8),  &m_pTexureAtomaticColorIcon);
}

void CSettingsWindow::Render()
{
	ImGui::Begin(xorstr("###Setting"), NULL, m_iImGuiStyle);
	{
		ImGui::SetWindowSize(ImVec2(555, 252));
		DrawIconAndTittle(xorstr("AVhook"));
		DrawCloseWindowButton();

		const ImVec2 buttonSize = ImVec2(102, 30);
		
		if (ImGui::Button(xorstr("AIMBOT"), buttonSize))
			m_iTab = TAB::AimBot;

		ImGui::SameLine();
		if (ImGui::Button(xorstr("TRIGGER BOT"), buttonSize))
			m_iTab = TAB::TriggerBot;

		ImGui::SameLine();
		if (ImGui::Button(xorstr("ESP"), buttonSize))
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

		ImGui::End();
	}
}
void CSettingsWindow::DrawAimbotChild()
{
	ImGui::Text(xorstr("Automatic Target Acquisition System"));
	const char* hitboxes[]   = { "Head", "Body", "Legs" };
	const char* priorities[] = { "FoV", "Distnace" };

	ImGui::BeginChild(xorstr("###General"), ImVec2(232, 166), true, m_iImGuiStyle);
	{
		ImGui::PushItemWidth(112.f);
		ImGui::Combo(xorstr("Hit-Box"), &m_pAllSettings->m_AimBotSettings.m_iSelectedHitBox, hitboxes, IM_ARRAYSIZE(hitboxes));
		DrawToolTip(xorstr("Set target Hit-Box."));

		ImGui::Combo(xorstr("Priority"), &m_pAllSettings->m_AimBotSettings.m_iPriorityType, priorities, IM_ARRAYSIZE(priorities));
		DrawToolTip(xorstr("Defines the target priority.\n\nFOV: The enemy closest to the crosshair is chosen first.\nDistance : The enemy closest to you is chosen first."));

		ImGui::InputFloat(xorstr("FoV"), &m_pAllSettings->m_AimBotSettings.m_fFov);
		DrawToolTip(xorstr("Define the field of view.\n\nNote: Enemy will be force-ignore if\nhe not in selected fov.\nSet FoV to 360 to disable it."));


		if (GlobalVars::client->pLocalPlayer != nullptr and ImGui::IsItemHovered())
		{
			auto screenSize = ImGui::GetMainViewport()->Size;

			float fovScreenRatio = sqrtf(screenSize.x * screenSize.x + screenSize.y * screenSize.y) / (float)GlobalVars::client->pLocalPlayer->m_iDefaultFOV / 2.f;

			ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(screenSize.x / 2.f, screenSize.y / 2.f),
				fovScreenRatio * m_pAllSettings->m_AimBotSettings.m_fFov,
				(ImColor)ImGui::GetStyle().Colors[ImGuiCol_Border]);

		}

		ImGui::InputFloat(xorstr("Smooth Factor"), &m_pAllSettings->m_AimBotSettings.m_fSmooth);
		ImGui::PopItemWidth();
		DrawToolTip(xorstr("Make aimbot act more like human.\n\nNote: Set \"Smooth\" value to \"0\" if\nyou want to completely disable it."));


		ImGui::Checkbox(xorstr("Auto shoot"), &m_pAllSettings->m_AimBotSettings.m_bAutoShot);
		DrawToolTip(xorstr("Provide automatic shoot when aimbot\naimed on enemy."));

		ImGui::Checkbox(xorstr("Active"), &m_pAllSettings->m_AimBotSettings.m_bActive);
		ImGui::EndChild();
	}
	ImGui::SameLine();
	ImGui::BeginChild(xorstr("###Binds"), ImVec2(232, 166), true, m_iImGuiStyle);
	{
		ImGui::Checkbox(xorstr("Activate on key"), &m_pAllSettings->m_AimBotSettings.m_bOnKey);
		DrawToolTip(xorstr("Set AimBot avtivation key."));
		ImGui::SameLine();
		if (ImGui::Button(xorstr("Set Key")))
		{
			CBindListener(&m_pAllSettings->m_AimBotSettings.m_iBindKey, m_pShowKeyBinderDialog).Listen();
		}
		ImGui::Text(xorstr("Binded to: %s"), VirtualKeyNumberToString(m_pAllSettings->m_AimBotSettings.m_iBindKey).c_str());

		ImGui::EndChild();
	}
}

void CSettingsWindow::DrawEspChild()
{
	ImGui::SetWindowSize(ImVec2(555, 500));

	ImGui::Image(m_pTexureEspIcon, ImVec2(16, 16));
	ImGui::SameLine();
	ImGui::Text(xorstr("Extra Sensory Perception"));

	const char* hitboxes[3]   = { "Head", "Body", "Legs" };
	const char* drawOptions[] = { "Custom", "Health" };
	const ImVec2 blockSize    = ImVec2(170, 145);

	ImGui::BeginChild(xorstr("###SnapLinesESP"), blockSize, true);
	{
		ImGui::Text(xorstr("Snap Lines"));
		ImGui::ColorEdit4(xorstr("###lineColor"),     (float*)&m_pAllSettings->m_SnapLinesSettings.m_Color, ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Checkbox(xorstr("Active###Drawlines"), &m_pAllSettings->m_SnapLinesSettings.m_bActive);

		ImGui::InputInt(xorstr("###lineThickness"),   &m_pAllSettings->m_SnapLinesSettings.m_iThickness);
		ImGui::Combo(xorstr("###LinePoint"),          &m_pAllSettings->m_SnapLinesSettings.m_iSelectedBone, hitboxes,    IM_ARRAYSIZE(hitboxes));
		ImGui::Combo(xorstr("###LineEspDrawMode"),    &m_pAllSettings->m_SnapLinesSettings.m_iDrawMode,     drawOptions, IM_ARRAYSIZE(drawOptions));
		ImGui::EndChild();
	}

	ImGui::SameLine();
	ImGui::BeginChild(xorstr("###Boxes"), blockSize, true);
	{
		ImGui::Text(xorstr("Box ESP"));
		ImGui::ColorEdit4(xorstr("###boxcolor"),       (float*)&m_pAllSettings->m_BoxEspSettings.m_Color, ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Checkbox(xorstr("Active###Draw boxes"), &m_pAllSettings->m_BoxEspSettings.m_bActive);

		ImGui::InputInt(xorstr("###boxThickness"),     &m_pAllSettings->m_BoxEspSettings.m_iThickness);
		ImGui::Combo(xorstr("###BoxEspDrawMode"),      &m_pAllSettings->m_BoxEspSettings.m_iDrawMode, drawOptions, IM_ARRAYSIZE(drawOptions));
		ImGui::EndChild();
	}

	ImGui::SameLine();
	ImGui::BeginChild(xorstr("###LabelEsp"), blockSize, true);
	{
		ImGui::Text(xorstr("Label ESP"));
		ImGui::ColorEdit4(xorstr("###NameLabelColor"), (float*)&m_pAllSettings->m_LabelEspSettings.m_NameLabelColor, ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Checkbox(xorstr("Name"), &m_pAllSettings->m_LabelEspSettings.m_bDrawName);

		ImGui::Image(m_pTexureAtomaticColorIcon, ImVec2(21, 21));
		ImGui::SameLine();
		ImGui::Checkbox(xorstr("Health"), &m_pAllSettings->m_LabelEspSettings.m_bDrawHealth);

		ImGui::ColorEdit4(xorstr("###ArmorLabelColor"), (float*)&m_pAllSettings->m_LabelEspSettings.m_ArmorLabelColor, ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Checkbox(xorstr("Armor"), &m_pAllSettings->m_LabelEspSettings.m_bDrawArmor);

		ImGui::ColorEdit4(xorstr("###DistanceLabelColor"), (float*)&m_pAllSettings->m_LabelEspSettings.m_DistanceLabelColor, ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Checkbox(xorstr("Distance"), &m_pAllSettings->m_LabelEspSettings.m_bDrawDistance);

		ImGui::ColorEdit4(xorstr("###Visibility"), (float*)&m_pAllSettings->m_LabelEspSettings.m_VisibilityLabelColor, ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Checkbox(xorstr("Visibility"), &m_pAllSettings->m_LabelEspSettings.m_bDrawVisibility);
		ImGui::ColorEdit4(xorstr("###Gloves"), (float*)&m_pAllSettings->m_LabelEspSettings.m_GlovesColor, ImGuiColorEditFlags_NoInputs);
		ImGui::EndChild();
	}

	ImGui::BeginChild(xorstr("###BaResp"), blockSize, true);
	{
		ImGui::Text(xorstr("Bar ESP"));
		ImGui::Image(m_pTexureAtomaticColorIcon, ImVec2(21, 21));
		ImGui::SameLine();
		ImGui::Checkbox(xorstr("Health bar"),        &m_pAllSettings->m_BarEspSettings.m_bDrawHealthBar);

		ImGui::ColorEdit4(xorstr("###ArmorBarColor"), (float*)&m_pAllSettings->m_BarEspSettings.m_ArmorColor, ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Checkbox(xorstr("Armor bar"),         &m_pAllSettings->m_BarEspSettings.m_bDrawArmorBar);
		ImGui::InputInt(xorstr("###barsthiccness"),  &m_pAllSettings->m_BarEspSettings.m_iThickness);
		ImGui::EndChild();
	}

	ImGui::SameLine();
	ImGui::BeginChild(xorstr("###Radar"), blockSize, true);
	{
		ImGui::Text(xorstr("Radar"));
		ImGui::Checkbox(xorstr("Active"), &m_pAllSettings->m_RadarSettings.m_bActive);

		ImGui::ColorEdit4(xorstr("Inactive Color"),   (float*)&m_pAllSettings->m_RadarSettings.m_InactiveFeatureColor, ImGuiColorEditFlags_NoInputs);
		ImGui::ColorEdit4(xorstr("Active Color"),     (float*)&m_pAllSettings->m_RadarSettings.m_ActiveFeatureColor,   ImGuiColorEditFlags_NoInputs);
		ImGui::ColorEdit4(xorstr("Border Color"),     (float*)&m_pAllSettings->m_RadarSettings.m_CyrcleBorderColor,    ImGuiColorEditFlags_NoInputs);
		ImGui::ColorEdit4(xorstr("Cross Color"),      (float*)&m_pAllSettings->m_RadarSettings.m_CrossColor,           ImGuiColorEditFlags_NoInputs);
		ImGui::ColorEdit4(xorstr("Background Color"), (float*)&m_pAllSettings->m_RadarSettings.m_BackGroundColor,      ImGuiColorEditFlags_NoInputs);
		ImGui::EndChild();
	}
}
void CSettingsWindow::DrawMiscChild()
{
	ImGui::Checkbox(xorstr("Bunny hop"), &m_pAllSettings->m_BunnyHopSettings.m_bActive);
	DrawToolTip(xorstr("Provide an automatic bunny hop.\n\nNote: Use to gain more speed than 250 hu/s."));

	if (GlobalVars::client->pLocalPlayer)
		ImGui::SliderInt(xorstr("Field of view"), &GlobalVars::client->pLocalPlayer->m_iDefaultFOV, 1, 120);
}
void CSettingsWindow::DrawCfgChild()
{
	ImGui::SetWindowSize(ImVec2(555, 450));

	ImGui::Text(xorstr("Menu configuration"));
	ImGui::BeginChild(xorstr("###FeatureCfg"), ImVec2(180, 80), true, m_iImGuiStyle);
	{
		ImGui::Text(xorstr("Feature Config Section"));

		DrawInputTextWithTextOnBackGround(xorstr("###Fname"), xorstr("<Config name>"), m_pAllSettings->m_sName, 32);
		if (ImGui::Button(xorstr("Import###fi")))
		{
			Config cfg;
			auto succes = Config::LoadConfigFile(m_pAllSettings->m_sName, &cfg);
			if (succes)
			{
				strcpy_s<32>(m_pAllSettings->m_sName, cfg.m_sName);
				*m_pAllSettings = cfg.m_pSettings;
			}
		}
		ImGui::SameLine();
		if (ImGui::Button(xorstr("Export###fb")))
		{
			Config cfgOnSave = Config(m_pAllSettings->m_sName, m_pAllSettings);
			cfgOnSave.DumpConfigFile(m_pAllSettings->m_sName);
		}
		ImGui::EndChild();
	}
}