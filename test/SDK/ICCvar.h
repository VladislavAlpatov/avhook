#pragma once
#include "AbstractInterface.h"
#include "../imgui/imgui.h"

namespace SSDK
{
	class ICCvar : public CAbstractInterface
	{
	public:
		void ConsolePrint(const ImColor& col, const char* text);

	private:

	};
}