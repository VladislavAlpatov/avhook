#include "CBaseWindow.h"

Windows::CBaseWindow::CBaseWindow(LPDIRECT3DDEVICE9 pDevice, HMODULE  hModule)
{
	m_pDevice = pDevice;
	m_hModule = hModule;

	ImFontConfig fontBUilderConfig;
	fontBUilderConfig.FontBuilderFlags |= ImGuiFreeTypeBuilderFlags_Monochrome | ImGuiFreeTypeBuilderFlags_MonoHinting;

	auto imGuiIo = ImGui::GetIO();
	m_pFontSmall      = imGuiIo.Fonts->AddFontFromFileTTF(xorstr("C:\\Windows\\Fonts\\verdana.ttf"), 11.f, &fontBUilderConfig);
	m_pFontMedium     = imGuiIo.Fonts->AddFontFromFileTTF(xorstr("C:\\Windows\\Fonts\\verdana.ttf"), 15.f, &fontBUilderConfig);
	m_pFontMediumBold = imGuiIo.Fonts->AddFontFromFileTTF(xorstr("C:\\Windows\\Fonts\\verdanab.ttf"), 15.f, &fontBUilderConfig);
}

void Windows::CBaseWindow::Toggle()
{
	auto newState = !m_bIsShow;

	if (newState)
		OnOpen();
	else
		OnClose();

	m_bIsShow = newState;
}

void Windows::CBaseWindow::KeepWindowInSreenArea()
{
	ImVec2 imgui_window_pos     = ImGui::GetWindowPos();
	ImVec2 imgui_window_size    = ImGui::GetWindowSize();
	ImVec2 game_window_size     = ImGui::GetMainViewport()->Size;
	ImVec2 new_imgui_window_pos = ImGui::GetWindowPos();

	if (imgui_window_pos.x + imgui_window_size.x > game_window_size.x)
		new_imgui_window_pos.x = game_window_size.x - imgui_window_size.x;

	// 33 is a heigh of tak bar
	else if (imgui_window_pos.y + imgui_window_size.y > game_window_size.y - 33)
		new_imgui_window_pos.y = game_window_size.y - imgui_window_size.y  - 33;

	else if (imgui_window_pos.x < 0)
		new_imgui_window_pos.x = 0;

	else if (imgui_window_pos.y < 0)
		new_imgui_window_pos.y = 0;

	ImGui::SetWindowPos(new_imgui_window_pos);
}
void Windows::CBaseWindow::DrawIconAndTittle(const char* tittle)
{
	ImGui::Image(m_pTextureIcon, ImVec2(16, 16));
	ImGui::SameLine();

	ImGui::PushFont(m_pFontMediumBold);
	ImGui::Text(tittle);
	ImGui::PopFont();
}

void Windows::CBaseWindow::DrawCloseWindowButton()
{
	ImVec2 windowSize = ImGui::GetWindowSize();

	// Setting position of button
	ImGui::SetCursorPos(ImVec2(windowSize.x - 25, 5));

	if (ImGui::Button(xorstr("X"), ImVec2(20, 20)))
		Toggle();

}

void Windows::CBaseWindow::Show()
{
	if (m_bIsShow or m_bForceShow)
	{
		ImGui::PushFont(m_pFontMedium);
		Render();
		ImGui::PopFont();
	}
}
void Windows::CBaseWindow::DrawInputTextWithTextOnBackGroundEx(const char* label, const char* backGroundLabel, char* text, size_t bufferSize, const ImColor& bgLabelCol, ImGuiInputTextFlags flags)
{
	
	if (text[0] != NULL)
	{
		ImGui::InputText(label, text, bufferSize);
		return;
	}
	auto textPos = ImGui::GetCursorPos();
	ImGui::InputText(label, text, bufferSize, flags);
	auto oldCursorPos = ImGui::GetCursorPos();

	textPos += ImVec2(7, 2);

	ImGui::SetCursorPos(textPos);
	ImGui::TextColored(bgLabelCol, backGroundLabel);
	ImGui::SetCursorPos(oldCursorPos);
}

void Windows::CBaseWindow::DrawInputTextWithTextOnBackGround(const char* label, const char* backGroundLabel, char* text, size_t bufferSize, ImGuiInputTextFlags flags)
{
	DrawInputTextWithTextOnBackGroundEx(label, backGroundLabel, text, bufferSize,ImGui::GetStyle().Colors[ImGuiCol_TextDisabled], flags);
}
void Windows::CBaseWindow::DrawImageWithBorder(ImTextureID textureID, const ImVec2& size)
{
	auto drawList  = ImGui::GetWindowDrawList();
	auto windowPos = ImGui::GetWindowPos();
	auto cursorPos = ImGui::GetCursorPos();

	auto ImageBorderPos = ImVec2(windowPos.x + cursorPos.x - 1, windowPos.y + cursorPos.y - 1);

	drawList->AddRect(ImageBorderPos, ImVec2(ImageBorderPos.x + size.x + 2, ImageBorderPos.y + size.y + 2), (ImColor)ImGui::GetStyle().Colors[ImGuiCol_Border]);

	ImGui::Image(textureID, size);
}
void Windows::CBaseWindow::DrawMultiLineInputTextWithTextOnBackGround(const char* label, const char* backGroundLabel, char* text, size_t bufferSize, ImGuiInputTextFlags flags)
{
	POLY_MARKER;

	if (text[0] != NULL)
	{
		ImGui::InputTextMultiline(label, text, bufferSize);
		return;
	}
	auto textPos = ImGui::GetCursorPos();
	ImGui::InputTextMultiline(label, text, bufferSize);
	auto oldCursorPos = ImGui::GetCursorPos();

	textPos += ImVec2(7, 2);

	ImGui::SetCursorPos(textPos);
	ImGui::TextColored(ImGui::GetStyle().Colors[ImGuiCol_TextDisabled], backGroundLabel);
	ImGui::SetCursorPos(oldCursorPos);
}
void Windows::CBaseWindow::DrawToolTip(const char* text)
{
	if (!ImGui::IsItemHovered())
		return;

	auto& style         =  ImGui::GetStyle();
	auto oldWindowPad   = style.WindowPadding;
	style.WindowPadding = ImVec2(2, 2);

	ImGui::PushFont(m_pFontSmall);
	ImGui::SetTooltip(text);
	ImGui::PopFont();

	style.WindowPadding = oldWindowPad;
}