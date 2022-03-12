#include "Settings.h"

using namespace Settings;

json CBaseSettings::ToJson()
{
	json jsn;

	jsn[xorstr("Active")]  = m_bActive;
	jsn[xorstr("OnKey")]   = m_bOnKey;
	jsn[xorstr("BindKey")] = m_iBindKey;

	return jsn;
};

json CBaseSettings::ImColorToJsn(const ImColor& color)
{
	json jsn;

	jsn[xorstr("R")] = color.Value.x;
	jsn[xorstr("G")] = color.Value.y;
	jsn[xorstr("B")] = color.Value.z;
	jsn[xorstr("A")] = color.Value.w;

	return jsn;
}

ImColor CBaseSettings::ImportImColorFromJson(const json& jsn)
{
	return ImColor(
		jsn[xorstr("R")].get<float>(),
		jsn[xorstr("G")].get<float>(),
		jsn[xorstr("B")].get<float>(),
		jsn[xorstr("A")].get<float>()
	);
}

json CAimBotSettings::ToJson()
{
	json jsn;

	jsn[xorstr("Active")]           = m_bActive;
	jsn[xorstr("OnKey")]            = m_bOnKey;
	jsn[xorstr("BindKey")]          = m_iBindKey;
	jsn[xorstr("AutoShot")]         = m_bAutoShot;
	jsn[xorstr("Silent")]           = silent;
	jsn[xorstr("Fov")]              = m_fFov;
	jsn[xorstr("Smooth")]           = m_fSmooth;
	jsn[xorstr("SelectedHitBox")]   = m_iSelectedHitBox;
	jsn[xorstr("PriorityType")]     = m_iPriorityType;
	jsn[xorstr("HealthBorder")]     = m_iHealthBorder;
	jsn[xorstr("HitBoxFilrerMode")] = m_iHitBoxFilterMode;

	return jsn;
};
CAimBotSettings::CAimBotSettings(const json& jsn)
{
	m_bActive           = jsn[xorstr("Active")].get<bool>();
	m_bOnKey            = jsn[xorstr("OnKey")].get<int>();
	m_iBindKey          = jsn[xorstr("BindKey")].get<int>();
	m_bAutoShot         = jsn[xorstr("AutoShot")].get<bool>();
	silent              = jsn[xorstr("Silent")].get<bool>();
	m_fFov              = jsn[xorstr("Fov")].get<float>();
	m_fSmooth           = jsn[xorstr("Smooth")].get<float>();
	m_iSelectedHitBox   = jsn[xorstr("SelectedHitBox")].get<int>();
	m_iPriorityType     = jsn[xorstr("PriorityType")].get<int>();
	m_iHealthBorder     = jsn[xorstr("HealthBorder")].get<int>();
	m_iHitBoxFilterMode = jsn[xorstr("HitBoxFilrerMode")].get<int>();
}
json SnapLinesSettings::ToJson()
{
	json jsn;

	jsn[xorstr("Active")] = m_bActive;
	jsn[xorstr("SelectedBone")] = m_iSelectedBone;
	jsn[xorstr("Color")] = ImColorToJsn(m_Color);
	jsn[xorstr("DrawMode")] = m_iDrawMode;
	jsn[xorstr("Thickness")] = m_iThickness;

	return jsn;
};
SnapLinesSettings::SnapLinesSettings(const json& jsn)
{
	m_bActive = jsn[xorstr("Active")].get<bool>();
	m_iSelectedBone = jsn[xorstr("SelectedBone")].get<int>();
	m_Color = ImportImColorFromJson(jsn[xorstr("Color")]);
	m_iDrawMode = jsn[xorstr("DrawMode")].get<int>();
	m_iThickness = jsn[xorstr("Thickness")].get<int>();
}
json BoxEspSettings::ToJson()
{
	json jsn;

	jsn[xorstr("Active")] = m_bActive;
	jsn[xorstr("Color")] = ImColorToJsn(m_Color);
	jsn[xorstr("Style")] = m_iStyle;
	jsn[xorstr("DrawMode")] = m_iDrawMode;
	jsn[xorstr("Thickness")] = m_iThickness;

	return jsn;
};
BoxEspSettings::BoxEspSettings(const json& jsn)
{
	m_bActive    = jsn[xorstr("Active")].get<bool>();
	m_iStyle	 = jsn[xorstr("Style")].get<int>();
	m_Color      = ImportImColorFromJson(jsn[xorstr("Color")]);
	m_iDrawMode  = jsn[xorstr("DrawMode")].get<int>();
	m_iThickness = jsn[xorstr("Thickness")].get<int>();
}

json MiscSettings::ToJson()
{
	json jsn;

	jsn[xorstr("WallPaper")] = m_bWallPaper;
	jsn[xorstr("ShowTime")] = m_bShowTime;
	jsn[xorstr("KillSound")] = m_bKillSound;
	jsn[xorstr("SnowFlakes")] = m_bSnowFlakes;
	jsn[xorstr("CustomFov")]  = m_iCustomFov;
	return jsn;
};
MiscSettings::MiscSettings(const json& jsn)
{
	m_bWallPaper = jsn[xorstr("WallPaper")].get<bool>();
	m_bShowTime = jsn[xorstr("ShowTime")].get<bool>();
	m_bKillSound = jsn[xorstr("KillSound")].get<bool>();
	m_bSnowFlakes = jsn[xorstr("SnowFlakes")].get<bool>();
	m_iCustomFov  = jsn[xorstr("CustomFov")].get<int>();
}

json TriggerBotSettings::ToJson()
{
	json jsn;

	jsn[xorstr("Active")] = m_bActive;
	jsn[xorstr("RageMode")] = m_bRageMode;
	jsn[xorstr("iDelay")] = m_iDelay;

	return jsn;
};
TriggerBotSettings::TriggerBotSettings(const json& jsn)
{
	m_bActive = jsn[xorstr("Active")].get<bool>();
	m_bRageMode = jsn[xorstr("RageMode")].get<bool>();
	m_iDelay = jsn[xorstr("iDelay")].get<int>();
}

json BarEspSettings::ToJson()
{
	json jsn;

	jsn[xorstr("Active")] = m_bActive;
	jsn[xorstr("DrawHealthBar")] = m_bDrawHealthBar;
	jsn[xorstr("DrawArmorBar")] = m_bDrawArmorBar;
	jsn[xorstr("Thickness")] = m_iThickness;
	jsn[xorstr("ArmorColor")] = ImColorToJsn(m_ArmorColor);
	jsn[xorstr("BackGroundColor")] = ImColorToJsn(m_BackGroundColor);

	return jsn;
};
BarEspSettings::BarEspSettings(const json& jsn)
{
	m_bActive         = jsn[xorstr("Active")].get<bool>();
	m_bDrawHealthBar  = jsn[xorstr("DrawHealthBar")].get<bool>();
	m_bDrawArmorBar   = jsn[xorstr("DrawArmorBar")].get<bool>();
	m_iThickness      = jsn[xorstr("Thickness")].get<int>();
	m_ArmorColor      = ImportImColorFromJson(jsn[xorstr("ArmorColor")].get<json>());
	m_BackGroundColor = ImportImColorFromJson(jsn[xorstr("BackGroundColor")].get<json>());
}

json CRadarSettings::ToJson()
{
	json jsn;

	jsn[xorstr("Active")] = m_bActive;
	jsn[xorstr("ActiveFeatureColor")] = ImColorToJsn(m_ActiveFeatureColor);
	jsn[xorstr("InactiveFeatureColor")] = ImColorToJsn(m_InactiveFeatureColor);
	jsn[xorstr("BackGroundColor")] = ImColorToJsn(m_BackGroundColor);
	jsn[xorstr("CrossColor")] = ImColorToJsn(m_CrossColor);
	jsn[xorstr("Style")] = m_iStyle;
	jsn[xorstr("CyrcleBorderColor")] = ImColorToJsn(m_CyrcleBorderColor);

	return jsn;
};

json CLabelEspSettings::ToJson()
{
	json jsn;

	jsn[xorstr("Active")] = m_bActive;
	jsn[xorstr("DrawDistance")] = m_bDrawDistance;
	jsn[xorstr("DrawHealth")] = m_bDrawHealth;
	jsn[xorstr("DrawArmor")] = m_bDrawArmor;
	jsn[xorstr("DrawName")] = m_bDrawName;
	jsn[xorstr("DrawVisibility")] = m_bDrawVisibility;
	jsn[xorstr("DrawAimbot")] = m_bDrawAimbot;

	jsn[xorstr("NameLabelColor")] = ImColorToJsn(m_NameLabelColor);
	jsn[xorstr("DistanceLabelColor")] = ImColorToJsn(m_DistanceLabelColor);
	jsn[xorstr("ArmorLabelColor")] = ImColorToJsn(m_ArmorLabelColor);
	jsn[xorstr("VisibilityLabelColor")] = ImColorToJsn(m_VisibilityLabelColor);

	return jsn;
};
CLabelEspSettings::CLabelEspSettings(const json& jsn) : CLabelEspSettings::CLabelEspSettings()
{
	m_bDrawName = jsn[xorstr("DrawName")].get<bool>();
	m_bDrawDistance = jsn[xorstr("DrawDistance")].get<bool>();
	m_bDrawHealth = jsn[xorstr("DrawHealth")].get<bool>();
	m_bDrawArmor = jsn[xorstr("DrawArmor")].get<bool>();
	m_bDrawVisibility = jsn[xorstr("DrawVisibility")].get<bool>();
	m_bDrawAimbot = jsn[xorstr("DrawAimbot")].get<bool>();

	m_NameLabelColor = ImportImColorFromJson(jsn[xorstr("NameLabelColor")].get<json>());
	m_DistanceLabelColor = ImportImColorFromJson(jsn[xorstr("DistanceLabelColor")].get<json>());
	m_ArmorLabelColor = ImportImColorFromJson(jsn[xorstr("ArmorLabelColor")].get<json>());
	m_VisibilityLabelColor = ImportImColorFromJson(jsn[xorstr("VisibilityLabelColor")].get<json>());
}

json CBunnyHopSettings::ToJson()
{
	json jsn;

	jsn[xorstr("Active")] = m_bActive;

	return jsn;
};
CBunnyHopSettings::CBunnyHopSettings(const json& jsn) : CBunnyHopSettings::CBunnyHopSettings()
{
	m_bActive = jsn[xorstr("Active")].get<bool>();
}
Settings::CAllSettings::CAllSettings(const json& jsn)
{
	m_AimBotSettings = Settings::CAimBotSettings(jsn[xorstr("AimBot")].get<nlohmann::json>());
	m_BarEspSettings = Settings::BarEspSettings(jsn[xorstr("BarEsp")].get<nlohmann::json>());
	m_BoxEspSettings = Settings::BoxEspSettings(jsn[xorstr("BoxEsp")].get<nlohmann::json>());
	m_BunnyHopSettings = Settings::CBunnyHopSettings(jsn[xorstr("BunnyHop")].get<nlohmann::json>());
	m_LabelEspSettings = Settings::CLabelEspSettings(jsn[xorstr("LabelEsp")].get<nlohmann::json>());
	m_MiscSettings = Settings::MiscSettings(jsn[xorstr("Misc")].get<nlohmann::json>());
	m_RadarSettings = Settings::CRadarSettings(jsn[xorstr("Radar")].get<nlohmann::json>());
	m_SnapLinesSettings = Settings::SnapLinesSettings(jsn[xorstr("SnapLinesEsp")].get<nlohmann::json>());
	m_TriggerBotSettings = Settings::TriggerBotSettings(jsn[xorstr("TriggerBot")].get<nlohmann::json>());
}
json CAllSettings::ToJson()
{
	json jsn;

	jsn[xorstr("AimBot")]       = m_AimBotSettings.ToJson();
	jsn[xorstr("BarEsp")]       = m_BarEspSettings.ToJson();
	jsn[xorstr("BoxEsp")]       = m_BoxEspSettings.ToJson();
	jsn[xorstr("BunnyHop")]     = m_BunnyHopSettings.ToJson();
	jsn[xorstr("LabelEsp")]     = m_LabelEspSettings.ToJson();
	jsn[xorstr("Misc")]         = m_MiscSettings.ToJson();
	jsn[xorstr("Radar")]        = m_RadarSettings.ToJson();
	jsn[xorstr("SnapLinesEsp")] = m_SnapLinesSettings.ToJson();
	jsn[xorstr("TriggerBot")]   = m_TriggerBotSettings.ToJson();
	return jsn;
}
CRadarSettings::CRadarSettings(const json& jsn)
{
	m_iStyle               = jsn[xorstr("Style")].get<int>();
	m_bActive              = jsn[xorstr("Active")].get<bool>();
	m_ActiveFeatureColor   = ImportImColorFromJson(jsn[xorstr("ActiveFeatureColor")].get<json>());
	m_InactiveFeatureColor = ImportImColorFromJson(jsn[xorstr("InactiveFeatureColor")].get<json>());
	m_BackGroundColor      = ImportImColorFromJson(jsn[xorstr("BackGroundColor")].get<json>());
	m_CrossColor           = ImportImColorFromJson(jsn[xorstr("CrossColor")].get<json>());
	m_CyrcleBorderColor	   = ImportImColorFromJson(jsn[xorstr("CyrcleBorderColor")].get<json>());
}