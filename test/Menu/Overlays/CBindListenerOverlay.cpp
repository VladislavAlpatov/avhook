#include "CBindListenerOverlay.h"
#include "../../Utils/Marker.h"
#include "../../Utils/xorstr.h"

void CBindListenerOverlay::Show()
{
	POLY_MARKER;


	ImGui::PushFont(m_pFont);
	Render();
	ImGui::PopFont();
}
void CBindListenerOverlay::Render()
{
	POLY_MARKER;

	auto pForeGraundDrawList = ImGui::GetForegroundDrawList();
	pForeGraundDrawList->AddRectFilled(ImVec2(), ImGui::GetMainViewport()->Size, ImColor(0, 0, 0, 150));


	auto screenSize = ImGui::GetMainViewport()->Size;
	const char* text = xorstr("Press Any Key Or ESC To Cancel");

	const auto textSize = ImGui::CalcTextSize(text);
	ImVec2 textPos = ImVec2( (screenSize.x - textSize.x) / 2.f, (screenSize.y - textSize.y) / 2.f);

	pForeGraundDrawList->AddText(textPos, (ImColor)ImGui::GetStyle().Colors[ImGuiCol_Text], text);
}