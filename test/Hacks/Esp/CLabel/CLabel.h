#pragma once
#include <string>
#include "../../../imgui/imgui.h"
#include "../../../SDK/CBaseEntity.h"

namespace CLabels
{
	class CBaseLabel
	{
	public:
		CBaseLabel(const std::string& name, bool bActive, int iPriority, const ImColor& color)
		{
			m_sName     = name;
			m_bActive   = bActive;
			m_iPriority = iPriority;
			m_Color     = color;
		};
		virtual bool Render(const ImVec2& vecPosition, const SSDK::CBaseEntity* pEntity) = 0;
		std::string		m_sName;
		bool            m_bActive;
		int             m_iPriority;
		ImColor         m_Color;
	};

	class CNameLabel : public CBaseLabel
	{
	public:
		CNameLabel(const std::string& name, bool bActive, int iPriority, const ImColor& color) : CBaseLabel(name, bActive, iPriority, color) {};
		virtual bool Render(const ImVec2& vecPosition, const SSDK::CBaseEntity* pEntity);
	private:

	};

	class CHealthLabel : public CBaseLabel
	{
	public:
		CHealthLabel(const std::string& name, bool bActive, int iPriority) : CBaseLabel(name, bActive, iPriority, ImColor(255, 255, 255)) {};
		virtual bool Render(const ImVec2& vecPosition, const SSDK::CBaseEntity* pEntity);
	private:

	};

	class CArmorLabel : public CBaseLabel
	{
	public:
		CArmorLabel(const std::string& name, bool bActive, int iPriority, const ImColor& color) : CBaseLabel(name, bActive, iPriority, color) {};
		virtual bool Render(const ImVec2& vecPosition, const SSDK::CBaseEntity* pEntity);
	private:

	};

	class CDistanceLabel : public CBaseLabel
	{
	public:
		CDistanceLabel(const std::string& name, bool bActive, int iPriority, const ImColor& color) : CBaseLabel(name, bActive, iPriority, color) {};
		virtual bool Render(const ImVec2& vecPosition, const SSDK::CBaseEntity* pEntity);
	private:

	};

	class CVisibilityLabel : public CBaseLabel
	{
	public:
		CVisibilityLabel(const std::string& name, bool bActive, int iPriority, const ImColor& color) : CBaseLabel(name, bActive, iPriority, color) {};
		virtual bool Render(const ImVec2& vecPosition, const SSDK::CBaseEntity* pEntity);
	private:

	};

	class CAimBotTargetLabel : public CBaseLabel
	{
	public:
		CAimBotTargetLabel(const std::string& name, bool bActive, int iPriority, const ImColor& color) : CBaseLabel(name, bActive, iPriority, color) {};
		virtual bool Render(const ImVec2& vecPosition, const SSDK::CBaseEntity* pEntity);
	};
}