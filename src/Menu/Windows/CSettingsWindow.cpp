#include "CSettingsWindow.h"

#include <fstream>
#include <d3dx9.h>
#include <memory>

#include "../../Globals/Settings.h"
#include "../../Globals/Interfaces.h"

#include "../../imgui/misc/freetype/imgui_freetype.h"
#include "../../imgui/imgui_internal.h"
#include "../../RawData/Images.h"



UI::CSettingsWindow::CSettingsWindow(const LPDIRECT3DDEVICE9 pDevice, CMessageLineList* pMessageLineList, bool* pShowKeyBinderDialog) : CBaseWindow(pDevice)
{
	POLY_MARKER;

	m_pShowKeyBinderDialog  = pShowKeyBinderDialog;
	m_pMessageLineList      = pMessageLineList;
	m_BindListener          = Routines::CBindListener(&GlobalVars::g_AllSettings.m_AimBotSettings.m_iBindKey, m_pShowKeyBinderDialog);
	
	D3DXCreateTextureFromFileInMemory(m_pDevice, Images::SettingsIcon,  sizeof(Images::SettingsIcon),  &m_pTextureIcon);
	D3DXCreateTextureFromFileInMemory(m_pDevice, Images::AimbotIcon,    sizeof(Images::AimbotIcon),    &m_pTextureAimBotIcon);
	D3DXCreateTextureFromFileInMemory(m_pDevice, Images::EspIcon,       sizeof(Images::EspIcon),       &m_pTextureEspIcon);
	D3DXCreateTextureFromFileInMemory(m_pDevice, Images::AutoColorIcon, sizeof(Images::AutoColorIcon), &m_pTextureAtomaticColorIcon);



	ImFontConfig fontConfig;
	fontConfig.FontBuilderFlags |= ImGuiFreeTypeBuilderFlags_Monochrome | ImGuiFreeTypeBuilderFlags_MonoHinting;
	const auto& io = ImGui::GetIO();
	
	static ImWchar ranges[] = { 0x1, 0xFFFD, 0 };
	m_pFontHeaderButtons = std::unique_ptr<ImFont>(io.Fonts->AddFontFromFileTTF(xorstr("C:\\Windows\\Fonts\\verdanab.ttf"), 13.f, &fontConfig, ranges));
}
std::string UI::CSettingsWindow::VirtualKeyNumberToString(int keyNumber)
{
	switch (keyNumber)
	{
	case VK_LBUTTON:  return xorstr("Left Mouse Button");
	case VK_RBUTTON:  return xorstr("Right Mouse Button");
	case VK_XBUTTON1: return xorstr("Mouse4 Button");
	case VK_XBUTTON2: return xorstr("Mouse5 Button");
		default:
			char name[32] = { 0 };
			const LONG lParamValue = (MapVirtualKeyW(keyNumber, MAPVK_VK_TO_VSC) << 16);
			int result = GetKeyNameTextA(lParamValue, name, 32);

			return name;
	}
}
void UI::CSettingsWindow::Render()
{
	POLY_MARKER;

	ImGui::Begin(xorstr("###Setting"), nullptr, m_iImGuiStyle);
	{
		ImGui::SetWindowSize(ImVec2(555, 252));
		DrawIconAndTittle(xorstr("AVhook"));
		DrawCloseWindowButton();
		
		auto& style = ImGui::GetStyle();

		const auto spacingOld = style.ItemSpacing;
		const auto paddingOld = style.FramePadding;

		style.ItemSpacing = ImVec2(-1, 0);

		ImGui::PushFont(m_pFontHeaderButtons.get());

		const auto rectStart = ImGui::GetWindowPos() + ImGui::GetCursorPos()-ImVec2(3,0);

		if (ImGui::Button(xorstr("General")))
			m_iTab = TAB::Menu;
		ImGui::SameLine();
		if (ImGui::Button(xorstr("Aim Bot")))
			m_iTab = TAB::AimBot;

		ImGui::SameLine();
		if (ImGui::Button(xorstr("Trigger Bot")))
			m_iTab = TAB::TriggerBot;

		ImGui::SameLine();
		if (ImGui::Button(xorstr("Visuals")))
			m_iTab = TAB::Visuals;

		ImGui::SameLine();
		if (ImGui::Button(xorstr("Misc")))
			m_iTab = TAB::Misc;


		style.ItemSpacing = spacingOld;
		style.FramePadding = paddingOld;

		ImGui::GetWindowDrawList()->AddRect(rectStart+ImVec2(3,0), rectStart + ImVec2(542, 19), (ImColor)style.Colors[ImGuiCol_Border]);
		ImGui::PopFont();
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);


		switch (m_iTab)
		{
		case AimBot:		DrawAimbotChild();        break;
		case Visuals:		DrawESPChild();           break;
		case Misc:			DrawMiscChild();          break;
		case Menu:			DrawCfgChild();			  break;
		case TriggerBot:   DrawTriggerBotChild();    break;

		default: break;
		}
		KeepWindowInScreenArea();
		ImGui::End();
	}
}
std::string UI::CSettingsWindow::GetAlias() const
{
	POLY_MARKER;
	return xorstr("Settings");
}
