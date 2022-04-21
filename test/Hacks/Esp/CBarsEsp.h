#include "CBaseEsp.h"

namespace Esp
{
	class CBarsEsp : public CBaseEsp
	{
	public:
		CBarsEsp(Settings::BarEspSettings* pSettings) : CBaseEsp(pSettings) {};

	private:
		virtual void InternalRenderAt(CBaseEntity* pEntity);
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