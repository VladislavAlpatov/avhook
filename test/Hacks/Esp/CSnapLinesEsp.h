#include "CBaseEsp.h"


class CSnapLinesEsp : public CBaseEsp
{
public:
	CSnapLinesEsp(SnapLinesSettings* pSettings) : CBaseEsp(pSettings) {};
private:
	virtual void InternalRenderAt(CBaseEntity* pEntity);
};