#include "CBindListenerOverlay.h"

void CBindListenerOverlay::Show()
{
	ImGui::PushFont(m_pFont);
	Render();
	ImGui::PopFont();
}
void CBindListenerOverlay::Render()
{
	auto pForeGraundDrawList = ImGui::GetForegroundDrawList();
	pForeGraundDrawList->AddRectFilled(ImVec2(), ImGui::GetMainViewport()->Size, ImColor(0, 0, 0, 150));


	auto screenSize = ImGui::GetMainViewport()->Size;
	const char* text = xorstr("Press Any Key Or ESC To Cancel");

	POLY_MARKER

	float textWidth = ImGui::CalcTextSize(text).x;
	ImVec2 textPos = ImVec2((screenSize.x / 2.f) - (textWidth / 2.f), screenSize.y / 2.f - 6);

	pForeGraundDrawList->AddText(textPos, (ImColor)ImGui::GetStyle().Colors[ImGuiCol_Text], text);
}