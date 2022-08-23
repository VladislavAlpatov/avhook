#pragma once
#include "CBaseEsp.h"
namespace Esp
{
	class CBoxEsp : public CUIEsp
	{
		
	public:
		CBoxEsp(Settings::BoxEspSettings* pSettings) : CUIEsp(pSettings) {};

	private:
		void	DrawSolidBox(const SSDK::CBaseEntity* pEntity, const ImColor& drawColor, const  float thickness);
		void	DrawCorneredBox(const SSDK::CBaseEntity* pEntity, const ImColor& drawColor,const  float thickness);

		virtual void InternalRenderAt(const SSDK::CBaseEntity* pEntity);
	};
}