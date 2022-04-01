#pragma once
#include "CBaseWindow.h"
#include "../Settings.h"
#include <string>

namespace UI
{
	class CTaskBarWindow : public CBaseWindow
	{
	public:
		CTaskBarWindow(LPDIRECT3DDEVICE9 pDevice, HMODULE  hModule, CBaseWindow* startWindow, Settings::MiscSettings* pMiscSettings);
		virtual void Render();
	private:
		CBaseWindow* m_pStartWindow = nullptr;
		Settings::MiscSettings* m_pMiscSetting = nullptr;
		std::string GetLocalTime();

	};
}