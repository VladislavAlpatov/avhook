#pragma once
#include <nlohmann/json.hpp>
#include "../Hacks/Esp/CLabel/CLabel.h"
#include "../Web/IWebObject.h"
#include "../Hacks/Esp/CTextureOverride/CTextureOverride.h"

namespace Settings
{

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
		nlohmann::json ToJson() const override;

	};
	class CAimBotSettings final : public CBaseSettings
	{
	public:
		CAimBotSettings();
		bool			   m_bAutoShot;
		bool			   m_bSilent;
		bool			   m_bIsWorking;
		bool			   m_bRcsControle;
		float			   m_fFov;
		float			   m_fSmooth;
		int                m_iSelectedHitBox;
		int				   m_iPriorityType;
		SSDK::CBaseEntity* m_pCurrentTarget;
		int				   m_iHealthBorder;
		int			       m_iHitBoxFilterMode;

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
		nlohmann::json ToJson() const override;
		CAimBotSettings(const nlohmann::json& jsn);
	};
	class SnapLinesSettings final : public CBaseSettings
	{
	public:
		SnapLinesSettings() = default;
		SnapLinesSettings(const nlohmann::json& jsn);
		int         m_iSelectedBone = 0;
		ImColor		m_Color = ImColor(255, 0, 0, 255);
		int			m_iDrawMode = 0;
		int			m_iThickness = 1;

		nlohmann::json ToJson() const override;
	};
	class BoxEspSettings final : public CBaseSettings
	{
	public:
		BoxEspSettings() = default;
		ImColor		m_Color = ImColor(255, 0, 0, 255);
		int			m_iDrawMode = 0;
		int			m_iThickness = 1;
		int			m_iStyle = 0;
		nlohmann::json ToJson() const override;
		enum  Style
		{
			Solid = 0,
			Cornered
		};
		BoxEspSettings(const nlohmann::json& jsn);
	};
	class MiscSettings final : public CBaseSettings
	{
	public:
		MiscSettings() = default;
		bool m_bWallPaper       = false;
		bool m_bShowTime        = false;
		bool m_bKillSound       = false;
		bool m_bSnowFlakes      = false;
		int  m_iCustomFov       = 90;

		nlohmann::json ToJson() const override;
		MiscSettings(const nlohmann::json& jsn);
	};

	class TriggerBotSettings final : public CBaseSettings
	{
	public:
		TriggerBotSettings() = default;
		bool m_bRageMode = false;
		int  m_iDelay    = 0;
		nlohmann::json ToJson() const override;
		TriggerBotSettings(const nlohmann::json& jsn);
	};
	class BarEspSettings final : public CBaseSettings
	{
	public:
		BarEspSettings()
		{
			m_bActive = true;
		}

		bool    m_bDrawHealthBar  = false;
		bool    m_bDrawArmorBar   = false;
		int     m_iThickness      = 1;
		int     m_iStyle          = 0;
		ImColor m_ArmorColor      = ImColor(56, 122, 255);
		ImColor m_BackGroundColor = ImColor(0, 0, 0, 0);

		nlohmann::json ToJson() const override;
		BarEspSettings(const nlohmann::json& jsn);
		
	};
	class CRadarSettings final : public CBaseSettings
	{
	public:
		CRadarSettings() = default;
		CRadarSettings(const nlohmann::json& jsn);
		bool    m_bDrawBorders         = false;
		int     m_iStyle               = 0;
		ImColor	m_ActiveFeatureColor   = ImColor(255, 0, 0);
		ImColor m_InactiveFeatureColor = ImColor(255, 255, 255);
		ImColor m_BackGroundColor      = ImColor(0, 0, 0, 30);
		ImColor m_CrossColor           = ImColor(255, 95, 95);
		ImColor m_CyrcleBorderColor    = ImColor(255, 95, 95);

		nlohmann::json ToJson() const override;

		enum RADAR_STYLE : int
		{
			EMBEDDED = 0,
			CUSTOM
		};
	};
	class CLabelEspSettings final : public CBaseSettings
	{
	public:
		CLabelEspSettings();
		CLabelEspSettings& operator=(const CLabelEspSettings& other);
		
		CLabelEspSettings(const CLabelEspSettings& other);
		int  m_iDrawPos  = 0;
		int  m_iMaxDrawDistance = 2048;
		std::vector<std::shared_ptr<CLabels::CBaseLabel>> m_Labels;
		nlohmann::json ToJson() const override;
		CLabelEspSettings(const nlohmann::json& jsn);
		//void Restore() override {};
		enum LABELS_ALLIGN
		{
			LEFT = 0,
			TOP
		};
	};
	class CBunnyHopSettings final : public CBaseSettings
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

		nlohmann::json ToJson() const override;
		CBunnyHopSettings(const nlohmann::json& jsn);
	private:

	};

	class CTextureOverrideSettings final : public CBaseSettings
	{
	public:
		CTextureOverrideSettings(const nlohmann::json& jsn);
		CTextureOverrideSettings() = default;
		std::list<Esp::CTextureOverride> m_overridedTextures;
		nlohmann::json ToJson() const override;
	};

	class CCrosshairSettings final : public CBaseSettings
	{
	public:
		CCrosshairSettings();
		CCrosshairSettings(const nlohmann::json& jsn);
		ImColor m_Color;
		ImColor m_SpeedBarCol = ImColor(0,0, 255);
		int     m_iSize;
		int		m_iThicness;
		int		m_iDistance = 100;
		bool	m_bDrawSensors = false;


		nlohmann::json ToJson() const override;

	};

	class CGlowEspSettings final : public CBaseSettings
	{
	public:
		CGlowEspSettings() = default;
		CGlowEspSettings(const nlohmann::json& jsn);
		ImColor m_Color = ImColor(255, 255, 255);
		float   m_fGlowSize = 1.f;
		int     m_iMaxDistance = 4096;
		int		m_iStyle = 0;
		int     m_iDrawMode = 0;

		enum DrawMode
		{
			Static,
			Dynamic
		};

		nlohmann::json ToJson() const override;
	};

	class CAllSettings final : public WebApi::IWebObject
	{
	public:
		CAllSettings(const nlohmann::json& jsn);
		CAllSettings() = default;
		std::string m_Name = { "", 32 };

		CAimBotSettings          m_AimBotSettings;
		SnapLinesSettings        m_SnapLinesSettings;
		BoxEspSettings	         m_BoxEspSettings;
		MiscSettings             m_MiscSettings;
		TriggerBotSettings       m_TriggerBotSettings;
		CRadarSettings           m_RadarSettings;
		CLabelEspSettings        m_LabelEspSettings;
		BarEspSettings           m_BarEspSettings;
		CBunnyHopSettings        m_BunnyHopSettings;
		CTextureOverrideSettings m_TextureOverrideSettings;
		CCrosshairSettings       m_CrosshairSettings;
		CGlowEspSettings		 m_GlowEspSettings;

		nlohmann::json ToJson() const override;
	};

	
}
