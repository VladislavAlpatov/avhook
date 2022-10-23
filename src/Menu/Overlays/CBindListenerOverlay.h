/*
 * Copyright (c) 2022.
 * Created by Alpatov Softworks with love in Russia.
 */

#pragma once
#include "../IBaseDrawObject.h"
#include "../../imgui/imgui.h"

namespace UI
{
	class CBindListenerOverlay final : public UI::IBaseDrawObject
	{
	public:
		CBindListenerOverlay(ImFont* pFont)
		{
			m_pFont = pFont;
		}
		void Show() override;

	private:
		ImFont* m_pFont = nullptr;
		void Render() override;
	};
}