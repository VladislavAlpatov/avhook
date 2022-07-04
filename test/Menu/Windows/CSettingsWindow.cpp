#include "CSettingsWindow.h"
#include "../../imgui/imgui_internal.h"
#include "../../Globals/Settings.h"
#include "../../Globals/Interfaces.h"

#include "../../Utils/CFGloader/CFGloader.h"
#include <fmt/format.h>
#include "../../RawData/Images.h"

#include <fstream>
#include <d3dx9.h>

enum TAB
{
	AimBot,
	TriggerBot,
	Visuals,
	Misc,
	Menu,
};


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
			DrawESPChild();
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
