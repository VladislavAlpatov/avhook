#include "CBaseEsp.h"
#include <list>
#include <format>
#include "CLabel/CLabel.h"


namespace Esp
{
	class CLabelEsp : public CBaseEsp
	{
	private:
		class Label
		{
		public:
			Label(const ImColor& color, const std::string& text)
			{
				m_Color = color;
				m_Text  = text;
			}
			ImColor     m_Color;
			std::string m_Text;

			int GetPrioriy() const { return m_iPriority; }

		private:
			int m_iPriority = 0;
		};

		void DrawLabelsAtLeftSide(const CBaseEntity* pEntity, const std::vector<CLabels::CBaseLabel*>& labels);
		void DrawLabelsAtTop(const CBaseEntity* pEntity, const std::vector<CLabels::CBaseLabel*>& labels);
	public:
		CLabelEsp(Settings::CLabelEspSettings* pSettings) : CBaseEsp(pSettings) {};
		virtual void InternalRenderAt(CBaseEntity* pEntity);
	};
};