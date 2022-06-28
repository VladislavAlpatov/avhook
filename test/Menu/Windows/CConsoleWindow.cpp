#pragma once
#include "CConsoleWindow.h"
#include "../../Utils/Marker.h"
#include "../../Utils/xorstr.h"

#include "../../RawData/Images.h"
#include <d3dx9.h>
#include "../../imgui/imgui_internal.h"

void UI::CConsoleWindow::Render()
{
	static char buff[128] = {NULL};
	ImGui::Begin(xorstr("###Console"), NULL, m_iImGuiStyle);
	{
		ImGui::SetWindowSize(ImVec2(256, 480));
		DrawIconAndTittle(xorstr("AVhook Developer Console"));

		ImGui::PushItemWidth(190);
		DrawInputTextWithTextOnBackGround(xorstr("###ConsoleInput"), xorstr("<\"name\" \"val\">"), buff, sizeof(buff));
		ImGui::PopItemWidth();
		ImGui::SameLine();

		if (ImGui::Button(xorstr("SET")))
		{
			ZeroMemory(buff, sizeof(buff));

			m_logHistory.push_back({ "Unknown command!", ImColor(255, 0, 0) });
		}

		ImGui::BeginChild(xorstr("###ConsoleLog"), ImVec2(240, 420), true);
		{
			for (const auto& log : m_logHistory)
			{
				ImGui::TextColored(log.second, log.first.c_str());
			}
			ImGui::EndChild();
		}

		DrawCloseWindowButton();
	}
	KeepWindowInSreenArea();
	ImGui::End();
}

UI::CConsoleWindow::CConsoleWindow(LPDIRECT3DDEVICE9 pDevice) : UI::CBaseWindow(pDevice)
{
	D3DXCreateTextureFromFileInMemory(m_pDevice, Images::ConsoleIcon, sizeof(Images::ConsoleIcon), &m_pTextureIcon);
}

std::string UI::CConsoleWindow::GetAlias()
{
	return xorstr("Console");
}

bool UI::CConsoleWindow::CanBeCovertedToInt(const std::string& str)
{
	if (!str.length());
		return false;

	for (const auto chr : str)
	{
		if (chr < '0' or chr > '9')
			return false;
	}

	if (str.length() > 1 and str[0] == '0')
		return false;

	return true;
}
