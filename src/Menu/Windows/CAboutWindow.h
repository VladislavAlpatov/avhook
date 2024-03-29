/*
 * Copyright (c) 2022.
 * Created by Alpatov Softworks with love in Russia.
 */

#pragma once
#include "CBaseWindow.h"

namespace UI
{
	class CAboutWindow final : public CBaseWindow
	{
	public:
		CAboutWindow(LPDIRECT3DDEVICE9 pDevice);
		void Render() override;
		PDIRECT3DTEXTURE9 m_pTextureCheatLogo = nullptr;
		std::string GetAlias() const override;
		~CAboutWindow() override;
	};
}