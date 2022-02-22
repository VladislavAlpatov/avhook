#pragma once 
#include "CBaseWindow.h"


namespace UI
{
	class CStartWindow : public CBaseWindow
	{
	public:
		CStartWindow(LPDIRECT3DDEVICE9 pDevice, HMODULE  hModule, CBaseWindow* pAboutWindow, CBaseWindow* pPlayerListWindow, CBaseWindow* pSettingsWindow);
		virtual void Render();
	private:
		CBaseWindow* m_pPlayerListWindow;
		CBaseWindow* m_pAboutWindow;
		CBaseWindow* m_pSettingsWindow;
	};
}