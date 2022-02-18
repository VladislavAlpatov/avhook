#include "CBaseEsp.h"
#include <list>
#include <format>


namespace Esp
{
	class CLabelEsp : public CBaseEsp
	{
	public:
		CLabelEsp(CLabelEspSettings* pSettings) : CBaseEsp(pSettings) {};
		virtual void InternalRenderAt(CBaseEntity* pEntity);

	private:
		struct Label
		{
			Label(const ImColor& color, const std::string& text)
			{
				m_Color = color;
				m_Text = text;
			}
			ImColor     m_Color;
			std::string m_Text;
		};
	};
};