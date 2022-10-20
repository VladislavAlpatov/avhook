#pragma once 
#include "CBaseWindow.h"
#include  "../Routines/BindListener.h"
#include "../MessageLine/CMessageLine.h"

namespace UI
{
	class CSettingsWindow final : public CBaseWindow
	{
	public:
		
		CSettingsWindow(LPDIRECT3DDEVICE9 pDevice, CMessageLineList* pMessageLineList, bool* pShowKeyBinderDialog);
		void Render() override;
		std::string GetAlias() const override;
	private:

		enum TAB : BYTE
		{
			AimBot,
			TriggerBot,
			Visuals,
			Misc,
			Menu,
		};

		char m_pMenuCfgName[32] = {};
		bool* m_pShowKeyBinderDialog;

		void DrawAimbotChild();
		void DrawESPChild();
		void DrawMiscChild();
		void DrawCfgChild();
		void DrawTriggerBotChild();
		PDIRECT3DTEXTURE9               m_pTextureAimBotIcon = nullptr;
		PDIRECT3DTEXTURE9               m_pTextureEspIcon = nullptr;
		PDIRECT3DTEXTURE9               m_pTextureMiscIcon = nullptr;
		PDIRECT3DTEXTURE9               m_pTextureAtomaticColorIcon = nullptr;
		CMessageLineList*               m_pMessageLineList;
		Routines::CBindListener			m_BindListener;

		std::unique_ptr<ImFont> m_pFontHeaderButtons;
		int               m_iTab = TAB::Menu;
	protected:
		std::string VirtualKeyNumberToString(int keyNumber);
	};
}