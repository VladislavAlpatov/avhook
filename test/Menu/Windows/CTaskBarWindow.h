#pragma once
#include "CBaseWindow.h"
#include <string>

namespace UI
{
	class CTaskBarWindow final : public CBaseWindow
	{
	public:
		CTaskBarWindow(LPDIRECT3DDEVICE9 pDevice);
		void Render() override;
	private:
		static std::string GetLocalTime();

	};
}