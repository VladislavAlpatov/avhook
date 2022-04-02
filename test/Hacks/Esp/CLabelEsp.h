#include "CBaseEsp.h"
#include <list>
#include <format>
#include "CLabel/CLabel.h"


namespace Esp
{
	class CLabelEsp : public CBaseEsp
	{
	private:
		void DrawLabelsAtLeftSide(const CBaseEntity* pEntity, const std::vector<CLabels::CBaseLabel*>& labels);
		void DrawLabelsAtTop(const CBaseEntity* pEntity, const std::vector<CLabels::CBaseLabel*>& labels);
	public:
		CLabelEsp(Settings::CLabelEspSettings* pSettings) : CBaseEsp(pSettings) {};
		virtual void InternalRenderAt(CBaseEntity* pEntity);
	};
};