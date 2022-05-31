#pragma once
#include "CAboutWindow.h"
#include <shellapi.h>
#include "../../Globals/GlobalVars.h"
#include "../../RawData/RAVhookLogo.h"
#include "../../RawData/Images.h"
#include <d3dx9.h>
#include "../../Utils/Marker.h"
#include "../../imgui/imgui_internal.h"
#include "../../RawData/Images.h"

UI::CAboutWindow::CAboutWindow(LPDIRECT3DDEVICE9 pDevice) : CBaseWindow(pDevice)
{
	D3DXCreateTextureFromFileInMemory(pDevice,    Images::AVhookLogo, sizeof(RawData::AVhookLogoData), &m_pTexureCheatLogo);
	D3DXCreateTextureFromFileInMemory(m_pDevice,  Images::AboutIcon, sizeof(Images::AboutIcon), &m_pTextureIcon);
}

void UI::CAboutWindow::Render()
{
	ImGui::Begin(xorstr("###About"), NULL, m_iImGuiStyle);
	{

		ImGui::SetWindowSize(ImVec2(400, 150));
		DrawIconAndTittle(xorstr("About program"));

		POLY_MARKER;

		DrawCloseWindowButton();
		
		POLY_MARKER;
		auto drawList  = ImGui::GetWindowDrawList();
		auto windowPos = ImGui::GetWindowPos();
		auto cursorPos = ImGui::GetCursorPos();

		auto ImageBorderPos = windowPos + cursorPos - ImVec2(1, 1);

		drawList->AddRectFilled(ImageBorderPos, ImageBorderPos + ImVec2(102, 102), (ImColor)ImGui::GetStyle().Colors[ImGuiCol_Border]);

		ImGui::Image(m_pTexureCheatLogo, ImVec2(100, 100));

		ImGui::SameLine();
		ImGui::Text(xorstr(u8"Compilation date: %s\nCompilation time: %s\nCopyright © 2022 Alpatov Softworks."), xorstr(__DATE__), xorstr(__TIME__));

		POLY_MARKER

		ImGui::SetCursorPos(ImVec2(115, 80));
		if (ImGui::Button(xorstr("SITE"), ImVec2(100, 25)))
			ShellExecuteA(0, 0, xorstr("https://avhook.ru/"), 0, 0, SW_SHOW);
		ImGui::SameLine();
		if (ImGui::Button(xorstr("DISCORD"), ImVec2(100, 25)))
			ShellExecuteA(0, 0, xorstr("https://discord.gg/PqND3RxTCP"), 0, 0, SW_SHOW);

		KeepWindowInSreenArea();
		ImGui::End();
	}
}

UI::CAboutWindow::~CAboutWindow()
{
	m_pTexureCheatLogo->Release();
	m_pTextureIcon->Release();
}