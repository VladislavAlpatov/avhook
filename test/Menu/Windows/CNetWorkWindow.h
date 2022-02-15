#pragma once
#include "CBaseWindow.h"
#include "../../Web/httplib.h"

#include <thread>
#include "../../Globals/GlobalVars.h"
#include "../../Web/CAVhookServerApi.h"

class CNetWorkWindow : public CBaseWindow
{
public:
	CNetWorkWindow(LPDIRECT3DDEVICE9 pDevice, HMODULE  hModule);
	virtual void Render();
	virtual void OnOpen();
	virtual void OnClose();
	virtual ~CNetWorkWindow();
private:
	PDIRECT3DTEXTURE9 m_pTexureDefaulteAvatar = nullptr;
	PDIRECT3DTEXTURE9 m_pTextureUserAvatar    = nullptr;
	// Uses as backup from server
	CUserInfo m_OldUserData;
	CUserInfo m_CurrentUserData;
	bool m_bAvatarSetWindow = false;
	char m_AvatarPath[128] = {0};
	void UpdateUserInfo();
	void SendNewUserInfoToServer(const CUserInfo& info);
};