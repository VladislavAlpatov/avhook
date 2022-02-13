#include "Settings.h"


json CBaseSettings::ToJson()
{
	json jsn;

	jsn[xorstr("Active")] = m_bActive;
	jsn[xorstr("OnKey")] = m_bOnKey;
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

json AimBotSettings::ToJson()
{
	json jsn;

	jsn[xorstr("Active")] = m_bActive;
	jsn[xorstr("OnKey")] = m_bOnKey;
	jsn[xorstr("BindKey")] = m_iBindKey;
	jsn[xorstr("AutoShot")] = m_bAutoShot;
	jsn[xorstr("Silent")] = silent;
	jsn[xorstr("Fov")] = m_fFov;
	jsn[xorstr("Smooth")] = m_fSmooth;
	jsn[xorstr("SelectedHitBox")] = m_iSelectedHitBox;
	jsn[xorstr("PriorityType")] = m_iPriorityType;
	return jsn;
};
AimBotSettings::AimBotSettings(const json& jsn)
{
	m_bActive = jsn[xorstr("Active")].get<bool>();
	m_bOnKey = jsn[xorstr("OnKey")].get<int>();
	m_iBindKey = jsn[xorstr("BindKey")].get<int>();
	m_bAutoShot = jsn[xorstr("AutoShot")].get<bool>();
	silent = jsn[xorstr("Silent")].get<bool>();
	m_fFov = jsn[xorstr("Fov")].get<float>();
	m_fSmooth = jsn[xorstr("Smooth")].get<float>();
	m_iSelectedHitBox = jsn[xorstr("SelectedHitBox")].get<int>();
	m_iPriorityType = jsn[xorstr("PriorityType")].get<int>();
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
json BoxEspSetting::ToJson()
{
	json jsn;

	jsn[xorstr("Active")] = m_bActive;
	jsn[xorstr("Color")] = ImColorToJsn(m_Color);
	jsn[xorstr("DrawMode")] = m_iDrawMode;
	jsn[xorstr("Thickness")] = m_iThickness;

	return jsn;
};
BoxEspSetting::BoxEspSetting(const json& jsn)
{
	m_bActive     = jsn[xorstr("Active")].get<bool>();

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

	return jsn;
};
MiscSettings::MiscSettings(const json& jsn)
{
	m_bWallPaper = jsn[xorstr("WallPaper")].get<bool>();
	m_bShowTime = jsn[xorstr("ShowTime")].get<bool>();
	m_bKillSound = jsn[xorstr("KillSound")].get<bool>();
	m_bSnowFlakes = jsn[xorstr("SnowFlakes")].get<bool>();
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

	return jsn;
};
BarEspSettings::BarEspSettings(const json& jsn)
{
	m_bActive = jsn[xorstr("Active")].get<bool>();
	m_bDrawHealthBar = jsn[xorstr("DrawHealthBar")].get<bool>();
	m_bDrawArmorBar = jsn[xorstr("DrawArmorBar")].get<bool>();
	m_iThickness = jsn[xorstr("Thickness")].get<int>();
	m_ArmorColor = ImportImColorFromJson(jsn[xorstr("ArmorColor")].get<json>());
}

json CRadarSettings::ToJson()
{
	json jsn;

	jsn[xorstr("Active")] = m_bActive;
	jsn[xorstr("ActiveFeatureColor")] = ImColorToJsn(m_ActiveFeatureColor);
	jsn[xorstr("InactiveFeatureColor")] = ImColorToJsn(m_InactiveFeatureColor);
	jsn[xorstr("BackGroundColor")] = ImColorToJsn(m_BackGroundColor);
	jsn[xorstr("CrossColor")] = ImColorToJsn(m_CrossColor);
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
	jsn[xorstr("DrawVisibility")] = m_bDrawVisibility;
	jsn[xorstr("DrawAimbot")] = m_bDrawAimbot;

	jsn[xorstr("NameLabelColor")] = ImColorToJsn(m_NameLabelColor);
	jsn[xorstr("DistanceLabelColor")] = ImColorToJsn(m_DistanceLabelColor);
	jsn[xorstr("ArmorLabelColor")] = ImColorToJsn(m_ArmorLabelColor);
	jsn[xorstr("VisibilityLabelColor")] = ImColorToJsn(m_VisibilityLabelColor);

	return jsn;
};
CLabelEspSettings::CLabelEspSettings(const json& jsn)
{
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
CBunnyHopSettings::CBunnyHopSettings(const json& jsn)
{
	m_bActive = jsn[xorstr("Active")].get<bool>();
}
json SAllSettings::ToJson()
{
	json jsn;
	jsn[xorstr("Aimbot")] = m_AimBotSettings.ToJson();
	jsn[xorstr("SnapLines")] = m_AimBotSettings.ToJson();
	jsn[xorstr("Boxes")] = m_AimBotSettings.ToJson();
	jsn[xorstr("Misc")] = m_AimBotSettings.ToJson();
	jsn[xorstr("TrigerBot")] = m_AimBotSettings.ToJson();
	jsn[xorstr("Radar")] = m_AimBotSettings.ToJson();
	jsn[xorstr("Labels")] = m_AimBotSettings.ToJson();
	jsn[xorstr("Bars")] = m_AimBotSettings.ToJson();
	jsn[xorstr("BunnyHop")] = m_AimBotSettings.ToJson();

	return jsn;
}