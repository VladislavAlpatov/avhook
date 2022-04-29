#pragma once
#include "CBaseWindow.h"
#include <string>

namespace UI
{
	class CTaskBarWindow : public CBaseWindow
	{
	public:
		CTaskBarWindow(LPDIRECT3DDEVICE9 pDevice);
		virtual void Render();
	private:
		std::string GetLocalTime();

	};
}