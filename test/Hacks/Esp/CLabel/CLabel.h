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
		Health,
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
			m_bActive = false;
		}
		CBaseLabel(const std::string& name, const bool bActive, const ImColor& color);
		virtual [[nodiscard]] int  GetTypeId() const { return LabelTypeId::Base; }
		std::string		m_sName;
		bool            m_bActive;
		ImColor         m_Color;
		virtual ~CBaseLabel() = default;

	protected:
		virtual bool Render(const ImVec2& vecPosition, const SSDK::CBaseEntity* pEntity) const { return false; };
	};

	class CNameLabel final : public CBaseLabel
	{
	public:
		CNameLabel(const std::string& name, const bool bActive, const ImColor& color) : CBaseLabel(name, bActive, color) {};
		int GetTypeId() const  override { return LabelTypeId::Name; }
	protected:
		bool Render(const ImVec2& vecPosition, const SSDK::CBaseEntity* pEntity) const override;
	};

	class CHealthLabel final : public CBaseLabel
	{
	public:
		CHealthLabel(const std::string& name,const bool bActive) : CBaseLabel(name, bActive, ImColor(255, 255, 255)) {};
		int GetTypeId() const override { return LabelTypeId::Health; }
	protected:
		bool Render(const ImVec2& vecPosition, const SSDK::CBaseEntity* pEntity) const override;
	};

	class CArmorLabel final : public CBaseLabel
	{
	public:
		CArmorLabel(const std::string& name,const bool bActive, const ImColor& color) : CBaseLabel(name, bActive, color) {};
		int  GetTypeId() const override  { return LabelTypeId::Armor; }
	protected:
		bool Render(const ImVec2& vecPosition, const SSDK::CBaseEntity* pEntity) const override;
	};

	class CDistanceLabel final : public CBaseLabel
	{
	public:
		CDistanceLabel(const std::string& name, const bool bActive, const ImColor& color) : CBaseLabel(name, bActive, color) {};
		int  GetTypeId()  const override { return LabelTypeId::Distance; }
	protected:
		// ReSharper disable InconsistentNaming
		bool Render(const ImVec2& vecPosition, const SSDK::CBaseEntity* pEntity) const override;
	};

	class CVisibilityLabel final : public CBaseLabel
	{
	public:
		CVisibilityLabel(const std::string& name, const bool bActive, const ImColor& color) : CBaseLabel(name, bActive, color) {};
		int  GetTypeId()  const override { return LabelTypeId::Visibility; }
	protected:
		bool Render(const ImVec2& vecPosition, const SSDK::CBaseEntity* pEntity) const override;
	};

	class CAimBotTargetLabel final : public CBaseLabel
	{
	public:
		CAimBotTargetLabel(const std::string& name, const bool bActive, const ImColor& color) : CBaseLabel(name, bActive, color) {};
		int  GetTypeId()  const override { return LabelTypeId::AimbotTarget; }
	protected:
		bool Render(const ImVec2& vecPosition, const SSDK::CBaseEntity* pEntity) const override;
	};
}