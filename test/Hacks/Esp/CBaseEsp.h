#pragma once
#include "../../Utils/Vec3.h"
#include "../../Menu/Settings.h"

//========= Copyright Alpatov Softworks, All rights reserved. ============//
//
// Purpose: Define an abstract ESP class
//
//===============================================================================


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
		CBaseEsp(Settings::CBaseSettings* pSettings)
		{
			m_pSettings = pSettings;
		};
	protected:
		bool isActive() const { return m_pSettings->m_bActive; }

		template <typename Type>
		__forceinline Type* GetSettings() const
		{
			return reinterpret_cast<Type*>(m_pSettings);
		}

	private:
		Settings::CBaseSettings* m_pSettings;
	};
	class CUIEsp : public CBaseEsp
	{
		/// <summary>
		/// Abstract class for non engine ESP (Health bars, boxes, etc....)
		/// </summary>
		friend UI::COverlay;

	public:
		CUIEsp(Settings::CBaseSettings* pSettings) : CBaseEsp(pSettings) {}

	protected:
		__forceinline void RenderAt(const SSDK::CBaseEntity* pEntity)
		{
			if (IsEntityOnScreen(pEntity))
				InternalRenderAt(pEntity);

		}
		EntityBox    CalcEspBox(const SSDK::CBaseEntity* pEntity) const;
		static ImVec3       WorldToScreen(const ImVec3& vecPosition);
		virtual void InternalRenderAt(const SSDK::CBaseEntity* pEntity) = 0;
	private:
		bool IsEntityOnScreen(const SSDK::CBaseEntity* pEnt) const
		{
			return WorldToScreen(pEnt->m_vecOrigin).z > 0.f;
		}
	};
}
