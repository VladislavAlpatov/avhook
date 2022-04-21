#pragma once
#include "../../imgui/imgui.h"

#include <string>
#include <vector>

namespace UI
{
	class CMessageLine
	{
	public:
		CMessageLine(const std::string& text, int showDuration, const ImColor& textColor)
		{
			m_iShowDuration = showDuration;
			m_sText         = text;
			m_Color         = textColor;
		};
		void Render(const ImVec2& drawPosition);

		// If message line should be shown?
		bool isShoudShow() const
		{
			return GetTickCount64() - m_ullCreationTime <= m_iShowDuration;
		}
		// Get size of message line
		ImVec2 GetSize() const;
	private:
		// Cration time stamp
		ULONGLONG   m_ullCreationTime = GetTickCount64();
		int         m_iShowDuration;
		std::string m_sText;
		ImVec2      m_vecSize;
		ImColor     m_Color;
	};
	class CMessageLineList
	{
	public:
		void Add(const std::string& text, const int showDuration)
		{
			Add(text, showDuration, ImGui::GetStyle().Colors[ImGuiCol_Text]);
		}
		void Add(const std::string& text, const int showDuration, const ImColor& col)
		{
			m_Lines.push_back(CMessageLine(text, showDuration, col));
		}

		void Render(ImVec2 startPosition)
		{
			for (int i = 0; i < m_Lines.size(); ++i)
			{
				auto messageLine = m_Lines[i];

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
	private:
		std::vector<CMessageLine> m_Lines;

	};
}

