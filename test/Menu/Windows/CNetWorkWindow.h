#pragma once
#include "CBaseWindow.h"
#include "../../Web/httplib.h"

#include <thread>
#include "../../Globals/GlobalVars.h"
#include "../../Web/CAVhookServerApi.h"
namespace Windows
{
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
		PDIRECT3DTEXTURE9 m_pTextureUserAvatar = nullptr;
		// Uses as backup from server
		WebApi::CUserInfo m_OldUserData;
		WebApi::CUserInfo m_CurrentUserData;
		WebApi::CAVHookServerApi m_ApiClient;
		bool m_bAvatarSetWindow = false;

		WebApi::AvatarUploadStatus m_avatarUploadStatus;
		char m_AvatarPath[128] = { 0 };
		void UpdateUserInfo();
		void SendNewUserInfoToServer(const WebApi::CUserInfo& info);
		void SetUserAvatar(const std::string pathToFile);
	};
}