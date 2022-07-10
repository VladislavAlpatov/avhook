#include "../CSettingsWindow.h"
#include "../../../Globals/Settings.h"
#include "../../../Globals/Interfaces.h"
#include "../../../imgui/imgui_internal.h"


void UI::CSettingsWindow::DrawAimbotChild()
{
	ImGui::SetWindowSize(ImVec2(555, 400));
	static const char* hitboxes[] = { "Head",   "Chest", "Pelvis" };
	static const char* priorities[] = { "FoV",    "Distance" };
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
