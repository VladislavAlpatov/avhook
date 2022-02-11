#pragma once
#include "CBaseEsp.h"

class CBoxEsp : public CBaseEsp
{
public:
	CBoxEsp(BoxEspSetting* pSettings) : CBaseEsp(pSettings) {};

private:
	virtual void InternalRenderAt(CBaseEntity* pEntity);
};