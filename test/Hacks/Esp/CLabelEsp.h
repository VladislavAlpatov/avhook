#pragma once

#include "CBaseEsp.h"
#include <list>
#include "CLabel/CLabel.h"


namespace Esp
{
	class CLabelEsp : public CBaseEsp
	{
	private:
		void DrawLabelsAtLeftSide(const SSDK::CBaseEntity* pEntity, const std::vector<std::shared_ptr<CLabels::CBaseLabel>>& pLabels);
		void DrawLabelsAtTop(const SSDK::CBaseEntity* pEntity, const std::vector<std::shared_ptr<CLabels::CBaseLabel>>& labels);
	public:
		CLabelEsp(Settings::CLabelEspSettings* pSettings) : CBaseEsp(pSettings) {};
		virtual void InternalRenderAt(const SSDK::CBaseEntity* pEntity);
	};
};