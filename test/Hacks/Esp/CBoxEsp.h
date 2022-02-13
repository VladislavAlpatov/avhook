#pragma once
#include "CBaseEsp.h"

class CBoxEsp : public CBaseEsp
{
public:
	CBoxEsp(BoxEspSettings* pSettings) : CBaseEsp(pSettings) {};

private:
	virtual void InternalRenderAt(CBaseEntity* pEntity);
};