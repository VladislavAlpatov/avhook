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

	inline void DrawAimbotConfiguration(AimBotSettings& aimBotSettings);
	inline void DrawTriggerBotConfiguration(TriggerBotSettings& triggerBotSettings);
	inline void DrawVisualsConfiguration(SnapLinesSettings& snapLinesSettings,
		BoxEspSetting& boxEspSettings, CLabelEspSettings& labelEspSettings,
		BarEspSettings& barEspSettings, CRadarSettings& radarSettings);

	inline void DrawMisceleniusConfiguration(MiscSettings& miscSettings);
	inline void DrawMenuAndCfgConfiguration(SAllSettings* pAllSettings);
	bool IsPathEndWith(const char* path, const char* end);

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
	std::string VirtualKeyNumberToString(int keyNumber)
	{
		char name[32] = { 0 };
		UINT scanCode = MapVirtualKeyW(keyNumber, MAPVK_VK_TO_VSC);
		LONG lParamValue = (scanCode << 16);
		int result = GetKeyNameTextA(lParamValue, name, 32);

		return std::string(name);
	}
};