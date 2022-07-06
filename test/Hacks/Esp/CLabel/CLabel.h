#pragma once
#include <string>
#include "../../../imgui/imgui.h"
#include "../../../SDK/CBaseEntity.h"

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
	public:
		CBaseLabel()
		{

		}
		CBaseLabel(const std::string& name, bool bActive, const ImColor& color);
		virtual bool Render(const ImVec2& vecPosition, const SSDK::CBaseEntity* pEntity) { return false; };
		virtual int  GetTypeId() { return LabelTypeId::Base; }
		std::string		m_sName;
		bool            m_bActive;
		ImColor         m_Color;
	};

	class CNameLabel : public CBaseLabel
	{
	public:
		CNameLabel(const std::string& name, bool bActive, const ImColor& color) : CBaseLabel(name, bActive, color) {};
		virtual bool Render(const ImVec2& vecPosition, const SSDK::CBaseEntity* pEntity);
		virtual int  GetTypeId() { return LabelTypeId::Name; }
	private:

	};

	class CHealthLabel : public CBaseLabel
	{
	public:
		CHealthLabel(const std::string& name, bool bActive) : CBaseLabel(name, bActive, ImColor(255, 255, 255)) {};
		virtual bool Render(const ImVec2& vecPosition, const SSDK::CBaseEntity* pEntity);
		virtual int  GetTypeId() { return LabelTypeId::Heatlh; }
	private:

	};

	class CArmorLabel : public CBaseLabel
	{
	public:
		CArmorLabel(const std::string& name, bool bActive, const ImColor& color) : CBaseLabel(name, bActive, color) {};
		virtual bool Render(const ImVec2& vecPosition, const SSDK::CBaseEntity* pEntity);
		virtual int  GetTypeId() { return LabelTypeId::Armor; }
	private:

	};

	class CDistanceLabel : public CBaseLabel
	{
	public:
		CDistanceLabel(const std::string& name, bool bActive, const ImColor& color) : CBaseLabel(name, bActive, color) {};
		virtual bool Render(const ImVec2& vecPosition, const SSDK::CBaseEntity* pEntity);
		virtual int  GetTypeId() { return LabelTypeId::Distance; }
	private:

	};

	class CVisibilityLabel : public CBaseLabel
	{
	public:
		CVisibilityLabel(const std::string& name, bool bActive, const ImColor& color) : CBaseLabel(name, bActive, color) {};
		virtual bool Render(const ImVec2& vecPosition, const SSDK::CBaseEntity* pEntity);
		virtual int  GetTypeId() { return LabelTypeId::Visibility; }
	private:

	};

	class CAimBotTargetLabel : public CBaseLabel
	{
	public:
		CAimBotTargetLabel(const std::string& name, bool bActive, const ImColor& color) : CBaseLabel(name, bActive, color) {};
		virtual bool Render(const ImVec2& vecPosition, const SSDK::CBaseEntity* pEntity);
		virtual int  GetTypeId() { return LabelTypeId::AimbotTarget; }
	};
}