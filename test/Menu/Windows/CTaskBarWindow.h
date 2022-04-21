#pragma once
#include "CBaseWindow.h"
#include <string>

namespace UI
{
	class CTaskBarWindow : public CBaseWindow
	{
	public:
		CTaskBarWindow(LPDIRECT3DDEVICE9 pDevice, HMODULE  hModule);
		virtual void Render();
	private:
		std::string GetLocalTime();

	};
}