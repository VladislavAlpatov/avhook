#pragma once
#include "CAboutWindow.h"
#include <shellapi.h>
#include <d3dx9.h>

#include "../../Globals/Settings.h"
#include "../../RawData/RAVhookLogo.h"
#include "../../RawData/Images.h"
#include "../../Utils/Marker.h"
#include "../../imgui/imgui_internal.h"

UI::CAboutWindow::CAboutWindow(const LPDIRECT3DDEVICE9 pDevice) : CBaseWindow(pDevice)
{
	D3DXCreateTextureFromFileInMemory(m_pDevice,    Images::AVhookLogo, sizeof(RawData::AVhookLogoData), &m_pTextureCheatLogo);
	D3DXCreateTextureFromFileInMemory(m_pDevice,  Images::AboutIcon, sizeof(Images::AboutIcon), &m_pTextureIcon);
}

void UI::CAboutWindow::Render()
{
	ImGui::Begin(xorstr("###About"), nullptr, m_iImGuiStyle);
	{

		ImGui::SetWindowSize(ImVec2(400, 150));
		DrawIconAndTittle(xorstr("About program"));

		POLY_MARKER;

		DrawCloseWindowButton();
		
		POLY_MARKER;

		const auto pDrawList  = ImGui::GetWindowDrawList();
		const auto windowPos = ImGui::GetWindowPos();
		const auto cursorPos = ImGui::GetCursorPos();

		const auto ImageBorderPos = windowPos + cursorPos - ImVec2(1, 1);

		pDrawList->AddRectFilled(ImageBorderPos, ImageBorderPos + ImVec2(102, 102), (ImColor)ImGui::GetStyle().Colors[ImGuiCol_Border]);

		ImGui::Image(m_pTextureCheatLogo, ImVec2(100, 100));

		ImGui::SameLine();
		ImGui::Text(
			xorstr(u8"Compilation date: %s\nCompilation time: %s\nCopyright © 2022 Alpatov Softworks."),
			xorstr(__DATE__), xorstr(__TIME__));

		POLY_MARKER

		ImGui::SetCursorPos(ImVec2(115, 80));
		if (ImGui::Button(xorstr("SITE"), ImVec2(100, 25)))
			ShellExecuteA(nullptr, nullptr, xorstr("https://avhook.ru/"), nullptr, nullptr, SW_SHOW);
		ImGui::SameLine();
		if (ImGui::Button(xorstr("DISCORD"), ImVec2(100, 25)))
			ShellExecuteA(nullptr, nullptr, xorstr("https://discord.gg/PqND3RxTCP"), nullptr, nullptr, SW_SHOW);

		KeepWindowInScreenArea();
		ImGui::End();
	}
}

std::string UI::CAboutWindow::GetAlias() const
{
	return xorstr("About");
}

UI::CAboutWindow::~CAboutWindow()
{
	m_pTextureCheatLogo->Release();
	m_pTextureIcon->Release();
}