#pragma once 
#include "CBaseWindow.h"
#include <memory>
#include <vector>

namespace UI
{
	class CDockWindow final : public CBaseWindow
	{
	public:
		CDockWindow(LPDIRECT3DDEVICE9 pDevice, const std::vector<std::shared_ptr<CBaseWindow>>& windowList);
		void Render() override;
	private:
		std::vector<std::shared_ptr<CBaseWindow>> m_WindowList;
	};
}