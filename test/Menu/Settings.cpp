#pragma once
#include "Settings.h"
#include "../Utils/xorstr.h"
#include "../Utils/Marker.h"

using namespace Settings;

json CBaseSettings::ToJson() const
{
	json jsn;
	POLY_MARKER;

	jsn[xorstr("Active")]  = m_bActive;
	jsn[xorstr("OnKey")]   = m_bOnKey;
	jsn[xorstr("BindKey")] = m_iBindKey;

	return jsn;
};

json CAimBotSettings::ToJson() const
{
	json jsn;
	POLY_MARKER;
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
	jsn[xorstr("RcsControl")]       = m_bRcsControle;

	return jsn;
};
CAimBotSettings::CAimBotSettings(const json& jsn)
{	
	POLY_MARKER;
	SetValueIfFiledExistInJson<bool>(jsn,  xorstr("Active"),           &m_bActive);
	SetValueIfFiledExistInJson<bool>(jsn,  xorstr("OnKey"),            &m_bOnKey);
	SetValueIfFiledExistInJson<int>(jsn,   xorstr("BindKey"),          &m_iBindKey);
	SetValueIfFiledExistInJson<bool>(jsn,  xorstr("AutoShot"),         &m_bAutoShot);
	SetValueIfFiledExistInJson<bool>(jsn,  xorstr("Silent"),           &silent);
	SetValueIfFiledExistInJson<bool>(jsn,  xorstr("RcsControl"),       &m_bRcsControle);
	SetValueIfFiledExistInJson<float>(jsn, xorstr("Fov"),              &m_fFov);
	SetValueIfFiledExistInJson<float>(jsn, xorstr("Smooth"),           &m_fSmooth);
	SetValueIfFiledExistInJson<int>(jsn,   xorstr("SelectedHitBox"),   &m_iSelectedHitBox);
	SetValueIfFiledExistInJson<int>(jsn,   xorstr("PriorityType"),     &m_iPriorityType);
	SetValueIfFiledExistInJson<int>(jsn,   xorstr("HealthBorder"),     &m_iHealthBorder);
	SetValueIfFiledExistInJson<int>(jsn,   xorstr("HitBoxFilrerMode"), &m_iHitBoxFilterMode);
}
json SnapLinesSettings::ToJson() const
{
	json jsn;

	POLY_MARKER;

	jsn[xorstr("Active")] = m_bActive;
	jsn[xorstr("SelectedBone")] = m_iSelectedBone;
	jsn[xorstr("Color")] = ImColorToJsn(m_Color);
	jsn[xorstr("DrawMode")] = m_iDrawMode;
	jsn[xorstr("Thickness")] = m_iThickness;

	return jsn;
};
SnapLinesSettings::SnapLinesSettings(const json& jsn)
{
	POLY_MARKER;

	SetValueIfFiledExistInJson<bool>(jsn, xorstr("Active"), &m_bActive);
	SetValueIfFiledExistInJson<int>(jsn,  xorstr("SelectedBone"), &m_iSelectedBone);
	SetValueIfFiledExistInJson<int>(jsn,  xorstr("DrawMode"), &m_iDrawMode);
	SetValueIfFiledExistInJson<int>(jsn, xorstr("Thickness"), &m_iThickness);
	SetValueIfFiledExistInJson(jsn, xorstr("Color"), &m_Color);
}
json BoxEspSettings::ToJson() const
{
	json jsn;

	POLY_MARKER;

	jsn[xorstr("Active")] = m_bActive;
	jsn[xorstr("Color")] = ImColorToJsn(m_Color);
	jsn[xorstr("Style")] = m_iStyle;
	jsn[xorstr("DrawMode")] = m_iDrawMode;
	jsn[xorstr("Thickness")] = m_iThickness;

	return jsn;
};

BoxEspSettings::BoxEspSettings(const json& jsn)
{

	POLY_MARKER;

	SetValueIfFiledExistInJson<bool>(jsn, xorstr("Active"), &m_bActive);
	SetValueIfFiledExistInJson<int>(jsn, xorstr("Style"), &m_iStyle);
	SetValueIfFiledExistInJson(jsn, xorstr("Color"), &m_Color);
	SetValueIfFiledExistInJson<int>(jsn, xorstr("DrawMode"), &m_iDrawMode);
	SetValueIfFiledExistInJson<int>(jsn, xorstr("Thickness"), &m_iThickness);
}

json MiscSettings::ToJson() const
{
	json jsn;

	POLY_MARKER;

	jsn[xorstr("WallPaper")] = m_bWallPaper;
	jsn[xorstr("ShowTime")] = m_bShowTime;
	jsn[xorstr("KillSound")] = m_bKillSound;
	jsn[xorstr("SnowFlakes")] = m_bSnowFlakes;
	jsn[xorstr("CustomFov")]  = m_iCustomFov;
	return jsn;
};

MiscSettings::MiscSettings(const json& jsn)
{
	POLY_MARKER;

	SetValueIfFiledExistInJson<bool>(jsn, xorstr("WallPaper"), &m_bWallPaper);
	SetValueIfFiledExistInJson<bool>(jsn, xorstr("ShowTime"), &m_bShowTime);
	SetValueIfFiledExistInJson<bool>(jsn, xorstr("KillSound"), &m_bKillSound);
	SetValueIfFiledExistInJson<bool>(jsn, xorstr("SnowFlakes"), &m_bSnowFlakes);
	SetValueIfFiledExistInJson<int>(jsn, xorstr("CustomFov"), &m_iCustomFov);
}

json TriggerBotSettings::ToJson() const
{
	json jsn;

	POLY_MARKER;

	jsn[xorstr("Active")] = m_bActive;
	jsn[xorstr("RageMode")] = m_bRageMode;
	jsn[xorstr("iDelay")] = m_iDelay;

	return jsn;
};
TriggerBotSettings::TriggerBotSettings(const json& jsn)
{

	POLY_MARKER;

	SetValueIfFiledExistInJson<bool>(jsn, xorstr("Active"), &m_bActive);
	SetValueIfFiledExistInJson<bool>(jsn, xorstr("RageMode"), &m_bRageMode);
	SetValueIfFiledExistInJson<int>(jsn, xorstr("iDelay"), &m_iDelay);
}

json BarEspSettings::ToJson() const
{
	json jsn;

	POLY_MARKER;

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
	POLY_MARKER;

	SetValueIfFiledExistInJson<bool>(jsn, xorstr("Active"),          &m_bActive);
	SetValueIfFiledExistInJson<bool>(jsn, xorstr("DrawHealthBar"),   &m_bDrawHealthBar);
	SetValueIfFiledExistInJson<bool>(jsn, xorstr("DrawArmorBar"),    &m_bDrawArmorBar);
	SetValueIfFiledExistInJson<int>(jsn,  xorstr("Thickness"),       &m_iThickness);
	SetValueIfFiledExistInJson(jsn,       xorstr("ArmorColor"),      &m_ArmorColor);
	SetValueIfFiledExistInJson(jsn,       xorstr("BackGroundColor"), &m_BackGroundColor);
}

json CRadarSettings::ToJson() const
{
	json jsn;

	POLY_MARKER;

	jsn[xorstr("Active")] = m_bActive;
	jsn[xorstr("ActiveFeatureColor")] = ImColorToJsn(m_ActiveFeatureColor);
	jsn[xorstr("InactiveFeatureColor")] = ImColorToJsn(m_InactiveFeatureColor);
	jsn[xorstr("BackGroundColor")] = ImColorToJsn(m_BackGroundColor);
	jsn[xorstr("CrossColor")]        = ImColorToJsn(m_CrossColor);
	jsn[xorstr("Style")]             = m_iStyle;
	jsn[xorstr("CyrcleBorderColor")] = ImColorToJsn(m_CyrcleBorderColor);

	return jsn;
};

json CLabelEspSettings::ToJson() const
{
	json jsn;

	POLY_MARKER;

	std::vector<json> lablesJson;
	jsn[xorstr("iDrawPos")] = m_iDrawPos;

	POLY_MARKER;

	for (auto pLabel : m_Labels)
	{
		json labelJson;
		labelJson[xorstr("bActive")]   = pLabel->m_bActive;
		labelJson[xorstr("Color")]     = ImColorToJsn(pLabel->m_Color);
		labelJson[xorstr("Name")]      = pLabel->m_sName;
		labelJson[xorstr("Type")]      = pLabel->GetTypeId();

		lablesJson.push_back(labelJson);

	}
	jsn[xorstr("Labels")] = lablesJson;

	return jsn;
};
CLabelEspSettings::CLabelEspSettings(const json& jsn)
{
	POLY_MARKER;
	SetValueIfFiledExistInJson<int>(jsn, xorstr("iDrawPos"), &m_iDrawPos);

	if (!jsn.contains(xorstr("Labels")))
		return;

	POLY_MARKER;

	for (auto& jsnLabel : jsn[xorstr("Labels")].get<std::vector<json>>())
	{
		CLabels::CBaseLabel* pLabel = nullptr;
		
		switch (jsnLabel["Type"].get<int>())
		{
		case CLabels::LabelTypeId::Name:
			pLabel = new CLabels::CNameLabel(jsnLabel[xorstr("Name")].get<std::string>(),
				jsnLabel[xorstr("bActive")].get<bool>(), ImportImColorFromJson(jsnLabel[xorstr("Color")].get<json>()));
			break;
		case CLabels::LabelTypeId::Heatlh:
			pLabel = new CLabels::CHealthLabel(jsnLabel[xorstr("Name")].get<std::string>(),
				jsnLabel[xorstr("bActive")].get<bool>());
			break;
		case CLabels::LabelTypeId::Distance:
			pLabel = new CLabels::CDistanceLabel(jsnLabel[xorstr("Name")].get<std::string>(),
				jsnLabel[xorstr("bActive")].get<bool>(), ImportImColorFromJson(jsnLabel[xorstr("Color")].get<json>()));
			break;
		case CLabels::LabelTypeId::Armor:
			pLabel = new CLabels::CArmorLabel(jsnLabel[xorstr("Name")].get<std::string>(),
				jsnLabel[xorstr("bActive")].get<bool>(), ImportImColorFromJson(jsnLabel[xorstr("Color")].get<json>()));
			break;
		case CLabels::LabelTypeId::Visibility:
			pLabel = new CLabels::CVisibilityLabel(jsnLabel[xorstr("Name")].get<std::string>(),
				jsnLabel[xorstr("bActive")].get<bool>(), ImportImColorFromJson(jsnLabel[xorstr("Color")].get<json>()));
			break;
		case CLabels::LabelTypeId::AimbotTarget:
			pLabel = new CLabels::CAimBotTargetLabel(jsnLabel[xorstr("Name")].get<std::string>(),
				jsnLabel[xorstr("bActive")].get<bool>(), ImportImColorFromJson(jsnLabel[xorstr("Color")].get<json>()));
			break;
		}
		if (pLabel)
			m_Labels.push_back(std::shared_ptr<CLabels::CBaseLabel>(pLabel));
	}
}

json CBunnyHopSettings::ToJson() const
{
	json jsn;

	jsn[xorstr("Active")] = m_bActive;

	return jsn;
};
CBunnyHopSettings::CBunnyHopSettings(const json& jsn) : CBunnyHopSettings::CBunnyHopSettings()
{
	POLY_MARKER;
	SetValueIfFiledExistInJson<bool>(jsn, xorstr("Active"), &m_bActive);
}
Settings::CAllSettings::CAllSettings(const json& jsn)
{

	POLY_MARKER;
	m_AimBotSettings     = Settings::CAimBotSettings(jsn[xorstr("AimBot")].get<nlohmann::json>());
	m_BarEspSettings     = Settings::BarEspSettings(jsn[xorstr("BarEsp")].get<nlohmann::json>());
	m_BoxEspSettings     = Settings::BoxEspSettings(jsn[xorstr("BoxEsp")].get<nlohmann::json>());
	m_BunnyHopSettings   = Settings::CBunnyHopSettings(jsn[xorstr("BunnyHop")].get<nlohmann::json>());
	m_LabelEspSettings   = Settings::CLabelEspSettings(jsn[xorstr("LabelEsp")].get<nlohmann::json>());
	m_MiscSettings       = Settings::MiscSettings(jsn[xorstr("Misc")].get<nlohmann::json>());
	m_RadarSettings      = Settings::CRadarSettings(jsn[xorstr("Radar")].get<nlohmann::json>());
	m_SnapLinesSettings  = Settings::SnapLinesSettings(jsn[xorstr("SnapLinesEsp")].get<nlohmann::json>());
	m_TriggerBotSettings = Settings::TriggerBotSettings(jsn[xorstr("TriggerBot")].get<nlohmann::json>());

	POLY_MARKER;
	auto tmp = jsn[xorstr("CfgName")].get<std::string>();
	m_Name = std::string(tmp.c_str(), 32);
}
json CAllSettings::ToJson()
{
	json jsn;

	POLY_MARKER;

	jsn[xorstr("CfgName")]      = m_Name.c_str();
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

	POLY_MARKER;

	SetValueIfFiledExistInJson<int>(jsn, xorstr("Style"), &m_iStyle);
	SetValueIfFiledExistInJson<bool>(jsn, xorstr("Active"), &m_bActive);

	SetValueIfFiledExistInJson(jsn, xorstr("ActiveFeatureColor"), &m_ActiveFeatureColor);
	SetValueIfFiledExistInJson(jsn, xorstr("InactiveFeatureColor"), &m_InactiveFeatureColor);
	SetValueIfFiledExistInJson(jsn, xorstr("BackGroundColor"), &m_BackGroundColor);
	SetValueIfFiledExistInJson(jsn, xorstr("CrossColor"), &m_CrossColor);
	SetValueIfFiledExistInJson(jsn, xorstr("CyrcleBorderColor"), &m_CyrcleBorderColor);
}