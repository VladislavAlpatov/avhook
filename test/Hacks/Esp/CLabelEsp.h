#include "CBaseEsp.h"
#include <list>
#include <format>


namespace Esp
{
	class CLabelEsp : public CBaseEsp
	{
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
		void DrawLabelsAtLeftSide(const CBaseEntity* pEntity, const std::list<Label>& labels);
		void DrawLabelsAtTop(const CBaseEntity* pEntity, const std::list<Label>& labels);
	public:
		CLabelEsp(Settings::CLabelEspSettings* pSettings) : CBaseEsp(pSettings) {};
		virtual void InternalRenderAt(CBaseEntity* pEntity);
	};
};