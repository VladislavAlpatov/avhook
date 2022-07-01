#pragma once
#include "CConsoleWindow.h"
#include "../../Utils/Marker.h"
#include "../../Utils/xorstr.h"

#include "../../RawData/Images.h"
#include <d3dx9.h>
#include "../../imgui/imgui_internal.h"
#include <fmt/format.h>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>

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

			if (!ConsoleExecute(buff))
				AddConsoleLog(fmt::format(xorstr("Unknow command: \"{}\""), buff));

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

	auto& style = ImGui::GetStyle();

	m_Convars.emplace(xorstr("r_use_aa_lines"), &style.AntiAliasedLines);
	m_Convars.emplace(xorstr("r_use_aa_fill"),  &style.AntiAliasedFill);
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

bool UI::CConsoleWindow::ConsoleExecute(const std::string& text)
{
	AddConsoleLog(xorstr(">> ")+text);

	std::vector<std::string> rawData;
	boost::split(rawData, text, boost::is_any_of(xorstr(" ")));

	if (rawData.size() == 2 and m_Convars.find(rawData[0]) != m_Convars.end())
	{
		*m_Convars[rawData[0]] = (bool)std::stoi(rawData[1]);
		AddConsoleLog(xorstr("Done"), ImColor(0, 255, 0));
		return true;
	}

	if (!rawData.empty() and rawData[0] == xorstr("cvar_list"))
	{
		for (const auto& cvar : m_Convars)
		{
			AddConsoleLog(fmt::format(xorstr("{}: {}"), cvar.first, (int)*cvar.second));
		}
		return true;
	}

	return false;
}

void UI::CConsoleWindow::AddConsoleLog(const std::string& text, const ImColor& col)
{
	m_logHistory.push_back({ text, col });
}