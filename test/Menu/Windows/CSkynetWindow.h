#include "CBaseWindow.h"
#include "../../Globals/GlobalVars.h"
#include "../../Server/Server.h"
#include "../../SDK/IClientEntityList.h"
#include "../../SDK/IVEngineClient013/IVEngineClient013.h"

class CSkyNetWindow : public CBaseWindow
{
public:
	CSkyNetWindow(LPDIRECT3DDEVICE9 pDevice, HMODULE  hModule);
	virtual void Render();
};