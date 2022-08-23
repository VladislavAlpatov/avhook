#pragma once
#include "CBaseEsp.h"

namespace Esp
{
	class CBarsEsp : public CUIEsp
	{
	public:
		CBarsEsp(Settings::BarEspSettings* pSettings) : CUIEsp(pSettings) {};
		
	private:
		virtual void InternalRenderAt(const SSDK::CBaseEntity* pEntity);
		struct LineData
		{
			LineData(const ImColor& color, float fLength)
			{
				m_Color = color;
				m_fLength = fLength;
			}
			ImColor m_Color;
			float	m_fLength;
		};
	};
}