#pragma once
#include "CBaseWindow.h"
#include "../Settings.h"
#include <string>
#include <time.h>

namespace Windows
{
	class CTaskBarWindow : public CBaseWindow
	{
	public:
		CTaskBarWindow(LPDIRECT3DDEVICE9 pDevice, HMODULE  hModule, CBaseWindow* startWindow, MiscSettings* pMiscSettings);
		virtual void Render();
	private:
		CBaseWindow* m_pStartWindow = nullptr;
		MiscSettings* m_pMiscSetting = nullptr;
		std::string GetLocalTime();

	};
}