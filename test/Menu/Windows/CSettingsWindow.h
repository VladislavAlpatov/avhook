#pragma once 
#include "CBaseWindow.h"
#include "../../imgui/imgui.h"

#include "../Settings.h"
#include "../../Globals/GlobalVars.h"
#include "../../Utils/CFGloader/CFGloader.h"
#include  "../Routines/BindListener.h"

class CSettingsWindow : public CBaseWindow
{
public:
	CSettingsWindow(LPDIRECT3DDEVICE9 pDevice, HMODULE  hModule, SAllSettings* pAllSetting, bool* pShowKeyBinderDialog);
	virtual void Render();
private:
	char m_pMenuCfgName[32] = {};
	bool* m_pShowKeyBinderDialog;

	inline void DrawAimbotChild();
	inline void DrawEspChild();
	inline void DrawMiscChild();
	inline void DrawCfgChild();

	PDIRECT3DTEXTURE9 m_pTexureAimBotIcon        = nullptr;
	PDIRECT3DTEXTURE9 m_pTexureEspIcon           = nullptr;
	PDIRECT3DTEXTURE9 m_pTexureMiscIcon          = nullptr;
	PDIRECT3DTEXTURE9 m_pTexureAtomaticColorIcon = nullptr;
	SAllSettings*     m_pAllSettings             = nullptr;
	int               m_iTab                     = 0;

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