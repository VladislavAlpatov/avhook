#include "CMessageLine.h"

void UI::CMessageLine::Render(const ImVec2& drawPosition) const
{
	auto pDrawList    = ImGui::GetForegroundDrawList();
	auto& colorTheme  = ImGui::GetStyle().Colors;
	pDrawList->AddRectFilled(drawPosition, drawPosition + m_vecSize, (ImColor)colorTheme[ImGuiCol_WindowBg]);
	pDrawList->AddRect(drawPosition,       drawPosition + m_vecSize, (ImColor)colorTheme[ImGuiCol_Border]);

	pDrawList->AddText(drawPosition + ImVec2(4, 3), m_Color, m_sText.c_str());

}