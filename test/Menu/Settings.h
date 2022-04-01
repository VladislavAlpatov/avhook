#pragma once
#include <Windows.h>

#include "../imgui/imgui.h"
#include "../Utils/xorstr.h"
#include "../SDK/CBaseEntity.h"
#include <nlohmann/json.hpp>
#include <typeinfo>
#include "../Hacks/Esp/CLabel/CLabel.h"
namespace Settings
{
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

		virtual json ToJson();
	protected:
		json    ImColorToJsn(const ImColor& color);
		ImColor ImportImColorFromJson(const json& jsn);

		template<typename T>
		bool SetValueIfFiledExistInJson(const json& jsn,const char* filedName, T* var)
		{
			if (jsn.contains(filedName))
			{
				*var = jsn[filedName].get<T>();
				return true;
			}
			return false;
		}

		bool SetValueIfFiledExistInJson(const json& jsn, const char* filedName, ImColor* var)
		{
			if (jsn.contains(filedName))
			{
				*var = ImportImColorFromJson(jsn[filedName].get<json>());
				return true;
			}
			return false;
		}
	};
	class CAimBotSettings : public CBaseSettings
	{
	public:
		CAimBotSettings() {};
		bool			   m_bAutoShot = false;
		bool			   silent = false;
		bool			   m_bIsWorking = false;
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
		virtual json ToJson();
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

		virtual json ToJson();
	};
	class BoxEspSettings : public CBaseSettings
	{
	public:
		BoxEspSettings() {};
		ImColor		m_Color = ImColor(255, 0, 0, 255);
		int			m_iDrawMode = 0;
		int			m_iThickness = 1;
		int			m_iStyle = 0;
		virtual json ToJson();
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

		virtual json ToJson();
		MiscSettings(const json& jsn);
	};

	class TriggerBotSettings : public CBaseSettings
	{
	public:
		TriggerBotSettings() {}
		bool m_bRageMode = false;
		int  m_iDelay    = 0;

		virtual json ToJson();
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

		virtual json ToJson();
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

		virtual json ToJson();

		enum RADAR_STYLE : int
		{
			EMBEDDED = 0,
			CUSTOM
		};
	};
	class CLabelEspSettings : public CBaseSettings
	{
	public:
		CLabelEspSettings()
		{
			m_bActive = true;
			m_Labels.push_back(new CLabels::CNameLabel("Name",                  true, 1, ImColor(255, 255, 255)));
			m_Labels.push_back(new CLabels::CHealthLabel("Health",              true, 1));
			m_Labels.push_back(new CLabels::CDistanceLabel("Distance",          true, 1, ImColor(255, 255, 255)));
			m_Labels.push_back(new CLabels::CArmorLabel("Armor",                true, 1, ImColor(255, 255, 255)));
			m_Labels.push_back(new CLabels::CVisibilityLabel("Visibility",      true, 1, ImColor(255, 255, 255)));
			m_Labels.push_back(new CLabels::CAimBotTargetLabel("Aimbot Target", true, 1, ImColor(255, 255, 255)));
		}
		bool m_bDrawName = false;
		bool m_bDrawDistance = false;
		bool m_bDrawHealth = false;
		bool m_bDrawArmor = false;
		bool m_bDrawVisibility = false;
		bool m_bDrawAimbot = false;
		int  m_iIndexMin = 0;
		int  m_iIndexMax = 0;
		int  m_iDrawPos  = 0;
		ImColor m_GlovesColor = ImColor(255, 255, 255);
		ImColor m_NameLabelColor = ImColor(255, 255, 255);
		ImColor m_DistanceLabelColor = ImColor(255, 155, 5);
		ImColor m_ArmorLabelColor = ImColor(56, 122, 255);
		ImColor m_VisibilityLabelColor = ImColor(0, 255, 208);
		std::vector<CLabels::CBaseLabel*> m_Labels;
		virtual json ToJson();
		CLabelEspSettings(const json& jsn);
		//void Restore() override {};
		enum LABELS_ALLIGN
		{
			LEFT = 0,
			TOP
		};
		~CLabelEspSettings()
		{
			for (auto pLabel : m_Labels)
			{
				delete pLabel;
			}
		}
	};
	class ChromaSettings
	{
	public:
		ChromaSettings() {}
		bool    m_bKillGlow = false;
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

		virtual json ToJson();
		CBunnyHopSettings(const json& jsn);
	private:

	};

	class CAllSettings
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
		ChromaSettings		  m_ChromaSettings;
		CBunnyHopSettings     m_BunnyHopSettings;

		json ToJson();
	};
}
