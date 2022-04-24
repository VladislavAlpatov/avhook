#pragma once
#include "CBaseEsp.h"
namespace Esp
{
	class CBoxEsp : public CBaseEsp
	{
		
	public:
		CBoxEsp(Settings::BoxEspSettings* pSettings) : CBaseEsp(pSettings) {};

	private:
		void	DrawSolidBox(const CBaseEntity* pEntity, const ImColor& drawColor, int thickness);
		void	DrawCorneredBox(const CBaseEntity* pEntity, const ImColor& drawColor,const  int thickness);

		virtual void InternalRenderAt(CBaseEntity* pEntity);
	};
}