#pragma once
#include "../../Utils/Vec3.h"
#include "../../Menu/Settings.h"

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

	using namespace SSDK;

	class CBaseEsp
	{
	public:

		CBaseEsp(Settings::CBaseSettings* pSettings)
		{
			m_pSettings = pSettings;
		};
		bool isActive() { return m_pSettings->m_bActive; }
		__forceinline void RenderAt(CBaseEntity* pEntity)
		{
			if (IsEntityOnScreen(pEntity))
				InternalRenderAt(pEntity);

		}
	protected:
		EntityBox CalcEspBox(const CBaseEntity* pEntity) const;
		ImVec3 WorldToScreen(const ImVec3& pos) const;
		virtual void InternalRenderAt(CBaseEntity* pEntity) = 0;

		template <typename Type>
		__forceinline Type* GetSettings() const
		{
			return reinterpret_cast<Type*>(m_pSettings);
		}

	private:
		Settings::CBaseSettings* m_pSettings;

		bool IsEntityOnScreen(const CBaseEntity* pEnt) const 
		{
			if (WorldToScreen(pEnt->m_vecOrigin).z > 0.f)
				return true;
			return false;
		}
	};
}