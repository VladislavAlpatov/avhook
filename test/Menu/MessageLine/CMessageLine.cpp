#include "CMessageLine.h"
#include "../../imgui/imgui_internal.h"

UI::CMessageLine::CMessageLine(const std::string& text, int showDuration, const ImColor& textColor)
{
	POLY_MARKER;
	m_iShowDuration = showDuration;
	m_sText = text;
	m_Color = textColor;
}

void UI::CMessageLine::Render(const ImVec2& drawPosition)
{
	POLY_MARKER;
	const ImVec2 messageBackGroundSize = GetSize();

	auto pDrawList    = ImGui::GetForegroundDrawList();
	auto& colorTheme  = ImGui::GetStyle().Colors;
	pDrawList->AddRectFilled(drawPosition, drawPosition + messageBackGroundSize, (ImColor)colorTheme[ImGuiCol_WindowBg]);
	pDrawList->AddRect(drawPosition,       drawPosition + messageBackGroundSize, (ImColor)colorTheme[ImGuiCol_Border]);

	POLY_MARKER;
	// ImVec2(4, 4) <- padding for text;
	pDrawList->AddText(drawPosition + ImVec2(4, 4), m_Color, m_sText.c_str());

}

bool UI::CMessageLine::isShoudShow() const
{
	return GetTickCount64() - m_ullCreationTime <= m_iShowDuration;
}

ImVec2 UI::CMessageLine::GetSize() const
{
	return ImGui::CalcTextSize(m_sText.c_str()) + ImVec2(6, 6);
}

void UI::CMessageLineList::Add(const std::string& text, const int showDuration)
{
	Add(text, showDuration, ImGui::GetStyle().Colors[ImGuiCol_Text]);
}

void UI::CMessageLineList::Add(const std::string& text, const int showDuration, const ImColor& col)
{
	m_Lines.push_back(CMessageLine(text, showDuration, col));
}

void UI::CMessageLineList::Render(ImVec2 startPosition)
{
	POLY_MARKER;
	for (int i = 0; i < m_Lines.size(); ++i)
	{
		auto messageLine = m_Lines[i];

		POLY_MARKER;
		if (!messageLine.isShoudShow())
		{
			m_Lines.erase(m_Lines.begin() + i);
			continue;
		}
		// -1 cuz window borders
		messageLine.Render(startPosition);
		startPosition.y += messageLine.GetSize().y - 1;
	}
}
