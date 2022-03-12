#pragma once 
#include "CBaseWindow.h"
#include "../Settings.h"
#include "../../Globals/GlobalVars.h"
#include "../../Utils/CFGloader/CFGloader.h"
#include  "../Routines/BindListener.h"
#include "../MessageLine/CMessageLine.h"

namespace UI
{
	class CSettingsWindow : public CBaseWindow
	{
	public:
		CSettingsWindow(LPDIRECT3DDEVICE9 pDevice, HMODULE  hModule, CMessageLineList* pMessageLineList, Settings::CAllSettings* pAllSetting, bool* pShowKeyBinderDialog);
		virtual void Render();
	private:
		char m_pMenuCfgName[32] = {};
		bool* m_pShowKeyBinderDialog;

		inline void DrawAimbotChild();
		inline void DrawEspChild();
		inline void DrawMiscChild();
		inline void DrawCfgChild();

		PDIRECT3DTEXTURE9               m_pTexureAimBotIcon = nullptr;
		PDIRECT3DTEXTURE9               m_pTexureEspIcon = nullptr;
		PDIRECT3DTEXTURE9               m_pTexureMiscIcon = nullptr;
		PDIRECT3DTEXTURE9               m_pTexureAtomaticColorIcon = nullptr;
		Settings::CAllSettings*         m_pAllSettings = nullptr;
		CMessageLineList*               m_pMessageLineList;
		Routines::CBindListener			m_BindListener;
		int               m_iTab = 0;

		enum TAB
		{
			AimBot,
			TriggerBot,
			Visuals,
			Misc,
			Menu,
		};
	protected:
		std::string VirtualKeyNumberToString(int keyNumber);
	};
}