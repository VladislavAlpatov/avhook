/*
 * Copyright (c) 2022.
 * Created by Alpatov Softworks with love in Russia.
 */

#include "Settings.h"
#include "../Utils/xorstr.h"
#include "../Utils/Marker.h"


nlohmann::json Settings::CBaseSettings::ToJson() const
{
	nlohmann::json jsn;
	POLY_MARKER;

	jsn[xorstr("Active")] = m_bActive;
	jsn[xorstr("OnKey")] = m_bOnKey;
	jsn[xorstr("BindKey")] = m_iBindKey;
	
	return jsn;
}


Settings::CAimBotSettings::CAimBotSettings()
{
	POLY_MARKER;
	m_bAutoShot = false;
	m_bSilent = false;
	m_bIsWorking = false;
	m_bRcsControle = false;
	m_fFov = 10.f;
	m_fSmooth = 0.f;
	POLY_MARKER;
	m_iSelectedHitBox = 0;
	m_iPriorityType = 0;
	m_pCurrentTarget = nullptr;
	m_iHealthBorder = 50;
	m_iHitBoxFilterMode = 0;
}


nlohmann::json Settings::CAimBotSettings::ToJson() const
{
	nlohmann::json jsn;
	POLY_MARKER;
	jsn[xorstr("Active")] = m_bActive;
	jsn[xorstr("OnKey")] = m_bOnKey;
	jsn[xorstr("BindKey")] = m_iBindKey;
	jsn[xorstr("AutoShot")] = m_bAutoShot;
	jsn[xorstr("Silent")] = m_bSilent;
	jsn[xorstr("Fov")] = m_fFov;
	jsn[xorstr("Smooth")] = m_fSmooth;
	jsn[xorstr("SelectedHitBox")] = m_iSelectedHitBox;
	jsn[xorstr("PriorityType")] = m_iPriorityType;
	jsn[xorstr("HealthBorder")] = m_iHealthBorder;
	jsn[xorstr("HitBoxFilrerMode")] = m_iHitBoxFilterMode;
	jsn[xorstr("RcsControl")] = m_bRcsControle;

	return jsn;
};

Settings::CAimBotSettings::CAimBotSettings(const nlohmann::json& jsn)
{
	POLY_MARKER;
	SetValueIfFiledExistInJson<bool>(jsn,  xorstr("Active"),           &m_bActive);
	SetValueIfFiledExistInJson<bool>(jsn,  xorstr("OnKey"),            &m_bOnKey);
	SetValueIfFiledExistInJson<int>(jsn,   xorstr("BindKey"),          &m_iBindKey);
	SetValueIfFiledExistInJson<bool>(jsn,  xorstr("AutoShot"),         &m_bAutoShot);
	SetValueIfFiledExistInJson<bool>(jsn,  xorstr("Silent"),           &m_bSilent);
	SetValueIfFiledExistInJson<bool>(jsn,  xorstr("RcsControl"),       &m_bRcsControle);
	SetValueIfFiledExistInJson<float>(jsn, xorstr("Fov"),              &m_fFov);
	SetValueIfFiledExistInJson<float>(jsn, xorstr("Smooth"),           &m_fSmooth);
	SetValueIfFiledExistInJson<int>(jsn,   xorstr("SelectedHitBox"),   &m_iSelectedHitBox);
	SetValueIfFiledExistInJson<int>(jsn,   xorstr("PriorityType"),     &m_iPriorityType);
	SetValueIfFiledExistInJson<int>(jsn,   xorstr("HealthBorder"),     &m_iHealthBorder);
	SetValueIfFiledExistInJson<int>(jsn,   xorstr("HitBoxFilrerMode"), &m_iHitBoxFilterMode);
}

nlohmann::json Settings::SnapLinesSettings::ToJson() const
{
	nlohmann::json jsn;

	POLY_MARKER;

	jsn[xorstr("Active")] = m_bActive;
	jsn[xorstr("SelectedBone")] = m_iSelectedBone;
	jsn[xorstr("Color")] = ImColorToJsn(m_Color);
	jsn[xorstr("DrawMode")] = m_iDrawMode;
	jsn[xorstr("Thickness")] = m_iThickness;

	return jsn;
};

Settings::SnapLinesSettings::SnapLinesSettings(const nlohmann::json& jsn)
{
	POLY_MARKER;

	SetValueIfFiledExistInJson<bool>(jsn, xorstr("Active"), &m_bActive);
	SetValueIfFiledExistInJson<int>(jsn, xorstr("SelectedBone"), &m_iSelectedBone);
	SetValueIfFiledExistInJson<int>(jsn, xorstr("DrawMode"), &m_iDrawMode);
	SetValueIfFiledExistInJson<int>(jsn, xorstr("Thickness"), &m_iThickness);
	SetValueIfFiledExistInJson(jsn, xorstr("Color"), &m_Color);
}

nlohmann::json Settings::BoxEspSettings::ToJson() const
{
	nlohmann::json jsn;

	POLY_MARKER;

	jsn[xorstr("Active")] = m_bActive;
	jsn[xorstr("Color")] = ImColorToJsn(m_Color);
	jsn[xorstr("Style")] = m_iStyle;
	jsn[xorstr("DrawMode")] = m_iDrawMode;
	jsn[xorstr("Thickness")] = m_iThickness;

	return jsn;
};

Settings::BoxEspSettings::BoxEspSettings(const nlohmann::json& jsn)
{
	POLY_MARKER;

	SetValueIfFiledExistInJson<bool>(jsn, xorstr("Active"), &m_bActive);
	SetValueIfFiledExistInJson<int>(jsn, xorstr("Style"), &m_iStyle);
	SetValueIfFiledExistInJson(jsn, xorstr("Color"), &m_Color);
	SetValueIfFiledExistInJson<int>(jsn, xorstr("DrawMode"), &m_iDrawMode);
	SetValueIfFiledExistInJson<int>(jsn, xorstr("Thickness"), &m_iThickness);
}

nlohmann::json Settings::MiscSettings::ToJson() const
{
	nlohmann::json jsn;

	POLY_MARKER;

	jsn[xorstr("WallPaper")] = m_bWallPaper;
	jsn[xorstr("ShowTime")] = m_bShowTime;
	jsn[xorstr("KillSound")] = m_bKillSound;
	jsn[xorstr("SnowFlakes")] = m_bSnowFlakes;
	jsn[xorstr("CustomFov")] = m_iCustomFov;
	return jsn;
};

Settings::MiscSettings::MiscSettings(const nlohmann::json& jsn)
{
	POLY_MARKER;

	SetValueIfFiledExistInJson<bool>(jsn, xorstr("WallPaper"), &m_bWallPaper);
	SetValueIfFiledExistInJson<bool>(jsn, xorstr("ShowTime"), &m_bShowTime);
	SetValueIfFiledExistInJson<bool>(jsn, xorstr("KillSound"), &m_bKillSound);
	SetValueIfFiledExistInJson<bool>(jsn, xorstr("SnowFlakes"), &m_bSnowFlakes);
	SetValueIfFiledExistInJson<int>(jsn, xorstr("CustomFov"), &m_iCustomFov);
}

nlohmann::json Settings::TriggerBotSettings::ToJson() const
{
	nlohmann::json jsn;

	POLY_MARKER;

	jsn[xorstr("Active")] = m_bActive;
	jsn[xorstr("RageMode")] = m_bRageMode;
	jsn[xorstr("iDelay")] = m_iDelay;

	return jsn;
};

Settings::TriggerBotSettings::TriggerBotSettings(const nlohmann::json& jsn)
{
	POLY_MARKER;

	SetValueIfFiledExistInJson<bool>(jsn, xorstr("Active"), &m_bActive);
	SetValueIfFiledExistInJson<bool>(jsn, xorstr("RageMode"), &m_bRageMode);
	SetValueIfFiledExistInJson<int>(jsn, xorstr("iDelay"), &m_iDelay);
}

nlohmann::json Settings::BarEspSettings::ToJson() const
{
	nlohmann::json jsn;

	POLY_MARKER;

	jsn[xorstr("Active")] = m_bActive;
	jsn[xorstr("DrawHealthBar")] = m_bDrawHealthBar;
	jsn[xorstr("DrawArmorBar")] = m_bDrawArmorBar;
	jsn[xorstr("Thickness")] = m_iThickness;
	jsn[xorstr("ArmorColor")] = ImColorToJsn(m_ArmorColor);
	jsn[xorstr("BackGroundColor")] = ImColorToJsn(m_BackGroundColor);
	jsn[xorstr("Style")] = m_iStyle;

	return jsn;
};

Settings::BarEspSettings::BarEspSettings(const nlohmann::json& jsn)
{
	POLY_MARKER;

	SetValueIfFiledExistInJson<bool>(jsn, xorstr("Active"), &m_bActive);
	SetValueIfFiledExistInJson<bool>(jsn, xorstr("DrawHealthBar"), &m_bDrawHealthBar);
	SetValueIfFiledExistInJson<bool>(jsn, xorstr("DrawArmorBar"), &m_bDrawArmorBar);
	SetValueIfFiledExistInJson<int>(jsn, xorstr("Thickness"), &m_iThickness);
	SetValueIfFiledExistInJson(jsn, xorstr("ArmorColor"), &m_ArmorColor);
	SetValueIfFiledExistInJson(jsn, xorstr("BackGroundColor"), &m_BackGroundColor);
	SetValueIfFiledExistInJson(jsn, xorstr("Style"), &m_iStyle);
}

nlohmann::json Settings::CRadarSettings::ToJson() const
{
	nlohmann::json jsn;

	POLY_MARKER;

	jsn[xorstr("Active")] = m_bActive;
	jsn[xorstr("ActiveFeatureColor")] = ImColorToJsn(m_ActiveFeatureColor);
	jsn[xorstr("InactiveFeatureColor")] = ImColorToJsn(m_InactiveFeatureColor);
	jsn[xorstr("BackGroundColor")] = ImColorToJsn(m_BackGroundColor);
	jsn[xorstr("CrossColor")] = ImColorToJsn(m_CrossColor);
	jsn[xorstr("Style")] = m_iStyle;
	jsn[xorstr("CyrcleBorderColor")] = ImColorToJsn(m_CyrcleBorderColor);
	return jsn;
};

Settings::CLabelEspSettings::CLabelEspSettings()
{
	POLY_MARKER;
	m_bActive = true;
	m_Labels.push_back(std::make_shared<CLabels::CNameLabel>(xorstr("Name"), false, ImColor(255, 255, 255)));
	m_Labels.push_back(std::make_shared<CLabels::CHealthLabel>(xorstr("Health"), false));
	m_Labels.push_back(std::make_shared<CLabels::CArmorLabel>(xorstr("Armor"), false, ImColor(255, 255, 255)));
	m_Labels.push_back(std::make_shared<CLabels::CDistanceLabel>(xorstr("Distance"), false, ImColor(255, 255, 255)));
	m_Labels.push_back(
		std::make_shared<CLabels::CVisibilityLabel>(xorstr("Visibility"), false, ImColor(255, 255, 255)));
	m_Labels.push_back(std::make_shared<CLabels::CAimBotTargetLabel>(xorstr("Locked"), false, ImColor(255, 255, 255)));
}

Settings::CLabelEspSettings& Settings::CLabelEspSettings::operator=(const CLabelEspSettings& other)
{
	POLY_MARKER;
	if (this == &other)
		return *this;

	m_iDrawPos = other.m_iDrawPos;
	m_iMaxDrawDistance = other.m_iMaxDrawDistance;

	m_bActive = true;

	m_Labels.clear();

	for (auto& pLabel : other.m_Labels)
	{
		auto pTmpLabel = std::make_shared<CLabels::CBaseLabel>();
		*pTmpLabel = *pLabel.get();

		// We also must copy vft table to safe original functions! 
		// if we will not do this object will get base class vft tables
		((uintptr_t*)pTmpLabel.get())[0] = ((uintptr_t*)pLabel.get())[0];

		m_Labels.push_back(pTmpLabel);
	}

	return *this;
}

Settings::CLabelEspSettings::CLabelEspSettings(const CLabelEspSettings& other)
	: CBaseSettings(other)
{
	POLY_MARKER;
	m_bActive = true;
	m_iDrawPos = other.m_iDrawPos;
	m_iMaxDrawDistance = other.m_iMaxDrawDistance;

	m_Labels.clear();
	for (const auto& pLabel : other.m_Labels)
	{
		auto pTmpLabel = std::make_shared<CLabels::CBaseLabel>();
		*pTmpLabel = *pLabel.get();

		// We also must copy vft table to safe original functions! 
		// if we will not do this object will get base class vft tabls
		((uintptr_t*)pTmpLabel.get())[0] = ((uintptr_t*)pLabel.get())[0];

		m_Labels.push_back(pTmpLabel);
	}
}

nlohmann::json Settings::CLabelEspSettings::ToJson() const
{
	nlohmann::json jsn;

	POLY_MARKER;

	std::vector<nlohmann::json> labelsJson;
	jsn[xorstr("iDrawPos")] = m_iDrawPos;
	jsn[xorstr("iDrawDistance")] = m_iMaxDrawDistance;
	POLY_MARKER;

	for (const auto& pLabel : m_Labels)
	{
		nlohmann::json labelJson;
		labelJson[xorstr("bActive")] = pLabel->m_bActive;
		labelJson[xorstr("Color")] = ImColorToJsn(pLabel->m_Color);
		labelJson[xorstr("Name")] = pLabel->m_sName;
		labelJson[xorstr("Type")] = pLabel->GetTypeId();

		labelsJson.push_back(labelJson);
	}
	jsn[xorstr("Labels")] = labelsJson;

	return jsn;
};

Settings::CLabelEspSettings::CLabelEspSettings(const nlohmann::json& jsn)
{
	POLY_MARKER;
	SetValueIfFiledExistInJson<int>(jsn, xorstr("iDrawPos"), &m_iDrawPos);
	SetValueIfFiledExistInJson<int>(jsn, xorstr("iDrawDistance"), &m_iMaxDrawDistance);

	if (!jsn.contains(xorstr("Labels")))
		return;

	POLY_MARKER;

	for (auto& jsnLabel : jsn[xorstr("Labels")].get<std::vector<nlohmann::json>>())
	{
		CLabels::CBaseLabel* pLabel = nullptr;

		switch (jsnLabel["Type"].get<int>())
		{
		case CLabels::LabelTypeId::Name:
			pLabel = new CLabels::CNameLabel(jsnLabel[xorstr("Name")].get<std::string>(),
			                                 jsnLabel[xorstr("bActive")].get<bool>(),
			                                 ImportImColorFromJson(jsnLabel[xorstr("Color")].get<nlohmann::json>()));
			break;
		case CLabels::LabelTypeId::Health:
			pLabel = new CLabels::CHealthLabel(jsnLabel[xorstr("Name")].get<std::string>(),
			                                   jsnLabel[xorstr("bActive")].get<bool>());
			break;
		case CLabels::LabelTypeId::Distance:
			pLabel = new CLabels::CDistanceLabel(jsnLabel[xorstr("Name")].get<std::string>(),
			                                     jsnLabel[xorstr("bActive")].get<bool>(),
			                                     ImportImColorFromJson(
				                                     jsnLabel[xorstr("Color")].get<nlohmann::json>()));
			break;
		case CLabels::LabelTypeId::Armor:
			pLabel = new CLabels::CArmorLabel(jsnLabel[xorstr("Name")].get<std::string>(),
			                                  jsnLabel[xorstr("bActive")].get<bool>(),
			                                  ImportImColorFromJson(jsnLabel[xorstr("Color")].get<nlohmann::json>()));
			break;
		case CLabels::LabelTypeId::Visibility:
			pLabel = new CLabels::CVisibilityLabel(jsnLabel[xorstr("Name")].get<std::string>(),
			                                       jsnLabel[xorstr("bActive")].get<bool>(),
			                                       ImportImColorFromJson(
				                                       jsnLabel[xorstr("Color")].get<nlohmann::json>()));
			break;
		case CLabels::LabelTypeId::AimbotTarget:
			pLabel = new CLabels::CAimBotTargetLabel(jsnLabel[xorstr("Name")].get<std::string>(),
			                                         jsnLabel[xorstr("bActive")].get<bool>(),
			                                         ImportImColorFromJson(
				                                         jsnLabel[xorstr("Color")].get<nlohmann::json>()));
			break;
		}
		if (pLabel)
			m_Labels.push_back(std::shared_ptr<CLabels::CBaseLabel>(pLabel));
	}
}

nlohmann::json Settings::CBunnyHopSettings::ToJson() const
{
	POLY_MARKER;
	nlohmann::json jsn;

	jsn[xorstr("Active")] = m_bActive;

	return jsn;
};

Settings::CBunnyHopSettings::CBunnyHopSettings(const nlohmann::json& jsn) : CBunnyHopSettings()
{
	POLY_MARKER;
	SetValueIfFiledExistInJson<bool>(jsn, xorstr("Active"), &m_bActive);
}

Settings::CAllSettings::CAllSettings(const nlohmann::json& jsn)
{
	POLY_MARKER;
	m_AimBotSettings = CAimBotSettings(jsn[xorstr("AimBot")].get<nlohmann::json>());
	m_BarEspSettings = BarEspSettings(jsn[xorstr("BarEsp")].get<nlohmann::json>());
	m_BoxEspSettings = BoxEspSettings(jsn[xorstr("BoxEsp")].get<nlohmann::json>());
	m_BunnyHopSettings = CBunnyHopSettings(jsn[xorstr("BunnyHop")].get<nlohmann::json>());
	m_LabelEspSettings = CLabelEspSettings(jsn[xorstr("LabelEsp")].get<nlohmann::json>());
	m_MiscSettings = MiscSettings(jsn[xorstr("Misc")].get<nlohmann::json>());
	m_RadarSettings = CRadarSettings(jsn[xorstr("Radar")].get<nlohmann::json>());
	m_SnapLinesSettings = SnapLinesSettings(jsn[xorstr("SnapLinesEsp")].get<nlohmann::json>());
	m_TriggerBotSettings = TriggerBotSettings(jsn[xorstr("TriggerBot")].get<nlohmann::json>());

	if (jsn.contains(xorstr("TextureOverried")))
		m_TextureOverrideSettings = CTextureOverrideSettings(jsn[xorstr("TextureOverried")].get<nlohmann::json>());

	if (jsn.contains(xorstr("CrosshairSettings")))
		m_CrosshairSettings = CCrosshairSettings(jsn[xorstr("CrosshairSettings")].get<nlohmann::json>());

	if (jsn.contains(xorstr("GlowEsp")))
		m_GlowEspSettings = CGlowEspSettings(jsn[xorstr("GlowEsp")].get<nlohmann::json>());

	POLY_MARKER;
	const auto tmp = jsn[xorstr("CfgName")].get<std::string>();
    memcpy(m_Name, tmp.c_str(), tmp.size());
}

nlohmann::json Settings::CAllSettings::ToJson() const
{
	nlohmann::json jsn;

	POLY_MARKER;

	jsn[xorstr("CfgName")] = m_Name;
	jsn[xorstr("AimBot")] = m_AimBotSettings.ToJson();
	jsn[xorstr("BarEsp")] = m_BarEspSettings.ToJson();
	jsn[xorstr("BoxEsp")] = m_BoxEspSettings.ToJson();
	jsn[xorstr("BunnyHop")] = m_BunnyHopSettings.ToJson();
	jsn[xorstr("LabelEsp")] = m_LabelEspSettings.ToJson();
	jsn[xorstr("Misc")] = m_MiscSettings.ToJson();
	jsn[xorstr("Radar")] = m_RadarSettings.ToJson();
	jsn[xorstr("SnapLinesEsp")] = m_SnapLinesSettings.ToJson();
	jsn[xorstr("TriggerBot")] = m_TriggerBotSettings.ToJson();
	jsn[xorstr("TextureOverried")] = m_TextureOverrideSettings.ToJson();
	jsn[xorstr("CrosshairSettings")] = m_CrosshairSettings.ToJson();
	jsn[xorstr("GlowEsp")] = m_GlowEspSettings.ToJson();

	return jsn;
}

Settings::CRadarSettings::CRadarSettings(const nlohmann::json& jsn)
{
	POLY_MARKER;

	SetValueIfFiledExistInJson(jsn, xorstr("Style"), &m_iStyle);
	SetValueIfFiledExistInJson(jsn, xorstr("Active"), &m_bActive);

	SetValueIfFiledExistInJson(jsn, xorstr("ActiveFeatureColor"), &m_ActiveFeatureColor);
	SetValueIfFiledExistInJson(jsn, xorstr("InactiveFeatureColor"), &m_InactiveFeatureColor);
	SetValueIfFiledExistInJson(jsn, xorstr("BackGroundColor"), &m_BackGroundColor);
	SetValueIfFiledExistInJson(jsn, xorstr("CrossColor"), &m_CrossColor);
	SetValueIfFiledExistInJson(jsn, xorstr("CyrcleBorderColor"), &m_CyrcleBorderColor);
}

Settings::CTextureOverrideSettings::CTextureOverrideSettings(const nlohmann::json& jsn)
{
	POLY_MARKER;

	for (const auto& jsonTexture : jsn[xorstr("Textures")].get<std::list<nlohmann::json>>())
	{
		auto tmp = Esp::CTextureOverride(jsonTexture[xorstr("uid")].get<int>(),
		                                 ImportImColorFromJson(jsonTexture[xorstr("Color")].get<nlohmann::json>()),
		                                 jsonTexture[xorstr("Name")].get<std::string>(),
		                                 jsonTexture[xorstr("EnableZ")].get<bool>());


		m_overridedTextures.push_back(tmp);
	}
	POLY_MARKER;
}

nlohmann::json Settings::CTextureOverrideSettings::ToJson() const
{
	POLY_MARKER;

	nlohmann::json outJsn;

	std::list<nlohmann::json> textureList;

	for (const auto& texture : m_overridedTextures)
	{
		nlohmann::json textureJson;
		textureJson[xorstr("uid")] = texture.m_iUid;
		textureJson[xorstr("EnableZ")] = texture.m_bEnableZ;
		textureJson[xorstr("Name")] = texture.m_sName;
		textureJson[xorstr("Color")] = ImColorToJsn(texture.GetColor());
		textureList.push_back(textureJson);
	}

	outJsn[xorstr("Textures")] = textureList;

	return outJsn;
}

Settings::CCrosshairSettings::CCrosshairSettings(const nlohmann::json& jsn)
{
	POLY_MARKER;
	m_Color = ImportImColorFromJson(jsn[xorstr("Color")].get<nlohmann::json>());
	m_iSize = jsn[xorstr("Size")].get<int>();
	m_bActive = jsn[xorstr("Active")].get<bool>();
	m_iThicness = jsn[xorstr("Thicness")].get<int>();
	m_iDistance = jsn[xorstr("Distance")].get<int>();
	m_SpeedBarCol = ImportImColorFromJson(jsn[xorstr("SpeedBarColor")].get<nlohmann::json>());
	SetValueIfFiledExistInJson(jsn, xorstr("DrawSensors"), &m_bDrawSensors);
}

Settings::CCrosshairSettings::CCrosshairSettings()
{
	POLY_MARKER;
	m_Color = ImColor(255, 255, 255);
	m_iSize = 5;
	m_iThicness = 2;
}

nlohmann::json Settings::CCrosshairSettings::ToJson() const
{
	POLY_MARKER;

	nlohmann::json outJson;

	outJson[xorstr("Color")] = ImColorToJsn(m_Color);
	outJson[xorstr("Size")] = m_iSize;
	outJson[xorstr("Active")] = m_bActive;
	outJson[xorstr("Thicness")] = m_iThicness;
	outJson[xorstr("DrawSensors")] = m_bDrawSensors;
	outJson[xorstr("Distance")] = m_iDistance;
	outJson[xorstr("SpeedBarColor")] = ImColorToJsn(m_SpeedBarCol);


	return outJson;
}

Settings::CGlowEspSettings::CGlowEspSettings(const nlohmann::json& jsn)
{
	POLY_MARKER;
	m_Color = ImportImColorFromJson(jsn[xorstr("Color")].get<nlohmann::json>());
	m_fGlowSize = jsn[xorstr("GlowSize")].get<float>();
	m_bActive = jsn[xorstr("Active")].get<bool>();
	m_iStyle = jsn[xorstr("Style")].get<int>();

	SetValueIfFiledExistInJson(jsn, xorstr("MaxDistance"), &m_iMaxDistance);
	SetValueIfFiledExistInJson(jsn, xorstr("DrawMode"), &m_iDrawMode);
}

nlohmann::json Settings::CGlowEspSettings::ToJson() const
{
	POLY_MARKER;
	nlohmann::json outJson;
	outJson[xorstr("Color")] = ImColorToJsn(m_Color);
	outJson[xorstr("Active")] = m_bActive;
	outJson[xorstr("GlowSize")] = m_fGlowSize;
	outJson[xorstr("Style")] = m_iStyle;
	outJson[xorstr("DrawMode")] = m_iDrawMode;
	outJson[xorstr("MaxDistance")] = m_iMaxDistance;
	return outJson;
}
