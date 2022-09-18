#pragma once

#include "CBaseWindow.h"

#include "../../imgui/misc/freetype/imgui_freetype.h"
#include "../../imgui/imgui_internal.h"

#include "../../Utils/xorstr.h"
#include "../../Utils/Marker.h"

UI::CBaseWindow::CBaseWindow(const LPDIRECT3DDEVICE9 pDevice)
{
	POLY_MARKER;
	m_pDevice = pDevice;

	ImFontConfig fontBuilderConfig;
	fontBuilderConfig.FontBuilderFlags |= ImGuiFreeTypeBuilderFlags_Monochrome | ImGuiFreeTypeBuilderFlags_MonoHinting;
	const auto imGuiIo = ImGui::GetIO();

	static ImWchar ranges[] = { 0x1, 0xFFFD, 0 };

	m_pFontSmall      = std::unique_ptr<ImFont>(imGuiIo.Fonts->AddFontFromFileTTF(xorstr("C:\\Windows\\Fonts\\verdana.ttf"),  11.f, &fontBuilderConfig, ranges));
	m_pFontSmallBold  = std::unique_ptr<ImFont>(imGuiIo.Fonts->AddFontFromFileTTF(xorstr("C:\\Windows\\Fonts\\verdanab.ttf"), 11.f, &fontBuilderConfig, ranges));
	m_pFontMedium     = std::unique_ptr<ImFont>(imGuiIo.Fonts->AddFontFromFileTTF(xorstr("C:\\Windows\\Fonts\\verdana.ttf"),  15.f, &fontBuilderConfig, ranges));
	m_pFontMediumBold = std::unique_ptr<ImFont>(imGuiIo.Fonts->AddFontFromFileTTF(xorstr("C:\\Windows\\Fonts\\verdanab.ttf"), 15.f, &fontBuilderConfig, ranges));

}

void UI::CBaseWindow::Toggle()
{
	POLY_MARKER;
	const auto newState = !m_bIsShow;

	if (newState)
		OnOpen();
	else
		OnClose();

	m_bIsShow = newState;
}

void UI::CBaseWindow::KeepWindowInScreenArea()
{
	POLY_MARKER;

	const ImVec2 windowPos     = ImGui::GetWindowPos();
	const ImVec2 windowSize    = ImGui::GetWindowSize();
	const ImVec2 screenSize     = ImGui::GetMainViewport()->Size;
	ImVec2 newWindowPos = ImGui::GetWindowPos();

	if (windowPos.x + windowSize.x > screenSize.x)
		newWindowPos.x = screenSize.x - windowSize.x;

	else if (windowPos.y + windowSize.y > screenSize.y)
		newWindowPos.y = screenSize.y - windowSize.y;

	else if (windowPos.x < 0)
		newWindowPos.x = 0;

	else if (windowPos.y < 0)
		newWindowPos.y = 0;

	
	ImGui::SetWindowPos(newWindowPos);
}
void UI::CBaseWindow::DrawIconAndTittle(const char* tittle) const
{

	POLY_MARKER;

	ImGui::Image(m_pTextureIcon, ImVec2(16, 16));
	ImGui::SameLine();

	ImGui::PushFont(m_pFontMediumBold.get());
	ImGui::Text(tittle);
	ImGui::PopFont();
}

void UI::CBaseWindow::DrawCloseWindowButton()
{
	POLY_MARKER;

	const ImVec2 windowSize = ImGui::GetWindowSize();

	// Setting position of button
	ImGui::SetCursorPos(ImVec2(windowSize.x - 25, 5));

	if (ImGui::Button(xorstr("X"), ImVec2(20, 20)))
		Toggle();

}

void UI::CBaseWindow::Show()
{
	POLY_MARKER;

	if (m_bIsShow or m_bForceShow)
	{
		ImGui::PushFont(m_pFontMedium.get());
		Render();
		ImGui::PopFont();
	}
}
std::string UI::CBaseWindow::GetAlias() const
{
	POLY_MARKER;
	return xorstr("Window");
}
void UI::CBaseWindow::DrawInputTextWithTextOnBackGroundEx(const char* label, const char* backGroundLabel, char* text, size_t bufferSize, const ImColor& bgLabelCol, ImGuiInputTextFlags flags)
{
	POLY_MARKER;

	if (text[0] != NULL)
	{
		ImGui::InputText(label, text, bufferSize);
		return;
	}
	const auto textPos = ImGui::GetCursorPos();
	ImGui::InputText(label, text, bufferSize, flags);
	ImGui::GetWindowDrawList()->AddText(ImGui::GetWindowPos() + textPos + ImVec2(7, 2), bgLabelCol, backGroundLabel);
}

void UI::CBaseWindow::DrawInputTextWithTextOnBackGround(const char* label, const char* backGroundLabel, char* text, size_t bufferSize, ImGuiInputTextFlags flags)
{
	DrawInputTextWithTextOnBackGroundEx(label, backGroundLabel, text, bufferSize,ImGui::GetStyle().Colors[ImGuiCol_TextDisabled], flags);
}
void UI::CBaseWindow::DrawInputIntWithTextOnBackGroundEx(const char* label, const char* backGroundLabel, int* pVal, size_t bufferSize, const ImColor& bgLabelCol, ImGuiInputTextFlags flags)
{
	// TODO: Finish this shit up.
}
void UI::CBaseWindow::DrawImageWithBorder(ImTextureID textureID, const ImVec2& size)
{
	POLY_MARKER;
	const auto drawList  = ImGui::GetWindowDrawList();
	const auto windowPos = ImGui::GetWindowPos();
	const auto cursorPos = ImGui::GetCursorPos();

	const auto ImageBorderPos = windowPos + cursorPos - ImVec2(1, 1);

	drawList->AddRect(ImageBorderPos, ImageBorderPos + size + ImVec2(2, 2), (ImColor)ImGui::GetStyle().Colors[ImGuiCol_Border]);

	ImGui::Image(textureID, size);
}
void UI::CBaseWindow::DrawTextCentered(const char* text)
{
	POLY_MARKER;
	ImGui::SetCursorPosX( (ImGui::GetWindowWidth() - ImGui::CalcTextSize(text).x) / 2.f);
	ImGui::Text(text);
}
void UI::CBaseWindow::DrawMultiLineInputTextWithTextOnBackGround(const char* label, const char* backGroundLabel, char* text, size_t bufferSize, ImGuiInputTextFlags flags)
{
	POLY_MARKER;

	if (text[0] != NULL)
	{
		ImGui::InputTextMultiline(label, text, bufferSize);
		return;
	}
	auto textPos = ImGui::GetCursorPos();
	ImGui::InputTextMultiline(label, text, bufferSize);
	const auto oldCursorPos = ImGui::GetCursorPos();

	textPos += ImVec2(7, 2);

	ImGui::SetCursorPos(textPos);
	ImGui::TextColored(ImGui::GetStyle().Colors[ImGuiCol_TextDisabled], backGroundLabel);
	ImGui::SetCursorPos(oldCursorPos);
}
void UI::CBaseWindow::DrawToolTip(const char* text)
{
	POLY_MARKER;
	if (!ImGui::IsItemHovered())
		return;

	auto& style         =  ImGui::GetStyle();
	const auto oldWindowPad   = style.WindowPadding;
	style.WindowPadding = ImVec2(2, 2);

	POLY_MARKER;

	ImGui::PushFont(m_pFontSmall.get());
	ImGui::SetTooltip(text);
	ImGui::PopFont();

	style.WindowPadding = oldWindowPad;
}