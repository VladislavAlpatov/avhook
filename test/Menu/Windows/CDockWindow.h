#pragma once 
#include "CBaseWindow.h"


namespace UI
{
	class CDockWindow : public CBaseWindow
	{
	public:
		CDockWindow(LPDIRECT3DDEVICE9 pDevice, HMODULE  hModule, CBaseWindow* pAboutWindow, CBaseWindow* pPlayerListWindow, CBaseWindow* pSettingsWindow);
		virtual void Render();
	private:
		CBaseWindow* m_pPlayerListWindow;
		CBaseWindow* m_pAboutWindow;
		CBaseWindow* m_pSettingsWindow;
	};
}