#pragma once

#include "CBaseEsp.h"
#include <list>
#include "CLabel/CLabel.h"


namespace Esp
{
	class CLabelEsp : public CUIEsp
	{
	private:
		void DrawLabelsAtLeftSide(const SSDK::CBaseEntity* pEntity, const std::vector<std::shared_ptr<CLabels::CBaseLabel>>& pLabels) const ;
		void DrawLabelsAtTop(const SSDK::CBaseEntity* pEntity, const std::vector<std::shared_ptr<CLabels::CBaseLabel>>& labels) const ;
	public:
		CLabelEsp(Settings::CLabelEspSettings* pSettings) : CUIEsp(pSettings) {};
		void InternalRenderAt(const SSDK::CBaseEntity* pEntity)  override;
	};
};