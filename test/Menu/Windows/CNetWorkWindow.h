#pragma once
#include "CBaseWindow.h"
#include "../../Web/CAVhookServerApi.h"
#include "../MessageLine/CMessageLine.h"

namespace UI
{
	class CNetWorkWindow final: public CBaseWindow
	{
	public:
		CNetWorkWindow(LPDIRECT3DDEVICE9 pDevice, CMessageLineList* pMessageLineList);
		void Render() override;
		void OnOpen() override;
		std::string GetAlias() const override;
		void OnClose() override;
		~CNetWorkWindow() override;
	private:
		PDIRECT3DTEXTURE9         m_pTextureDefaultAvatar = nullptr;
		PDIRECT3DTEXTURE9         m_pTextureUserAvatar    = nullptr;
		bool                      m_bAvatarSetWindow      = false;
		char                      m_AvatarPath[128]       = { 0 };
		// Uses as backup from server
		WebApi::CUserInfo          m_UserData;
		WebApi::CLoaderTheme	   m_LoaderTheme;
		WebApi::CAVHookServerApi   m_ApiClient;
		std::vector<WebApi::CConfig> m_ConfigsList;
		CMessageLineList*          m_pMessageLineList;

		WebApi::AvatarUploadStatus m_avatarUploadStatus;
		
		void UpdateUserInfo();
		void SendNewUserInfoToServer(const WebApi::CUserInfo& info);
		void SetUserAvatar(const std::string& pathToFile);

		void DrawConfigCombo(const char* label, int* CurrentItem, const std::vector<WebApi::CConfig>& list);
	};
}