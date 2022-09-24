#include "CConsoleWindow.h"
#include "../../Utils/Marker.h"
#include "../../Utils/xorstr.h"

#include "../../RawData/Images.h"
#include <d3dx9.h>
#include <fmt/format.h>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>

void UI::CConsoleWindow::Render()
{
	static char buff[128] = {NULL};
	ImGui::Begin(xorstr("###Console"), nullptr, m_iImGuiStyle);
	{
		POLY_MARKER;

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
			for (const auto& [text, color] : m_logHistory)
			{
				ImGui::TextColored(color, text.c_str());
			}
			ImGui::EndChild();
		}

		DrawCloseWindowButton();
	}
	KeepWindowInScreenArea();
	ImGui::End();
}

UI::CConsoleWindow::CConsoleWindow(LPDIRECT3DDEVICE9 pDevice) : UI::CBaseWindow(pDevice)
{
	POLY_MARKER;
	D3DXCreateTextureFromFileInMemory(m_pDevice, Images::ConsoleIcon, sizeof(Images::ConsoleIcon), &m_pTextureIcon);

	auto& style = ImGui::GetStyle();

	m_Convars.emplace(xorstr("r_use_aa_lines"), &style.AntiAliasedLines);
	m_Convars.emplace(xorstr("r_use_aa_fill"),  &style.AntiAliasedFill);
}

std::string UI::CConsoleWindow::GetAlias() const
{
	POLY_MARKER;

	return xorstr("Console");
}

bool UI::CConsoleWindow::CanBeConvertedToInt(const std::string& str)
{
	POLY_MARKER;
	if (!str.length());
		return false;
}

bool UI::CConsoleWindow::ConsoleExecute(const std::string& text)
{
	POLY_MARKER;
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
		for (const auto& [cvarName, pVal] : m_Convars)
		{
			AddConsoleLog(fmt::format(xorstr("{}: {}"), cvarName, (int)*pVal));
		}
		return true;
	}

	return false;
}

void UI::CConsoleWindow::AddConsoleLog(const std::string& text, const ImColor& col)
{
	POLY_MARKER;
	m_logHistory.emplace_back(text, col);
}
