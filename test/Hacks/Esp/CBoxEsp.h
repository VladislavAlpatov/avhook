#pragma once
#include "CBaseEsp.h"
namespace Esp
{
	class CBoxEsp : public CBaseEsp
	{
	public:
		CBoxEsp(BoxEspSettings* pSettings) : CBaseEsp(pSettings) {};

	private:
		void	DrawSolidBox(CBaseEntity* pEntity, const ImColor& drawColor, int thickness);
		void	DrawCorneredBox(CBaseEntity* pEntity, const ImColor& drawColor, int thickness);
		virtual void InternalRenderAt(CBaseEntity* pEntity);
	};
}