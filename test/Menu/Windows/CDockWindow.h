#pragma once 
#include "CBaseWindow.h"
#include <memory>
#include <vector>

namespace UI
{
	class CDockWindow : public CBaseWindow
	{
	public:
		CDockWindow(LPDIRECT3DDEVICE9 pDevice, const std::vector<std::shared_ptr<CBaseWindow>>& windowList);
		virtual void Render();
	private:
		std::vector<std::shared_ptr<CBaseWindow>> m_WindowList;
	};
}