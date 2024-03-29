﻿#include "CDockWindow.h"
#include "../../Utils/xorstr.h"
#include "../../Utils/Marker.h"

UI::CDockWindow::CDockWindow(const LPDIRECT3DDEVICE9 pDevice, const std::vector<std::shared_ptr<CBaseWindow>>& windowList) : CBaseWindow(pDevice)
{
	POLY_MARKER;
	m_WindowList = windowList;
	m_bForceShow = true;
}
void UI::CDockWindow::Render()
{
	POLY_MARKER;
	ImGui::Begin(xorstr("###Start"), nullptr, m_iImGuiStyle | ImGuiWindowFlags_NoMove);
	{
		const ImVec2 screenSize = ImGui::GetMainViewport()->Size;
		ImGui::SetWindowPos(ImVec2( (screenSize.x - ImGui::GetWindowWidth()) / 2.f , screenSize.y - ImGui::GetWindowHeight()));

		for (const auto& pWindow : m_WindowList)
		{
			auto windowAlias = pWindow->GetAlias();

			for (char& chr : windowAlias) 
				chr = (char)toupper(chr);

			if (ImGui::Button(windowAlias.c_str(), ImVec2(100, 25)))
				pWindow->Toggle();
			ImGui::SameLine();

		}
		ImGui::End();
	}
}