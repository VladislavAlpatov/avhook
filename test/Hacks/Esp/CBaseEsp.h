#pragma once
#include "../../Utils/Vec3.h"
#include "../../Menu/Settings.h"

namespace UI
{
	class COverlay;
}

namespace Esp
{

	class EntityBox
	{
	public:
		
		ImVec2 m_vecTopLeft;
		ImVec2 m_vecTopRight;

		ImVec2 m_vecBottomLeft;
		ImVec2 m_vecBottomRight;

		ImVec2 GetSize() const;
	};

	class CBaseEsp
	{
	public:
		friend UI::COverlay;
		CBaseEsp(Settings::CBaseSettings* pSettings)
		{
			m_pSettings = pSettings;
		};
	protected:
		bool isActive() { return m_pSettings->m_bActive; }
		__forceinline void RenderAt(const SSDK::CBaseEntity* pEntity)
		{
			if (IsEntityOnScreen(pEntity))
				InternalRenderAt(pEntity);

		}
		EntityBox CalcEspBox(const SSDK::CBaseEntity* pEntity) const;
		ImVec3 WorldToScreen(const ImVec3& pos) const;
		virtual void InternalRenderAt(const SSDK::CBaseEntity* pEntity) = 0;

		template <typename Type>
		__forceinline Type* GetSettings() const
		{
			return reinterpret_cast<Type*>(m_pSettings);
		}

	private:
		Settings::CBaseSettings* m_pSettings;

		bool IsEntityOnScreen(const SSDK::CBaseEntity* pEnt) const 
		{
			return WorldToScreen(pEnt->m_vecOrigin).z > 0.f;
		}
	};
}
