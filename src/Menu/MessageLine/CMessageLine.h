#pragma once
#include "../../imgui/imgui.h"

#include <string>
#include <vector>

namespace UI
{
	class CMessageLine
	{
	public:
		CMessageLine(const std::string& text, int showDuration, const ImColor& textColor);
		void Render(const ImVec2& drawPosition);

		// If message line should be shown?
		bool isShoudShow() const;
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
		void Add(const std::string& text, const int showDuration);
		void Add(const std::string& text, const int showDuration, const ImColor& col);

		void Render(ImVec2 startPosition);
	private:
		std::vector<CMessageLine> m_Lines;

	};
}

