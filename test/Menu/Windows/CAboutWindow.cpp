#include "CAboutWindow.h"

Windows::CAboutWindow::CAboutWindow(LPDIRECT3DDEVICE9 pDevice, HMODULE  hModule) : CBaseWindow(pDevice, hModule)
{
	D3DXCreateTextureFromResourceA(m_pDevice, m_hModule, MAKEINTRESOURCE(IDB_BITMAP1), &m_pTextureIcon);
	D3DXCreateTextureFromFileInMemory(pDevice, RawData::AVhookLogoData, sizeof(RawData::AVhookLogoData), &m_pTexureCheatLogo);
}

void Windows::CAboutWindow::Render()
{
	ImGui::Begin(xorstr("###About"), NULL, m_iImGuiStyle);
	{

		ImGui::SetWindowSize(ImVec2(400, 150));
		DrawIconAndTittle(xorstr("About program"));

		POLY_MARKER

		DrawCloseWindowButton();
		
		POLY_MARKER;
		auto drawList = ImGui::GetWindowDrawList();
		auto windowPos = ImGui::GetWindowPos();
		auto cursorPos = ImGui::GetCursorPos();

		auto ImageBorderPos = ImVec2(windowPos.x + cursorPos.x - 1, windowPos.y + cursorPos.y - 1);

		drawList->AddRectFilled(ImageBorderPos, ImVec2(ImageBorderPos.x + 100 + 2, ImageBorderPos.y + 100 + 2), (ImColor)ImGui::GetStyle().Colors[ImGuiCol_Border]);

		ImGui::Image(m_pTexureCheatLogo, ImVec2(100, 100));

		ImGui::SameLine();
		ImGui::Text(xorstr("Compilation date: %s\nCompilation time: %s\nPowered by LSS, all rights reserved."), xorstr(__DATE__), xorstr(__TIME__));

		POLY_MARKER

		ImGui::SetCursorPos(ImVec2(115, 80));
		if (ImGui::Button(xorstr("SITE"), ImVec2(100, 25)))
			ShellExecute(0, 0, xorstr("https://avhook.ru/"), 0, 0, SW_SHOW);
		ImGui::SameLine();
		if (ImGui::Button(xorstr("DISCORD"), ImVec2(100, 25)))
			ShellExecute(0, 0, xorstr("https://discord.gg/PqND3RxTCP"), 0, 0, SW_SHOW);

		KeepWindowInSreenArea();
		ImGui::End();
	}
}

Windows::CAboutWindow::~CAboutWindow()
{
	m_pTexureCheatLogo->Release();
	m_pTextureIcon->Release();
}