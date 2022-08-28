#pragma once
#include "CDockWindow.h"
#include "../../Utils/xorstr.h"
#include "../../Utils/Marker.h"

#include <boost/algorithm/string.hpp>

UI::CDockWindow::CDockWindow(LPDIRECT3DDEVICE9 pDevice, const std::vector<std::shared_ptr<CBaseWindow>>& windowList) : CBaseWindow(pDevice)
{
	POLY_MARKER;
	m_WindowList = windowList;
	m_bForceShow = true;
}
void UI::CDockWindow::Render()
{
	POLY_MARKER;
	ImGui::Begin(xorstr("###Start"), NULL, m_iImGuiStyle | ImGuiWindowFlags_NoMove);
	{
		ImVec2 screenSize = ImGui::GetMainViewport()->Size;
		ImGui::SetWindowPos(ImVec2( (screenSize.x - ImGui::GetWindowWidth()) / 2.f , screenSize.y - ImGui::GetWindowHeight()));

		for (auto& pWindow : m_WindowList)
		{
			auto windowAlias = pWindow->GetAlias();
			boost::to_upper(windowAlias);

			if (ImGui::Button(windowAlias.c_str(), ImVec2(100, 25)))
				pWindow->Toggle();
			ImGui::SameLine();

		}
		ImGui::End();
	}
}