#pragma once
#include <Windows.h>

#include "../imgui/imgui.h"
#include "../Utils/xorstr.h"
#include "../SDK/CBaseEntity.h"
#include <nlohmann/json.hpp>

using namespace nlohmann;

enum DrawMod : int
{
	CUSTOM,
	AUTO
};
class CBaseSettings
{
public:
	bool m_bActive = false;
	bool m_bOnKey  = false;
	int m_iBindKey = 0;
	
	virtual json ToJson() 
	{ 
		json jsn;

		jsn[xorstr("Active")]  = m_bActive;
		jsn[xorstr("OnKey")]   = m_bOnKey;
		jsn[xorstr("BindKey")] = m_iBindKey;

		return jsn;
	};
protected:
	json ImColorToJsn(const ImColor& color)
	{
		json jsn;

		jsn[xorstr("R")] = color.Value.x;
		jsn[xorstr("G")] = color.Value.y;
		jsn[xorstr("B")] = color.Value.z;
		jsn[xorstr("A")] = color.Value.w;

		return jsn;
	}
	ImColor ImportImColorFromJson(const json& jsn)
	{
		return ImColor(
			jsn[xorstr("R")].get<float>(), 
			jsn[xorstr("G")].get<float>(),
			jsn[xorstr("B")].get<float>(), 
			jsn[xorstr("A")].get<float>()
		);
	}
};
class AimBotSettings : public CBaseSettings
{
public:
	AimBotSettings() {};
	bool			   m_bAutoShot	   = false;
	bool			   silent		   = false;
	bool			   m_bIsWorking	   = false;
	float			   m_fFov          = 10.f;
	float			   m_fSmooth        = 0.f;
	int                m_iSelectedHitBox = 0;
	int				   m_iPriorityType   = 0;
	CBaseEntity*       m_pCurrentTarget  = 0;

	enum PriorityType
	{
		Distance,
		FieldOfView,
	};
	virtual json ToJson()
	{
		json jsn;

		jsn[xorstr("Active")]         = m_bActive;
		jsn[xorstr("OnKey")]          = m_bOnKey;
		jsn[xorstr("BindKey")]        = m_iBindKey;
		jsn[xorstr("AutoShot")]       = m_bAutoShot;
		jsn[xorstr("Silent")]         = silent;
		jsn[xorstr("Fov")]            = m_fFov;
		jsn[xorstr("Smooth")]         = m_fSmooth;
		jsn[xorstr("SelectedHitBox")] = m_iSelectedHitBox;
		jsn[xorstr("PriorityType")]   = m_iPriorityType;
		return jsn;
	};
	AimBotSettings(const json& jsn)
	{
		m_bActive         = jsn[xorstr("Active")].get<bool>();
		m_bOnKey          = jsn[xorstr("OnKey")].get<int>();
		m_iBindKey        = jsn[xorstr("BindKey")].get<int>();
		m_bAutoShot       = jsn[xorstr("AutoShot")].get<bool>();
		silent            = jsn[xorstr("Silent")].get<bool>();
		m_fFov            = jsn[xorstr("Fov")].get<float>();
		m_fSmooth         = jsn[xorstr("Smooth")].get<float>();
		m_iSelectedHitBox = jsn[xorstr("SelectedHitBox")].get<int>();
		m_iPriorityType   = jsn[xorstr("PriorityType")].get<int>();
	}
};
class SnapLinesSettings : public CBaseSettings
{
public:
	SnapLinesSettings() {};
	int m_iSelectedBone = 0;
	ImColor		m_Color = ImColor(255, 0, 0, 255);
	int			m_iDrawMode = 0;
	int			m_iThickness = 1;

	virtual json ToJson()
	{
		json jsn;

		jsn[xorstr("Active")]          = m_bActive;
		jsn[xorstr("SelectedBone")]    = m_iSelectedBone;
		jsn[xorstr("Color")]           = ImColorToJsn(m_Color);
		jsn[xorstr("DrawMode")]        = m_iDrawMode;
		jsn[xorstr("Thickness")]       = m_iThickness;

		return jsn;
	};

	SnapLinesSettings(const json& jsn)
	{
		m_bActive = jsn[xorstr("Active")].get<bool>();
		m_iSelectedBone = jsn[xorstr("SelectedBone")].get<int>();
		m_Color = ImportImColorFromJson(jsn[xorstr("Color")]);
		m_iDrawMode = jsn[xorstr("DrawMode")].get<int>();
		m_iThickness = jsn[xorstr("Thickness")].get<int>();
	}
};
class BoxEspSetting : public CBaseSettings
{
public:
	BoxEspSetting() {};
	ImColor		m_Color      = ImColor(255, 0, 0, 255);
	int			m_iDrawMode  = 0;
	int			m_iThickness = 1;

	virtual json ToJson()
	{
		json jsn;

		jsn[xorstr("Active")] = m_bActive;
		jsn[xorstr("Color")] = ImColorToJsn(m_Color);
		jsn[xorstr("DrawMode")] = m_iDrawMode;
		jsn[xorstr("Thickness")] = m_iThickness;

		return jsn;
	};

	BoxEspSetting(const json& jsn)
	{
		m_bActive = jsn[xorstr("Active")].get<bool>();

		m_Color = ImportImColorFromJson(jsn[xorstr("Color")]);
		m_iDrawMode = jsn[xorstr("DrawMode")].get<int>();
		m_iThickness = jsn[xorstr("Thickness")].get<int>();
	}
};
class MiscSettings : public CBaseSettings
{
public:
	MiscSettings() {};
	bool m_bWallPaper  = false;
	bool m_bShowTime   = false;
	bool m_bKillSound  = false;
	bool m_bSnowFlakes = false;
	char killSoundPath[100] = { 0 };

	virtual json ToJson()
	{
		json jsn;

		jsn[xorstr("WallPaper")]  = m_bWallPaper;
		jsn[xorstr("ShowTime")]   = m_bShowTime;
		jsn[xorstr("KillSound")]  = m_bKillSound;
		jsn[xorstr("SnowFlakes")] = m_bSnowFlakes;

		return jsn;
	};
	MiscSettings(const json& jsn)
	{
		m_bWallPaper  = jsn[xorstr("WallPaper")].get<bool>();
		m_bShowTime   = jsn[xorstr("ShowTime")].get<bool>();
		m_bKillSound  = jsn[xorstr("KillSound")].get<bool>();
		m_bSnowFlakes = jsn[xorstr("SnowFlakes")].get<bool>();
	}
};

class TriggerBotSettings : public CBaseSettings
{
public:
	TriggerBotSettings() {}
	bool m_bRageMode   = false;
	int  m_iDelay  = 0;

	virtual json ToJson()
	{
		json jsn;

		jsn[xorstr("Active")]   = m_bActive;
		jsn[xorstr("RageMode")] = m_bRageMode;
		jsn[xorstr("iDelay")]   = m_iDelay;

		return jsn;
	};
	TriggerBotSettings(const json& jsn)
	{
		m_bActive   = jsn[xorstr("Active")].get<bool>();
		m_bRageMode = jsn[xorstr("RageMode")].get<bool>();
		m_iDelay    = jsn[xorstr("iDelay")].get<int>();
	}
};
class BarEspSettings : public CBaseSettings
{
public:
	BarEspSettings()
	{
		m_bActive = true;
	}
	bool    m_bDrawHealthBar = false;
	bool    m_bDrawArmorBar = false;
	int     m_iThickness = 1;
	ImColor m_ArmorColor = ImColor(56, 122, 255);

	virtual json ToJson()
	{
		json jsn;

		jsn[xorstr("Active")]        = m_bActive;
		jsn[xorstr("DrawHealthBar")] = m_bDrawHealthBar;
		jsn[xorstr("DrawArmorBar")]  = m_bDrawArmorBar;
		jsn[xorstr("Thickness")]     = m_iThickness;
		jsn[xorstr("ArmorColor")]    = ImColorToJsn(m_ArmorColor);

		return jsn;
	};
	BarEspSettings(const json& jsn)
	{
		m_bActive        = jsn[xorstr("Active")].get<bool>();
		m_bDrawHealthBar = jsn[xorstr("DrawHealthBar")].get<bool>();
		m_bDrawArmorBar  = jsn[xorstr("DrawArmorBar")].get<bool>();
		m_iThickness     = jsn[xorstr("Thickness")].get<int>();
		m_ArmorColor     = ImportImColorFromJson(jsn[xorstr("ArmorColor")].get<json>());
	}
};
class CRadarSettings : public CBaseSettings
{
public:
	CRadarSettings() {}
	bool m_bDrawBorders = false;
	ImColor	m_ActiveFeatureColor   = ImColor(255, 0, 0);
	ImColor m_InactiveFeatureColor = ImColor(255, 255, 255);
	ImColor m_BackGroundColor      = ImColor(0, 0, 0, 30);
	ImColor m_CrossColor           = ImColor(255, 95, 95);
	ImColor m_CyrcleBorderColor    = ImColor(255, 95, 95);
	
	virtual json ToJson()
	{
		json jsn;

		jsn[xorstr("Active")]               = m_bActive;
		jsn[xorstr("ActiveFeatureColor")]   = ImColorToJsn(m_ActiveFeatureColor);
		jsn[xorstr("InactiveFeatureColor")] = ImColorToJsn(m_InactiveFeatureColor);
		jsn[xorstr("BackGroundColor")]      = ImColorToJsn(m_BackGroundColor);
		jsn[xorstr("CrossColor")]           = ImColorToJsn(m_CrossColor);
		jsn[xorstr("CyrcleBorderColor")]    = ImColorToJsn(m_CyrcleBorderColor);

		return jsn;
	};
};
class CLabelEspSettings : public CBaseSettings
{
public:
	CLabelEspSettings()
	{
		m_bActive = true;
	}
	bool m_bDrawName       = false;
	bool m_bDrawDistance   = false;
	bool m_bDrawHealth     = false;
	bool m_bDrawArmor      = false;
	bool m_bDrawVisibility = false;
	bool m_bDrawAimbot     = false;
	int  m_iIndexMin = 0;
	int  m_iIndexMax = 0;
	ImColor m_GlovesColor          = ImColor(255, 255, 255);
	ImColor m_NameLabelColor       = ImColor(255, 255, 255);
	ImColor m_DistanceLabelColor   = ImColor(255, 155, 5);
	ImColor m_ArmorLabelColor      = ImColor(56, 122, 255);
	ImColor m_VisibilityLabelColor = ImColor(0, 255, 208);

	virtual json ToJson()
	{
		json jsn;

		jsn[xorstr("Active")]         = m_bActive;
		jsn[xorstr("DrawDistance")]   = m_bDrawDistance;
		jsn[xorstr("DrawHealth")]     = m_bDrawHealth;
		jsn[xorstr("DrawArmor")]      = m_bDrawArmor;
		jsn[xorstr("DrawVisibility")] = m_bDrawVisibility;
		jsn[xorstr("DrawAimbot")]     = m_bDrawAimbot;

		jsn[xorstr("NameLabelColor")]       = ImColorToJsn(m_NameLabelColor);
		jsn[xorstr("DistanceLabelColor")]   = ImColorToJsn(m_DistanceLabelColor);
		jsn[xorstr("ArmorLabelColor")]      = ImColorToJsn(m_ArmorLabelColor);
		jsn[xorstr("VisibilityLabelColor")] = ImColorToJsn(m_VisibilityLabelColor);

		return jsn;
	};
	CLabelEspSettings(const json& jsn)
	{
		m_bDrawDistance   = jsn[xorstr("DrawDistance")].get<bool>();
		m_bDrawHealth     = jsn[xorstr("DrawHealth")].get<bool>();
		m_bDrawArmor      = jsn[xorstr("DrawArmor")].get<bool>();
		m_bDrawVisibility = jsn[xorstr("DrawVisibility")].get<bool>();
		m_bDrawAimbot     = jsn[xorstr("DrawAimbot")].get<bool>();

		m_NameLabelColor       = ImportImColorFromJson(jsn[xorstr("NameLabelColor")].get<json>());
		m_DistanceLabelColor   = ImportImColorFromJson(jsn[xorstr("DistanceLabelColor")].get<json>());
		m_ArmorLabelColor      = ImportImColorFromJson(jsn[xorstr("ArmorLabelColor")].get<json>());
		m_VisibilityLabelColor = ImportImColorFromJson(jsn[xorstr("VisibilityLabelColor")].get<json>());
	}
	//void Restore() override {};
};
class ChromaSettings
{
public:
	ChromaSettings() {}
	bool    m_bKillGlow     = false;
	ImColor m_KillGlowColor = ImColor(255, 0, 0);

};
class CBunnyHopSettings : public CBaseSettings
{
public:
	CBunnyHopSettings()
	{
		m_bOnKey = true;
		m_iBindKey = VK_SPACE;
	}
	int  m_iMaxPerfectJumps = 0;
	bool m_bLegitMode = false;
	int  m_iPerfectJumps = 0;

	virtual json ToJson()
	{
		json jsn;

		jsn[xorstr("Active")] = m_bActive;

		return jsn;
	};
	CBunnyHopSettings(const json& jsn)
	{
		m_bActive = jsn[xorstr("Active")].get<bool>();
	}
private:

};

struct SAllSettings
{
	char m_sName[32] = {0};
	AimBotSettings        m_AimBotSettings;
	SnapLinesSettings     m_SnapLinesSettings;
	BoxEspSetting	      m_BoxEspSettings;
	MiscSettings          m_MiscSettings;
	TriggerBotSettings    m_TriggerBotSettings;
	CRadarSettings        m_RadarSettings;
	CLabelEspSettings     m_LabelEspSettings;
	BarEspSettings        m_BarEspSettings;
	ChromaSettings		  m_ChromaSettings;
	CBunnyHopSettings     m_BunnyHopSettings;

	json ToJson()
	{
		json jsn;
		jsn[xorstr("Aimbot")]    = m_AimBotSettings.ToJson();
		jsn[xorstr("SnapLines")] = m_AimBotSettings.ToJson();
		jsn[xorstr("Boxes")]     = m_AimBotSettings.ToJson();
		jsn[xorstr("Misc")]      = m_AimBotSettings.ToJson();
		jsn[xorstr("TrigerBot")] = m_AimBotSettings.ToJson();
		jsn[xorstr("Radar")]     = m_AimBotSettings.ToJson();
		jsn[xorstr("Labels")]    = m_AimBotSettings.ToJson();
		jsn[xorstr("Bars")]      = m_AimBotSettings.ToJson();
		jsn[xorstr("BunnyHop")]  = m_AimBotSettings.ToJson();

		return jsn;
	}

};