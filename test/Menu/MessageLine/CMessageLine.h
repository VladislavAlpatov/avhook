#pragma once
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_internal.h"
#include <string>
#include <vector>

namespace UI
{
	class CMessageLine
	{
	public:
		CMessageLine(const std::string& text, int showDuration)
		{
			m_iShowDuration = showDuration;
			m_sText         = text;
			m_vecSize       = ImGui::CalcTextSize(m_sText.c_str()) + ImVec2(10, 4);
		};
		void Render(const ImVec2& drawPosition) const;
		bool isShoudShow() const
		{
			return GetTickCount64() - m_OldTime <= m_iShowDuration;
		}
		ImVec2 GetSize() const
		{
			return m_vecSize;
		}
	private:
		ULONGLONG m_OldTime = GetTickCount64() - 100;
		int m_iShowDuration;
		std::string m_sText;
		ImVec2 m_vecSize;
	};

	class CMessageLineList
	{
	public:
		void Add(const std::string& text, const int showDuration)
		{
			m_Lines.push_back(CMessageLine(text, showDuration));
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

