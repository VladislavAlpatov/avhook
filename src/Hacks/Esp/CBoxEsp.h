#pragma once
#include "CBaseEsp.h"
namespace Esp
{
	class CBoxEsp final : public CUIEsp
	{
		
	public:
		CBoxEsp(Settings::BoxEspSettings* pSettings) : CUIEsp(pSettings) {};

	private:
		void	DrawSolidBox(const SSDK::CBaseEntity* pEntity, const ImColor& drawColor, const  float thickness) const;
		void	DrawCorneredBox(const SSDK::CBaseEntity* pEntity, const ImColor& drawColor,const  float thickness) const;

		void InternalRenderAt(const SSDK::CBaseEntity* pEntity) override;
	};
}