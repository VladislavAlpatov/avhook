#pragma once 
#include "CBaseWindow.h"
#include <memory>


namespace UI
{
	class CDockWindow : public CBaseWindow
	{
	public:
		CDockWindow(LPDIRECT3DDEVICE9 pDevice, const std::shared_ptr<CBaseWindow>& pAboutWindow, const std::shared_ptr<CBaseWindow>& pPlayerListWindow, const std::shared_ptr<CBaseWindow>& pSettingsWindow);
		virtual void Render();
	private:
		std::shared_ptr<CBaseWindow> m_pPlayerListWindow;
		std::shared_ptr<CBaseWindow> m_pAboutWindow;
		std::shared_ptr<CBaseWindow> m_pSettingsWindow;
	};
}