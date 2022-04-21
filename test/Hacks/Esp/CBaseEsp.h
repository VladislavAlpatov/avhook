#pragma once
#include "../../Utils/Vec3.h"
#include "../../Menu/Settings.h"

namespace Esp
{

	struct EntityBox
	{
		ImVec2 m_vecTop;
		ImVec2 m_vecBottom;
		float  m_Width;
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
		EntityBox CalcEspBox(const CBaseEntity* pEntity);
		ImVec3 WorldToScreen(const ImVec3& pos);
		virtual void InternalRenderAt(CBaseEntity* pEntity) = 0;

		template <typename Type>
		__forceinline Type* GetSettings()
		{
			return reinterpret_cast<Type*>(m_pSettings);
		}

	private:
		Settings::CBaseSettings* m_pSettings;

		bool IsEntityOnScreen(CBaseEntity* pEnt)
		{
			if (WorldToScreen(pEnt->m_vecOrigin).z > 0.f)
				return true;
			return false;
		}
	};
}