#pragma once
#include "IBaseInterface.h"
#include "../imgui/imgui.h"

namespace SSDK
{
	class ICCvar : public IBaseInterface
	{
	public:
		void ConsolePrint(const ImColor& col, const char* text);

	private:

	};
}