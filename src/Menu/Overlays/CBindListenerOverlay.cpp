/*
 * Copyright (c) 2022.
 * Created by Alpatov Softworks with love in Russia.
 */

#include "CBindListenerOverlay.h"
#include "../../Utils/Marker.h"
#include "../../Utils/xorstr.h"
#include "../../imgui/imgui_internal.h"

void UI::CBindListenerOverlay::Show()
{
	POLY_MARKER;

	ImGui::PushFont(m_pFont);
	Render();
	ImGui::PopFont();
}
void UI::CBindListenerOverlay::Render()
{
	POLY_MARKER;

	const auto pForeGroundDrawList = ImGui::GetForegroundDrawList();
	pForeGroundDrawList->AddRectFilled(ImVec2(), ImGui::GetMainViewport()->Size, ImColor(0, 0, 0, 150));


	const auto screenSize = ImGui::GetMainViewport()->Size;
	const char* text = xorstr("Press Any Key Or ESC To Cancel");

	const ImVec2 textSize = ImGui::CalcTextSize(text);

	pForeGroundDrawList->AddText((screenSize - textSize) / 2.f, (ImColor)ImGui::GetStyle().Colors[ImGuiCol_Text], text);
}