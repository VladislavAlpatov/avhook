#pragma once
#include <string>
#include "../../../imgui/imgui.h"
#include "../../../SDK/CBaseEntity.h"

namespace Esp { class CLabelEsp; }

namespace CLabels
{
	enum LabelTypeId : int 
	{
		Base = -1,
		Name,
		Heatlh,
		Armor,
		Distance,
		Visibility,
		AimbotTarget,
	};

	class CBaseLabel
	{
		friend Esp::CLabelEsp;
	public:
		CBaseLabel()
		{

		}
		CBaseLabel(const std::string& name, bool bActive, const ImColor& color);
		virtual int  GetTypeId() { return LabelTypeId::Base; }
		std::string		m_sName;
		bool            m_bActive;
		ImColor         m_Color;

	protected:
		virtual bool Render(const ImVec2& vecPosition, const SSDK::CBaseEntity* pEntity) { return false; };
	};

	class CNameLabel : public CBaseLabel
	{
	public:
		CNameLabel(const std::string& name, bool bActive, const ImColor& color) : CBaseLabel(name, bActive, color) {};
		virtual int  GetTypeId() { return LabelTypeId::Name; }
	protected:
		bool Render(const ImVec2& vecPosition, const SSDK::CBaseEntity* pEntity) override;
	};

	class CHealthLabel : public CBaseLabel
	{
	public:
		CHealthLabel(const std::string& name, bool bActive) : CBaseLabel(name, bActive, ImColor(255, 255, 255)) {};
		virtual int  GetTypeId() { return LabelTypeId::Heatlh; }
	protected:
		bool Render(const ImVec2& vecPosition, const SSDK::CBaseEntity* pEntity) override;
	};

	class CArmorLabel : public CBaseLabel
	{
	public:
		CArmorLabel(const std::string& name, bool bActive, const ImColor& color) : CBaseLabel(name, bActive, color) {};
		virtual int  GetTypeId() { return LabelTypeId::Armor; }
	protected:
		bool Render(const ImVec2& vecPosition, const SSDK::CBaseEntity* pEntity) override;
	};

	class CDistanceLabel : public CBaseLabel
	{
	public:
		CDistanceLabel(const std::string& name, bool bActive, const ImColor& color) : CBaseLabel(name, bActive, color) {};
		virtual int  GetTypeId() { return LabelTypeId::Distance; }
	protected:
		bool Render(const ImVec2& vecPosition, const SSDK::CBaseEntity* pEntity) override;
	};

	class CVisibilityLabel : public CBaseLabel
	{
	public:
		CVisibilityLabel(const std::string& name, bool bActive, const ImColor& color) : CBaseLabel(name, bActive, color) {};
		virtual int  GetTypeId() { return LabelTypeId::Visibility; }
	protected:
		bool Render(const ImVec2& vecPosition, const SSDK::CBaseEntity* pEntity) override;
	};

	class CAimBotTargetLabel : public CBaseLabel
	{
	public:
		CAimBotTargetLabel(const std::string& name, bool bActive, const ImColor& color) : CBaseLabel(name, bActive, color) {};
		virtual int  GetTypeId() { return LabelTypeId::AimbotTarget; }
	protected:
		bool Render(const ImVec2& vecPosition, const SSDK::CBaseEntity* pEntity) override;
	};
}