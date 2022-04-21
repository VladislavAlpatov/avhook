#pragma once
#include "CMessageLine.h"
#include "../../imgui/imgui_internal.h"

void UI::CMessageLine::Render(const ImVec2& drawPosition)
{
	
	const ImVec2 messageBackGroundSize = GetSize();

	auto pDrawList    = ImGui::GetForegroundDrawList();
	auto& colorTheme  = ImGui::GetStyle().Colors;
	pDrawList->AddRectFilled(drawPosition, drawPosition + messageBackGroundSize, (ImColor)colorTheme[ImGuiCol_WindowBg]);
	pDrawList->AddRect(drawPosition,       drawPosition + messageBackGroundSize, (ImColor)colorTheme[ImGuiCol_Border]);


	// ImVec2(4, 4) <- padding for text;
	pDrawList->AddText(drawPosition + ImVec2(4, 4), m_Color, m_sText.c_str());

}

ImVec2 UI::CMessageLine::GetSize() const
{
	return ImGui::CalcTextSize(m_sText.c_str()) + ImVec2(6, 6);
}
