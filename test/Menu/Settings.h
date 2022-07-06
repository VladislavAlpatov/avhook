#pragma once
#include <Windows.h>

#include "../imgui/imgui.h"
#include "../SDK/CBaseEntity.h"
#include <nlohmann/json.hpp>
#include "../Hacks/Esp/CLabel/CLabel.h"
#include "../Web/IWebObject.h"
#include "../Hacks/Esp/CTextureOverride/CTextureOverride.h"

namespace Settings
{
	using namespace nlohmann;

	enum DrawMod : int
	{
		CUSTOM,
		AUTO
	};
	class CBaseSettings : public WebApi::IWebObject
	{
	public:
		bool m_bActive = false;
		bool m_bOnKey  = false;
		int m_iBindKey = 0;
		json ToJson() const override;

	};
	class CAimBotSettings : public CBaseSettings
	{
	public:
		CAimBotSettings() {};
		bool			   m_bAutoShot = false;
		bool			   silent = false;
		bool			   m_bIsWorking = false;
		bool			   m_bRcsControle = false;
		float			   m_fFov = 10.f;
		float			   m_fSmooth = 0.f;
		int                m_iSelectedHitBox = 0;
		int				   m_iPriorityType = 0;
		SSDK::CBaseEntity* m_pCurrentTarget = 0;
		int				   m_iHealthBorder = 50;
		int			       m_iHitBoxFilterMode = 0;

		enum PriorityType
		{
			FieldOfView,
			Distance
		};
		enum HitBoxFilterMode
		{
			Static = 0,
			Dynamic
		};
		json ToJson() const override;
		CAimBotSettings(const json& jsn);
	};
	class SnapLinesSettings : public CBaseSettings
	{
	public:
		SnapLinesSettings() {};
		SnapLinesSettings(const json& jsn);
		int m_iSelectedBone = 0;
		ImColor		m_Color = ImColor(255, 0, 0, 255);
		int			m_iDrawMode = 0;
		int			m_iThickness = 1;

		json ToJson() const override;
	};
	class BoxEspSettings : public CBaseSettings
	{
	public:
		BoxEspSettings() {};
		ImColor		m_Color = ImColor(255, 0, 0, 255);
		int			m_iDrawMode = 0;
		int			m_iThickness = 1;
		int			m_iStyle = 0;
		json ToJson() const override;
		enum  Style
		{
			Solid = 0,
			Cornered
		};
		BoxEspSettings(const json& jsn);
	};
	class MiscSettings : public CBaseSettings
	{
	public:
		MiscSettings() {};
		bool m_bWallPaper       = false;
		bool m_bShowTime        = false;
		bool m_bKillSound       = false;
		bool m_bSnowFlakes      = false;
		int  m_iCustomFov       = 90;
		char killSoundPath[100] = { 0 };

		json ToJson() const override;
		MiscSettings(const json& jsn);
	};

	class TriggerBotSettings : public CBaseSettings
	{
	public:
		TriggerBotSettings() {}
		bool m_bRageMode = false;
		int  m_iDelay    = 0;

		json ToJson() const override;
		TriggerBotSettings(const json& jsn);
	};
	class BarEspSettings : public CBaseSettings
	{
	public:
		BarEspSettings()
		{
			m_bActive = true;
		}

		bool    m_bDrawHealthBar  = false;
		bool    m_bDrawArmorBar   = false;
		int     m_iThickness      = 1;
		ImColor m_ArmorColor      = ImColor(56, 122, 255);
		ImColor m_BackGroundColor = ImColor(0, 0, 0, 0);

		json ToJson() const override;
		BarEspSettings(const json& jsn);
	};
	class CRadarSettings : public CBaseSettings
	{
	public:
		CRadarSettings() {};
		CRadarSettings(const json& jsn);
		bool    m_bDrawBorders         = false;
		int     m_iStyle               = 0;
		ImColor	m_ActiveFeatureColor   = ImColor(255, 0, 0);
		ImColor m_InactiveFeatureColor = ImColor(255, 255, 255);
		ImColor m_BackGroundColor      = ImColor(0, 0, 0, 30);
		ImColor m_CrossColor           = ImColor(255, 95, 95);
		ImColor m_CyrcleBorderColor    = ImColor(255, 95, 95);

		json ToJson() const override;

		enum RADAR_STYLE : int
		{
			EMBEDDED = 0,
			CUSTOM
		};
	};
	class CLabelEspSettings : public CBaseSettings
	{
	public:
		CLabelEspSettings();
		CLabelEspSettings& operator=(const CLabelEspSettings& other);
		
		CLabelEspSettings(const CLabelEspSettings& other);
		int  m_iDrawPos  = 0;
		int  m_iMaxDrawDistance = 2048;
		std::vector<std::shared_ptr<CLabels::CBaseLabel>> m_Labels;
		json ToJson() const override;
		CLabelEspSettings(const json& jsn);
		//void Restore() override {};
		enum LABELS_ALLIGN
		{
			LEFT = 0,
			TOP
		};
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

		json ToJson() const override;
		CBunnyHopSettings(const json& jsn);
	private:

	};


	class CTextureOverrideSettings : public CBaseSettings
	{
	public:
		CTextureOverrideSettings(const json& jsn);
		CTextureOverrideSettings() {};
		std::list<Esp::CTextureOverride> m_overridedTextures;
		json ToJson() const override;
	};
	class CAllSettings : public WebApi::IWebObject
	{
	public:
		CAllSettings(const json& jsn);
		CAllSettings() {};
		std::string m_Name = std::string("", 32);

		CAimBotSettings       m_AimBotSettings;
		SnapLinesSettings     m_SnapLinesSettings;
		BoxEspSettings	      m_BoxEspSettings;
		MiscSettings          m_MiscSettings;
		TriggerBotSettings    m_TriggerBotSettings;
		CRadarSettings        m_RadarSettings;
		CLabelEspSettings     m_LabelEspSettings;
		BarEspSettings        m_BarEspSettings;
		CBunnyHopSettings     m_BunnyHopSettings;
		CTextureOverrideSettings m_TextureOverrideSettings;
		json ToJson() const override;
	};
}
