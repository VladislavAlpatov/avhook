#pragma once
#include "CBaseWindow.h"
#include "../../Web/CAVhookServerApi.h"
#include "../MessageLine/CMessageLine.h"

namespace UI
{
	class CNetWorkWindow : public CBaseWindow
	{
	public:
		CNetWorkWindow(LPDIRECT3DDEVICE9 pDevice, CMessageLineList* pMessageLineList);
		virtual void Render();
		virtual void OnOpen();
		virtual void OnClose();
		virtual ~CNetWorkWindow();
	private:
		PDIRECT3DTEXTURE9         m_pTexureDefaulteAvatar = nullptr;
		PDIRECT3DTEXTURE9         m_pTextureUserAvatar    = nullptr;
		bool                      m_bAvatarSetWindow      = false;
		char                      m_AvatarPath[128]       = { 0 };
		char                      m_cfgName[32]           = { 0 };
		// Uses as backup from server
		WebApi::CUserInfo          m_UserData;
		WebApi::CLoaderTheme	   m_LoaderTheme;
		WebApi::CAVHookServerApi   m_ApiClient;
		std::vector<WebApi::CConfig> m_ConfgsList;
		CMessageLineList*          m_pMessageLineList;

		WebApi::AvatarUploadStatus m_avatarUploadStatus;
		
		void UpdateUserInfo();
		void SendNewUserInfoToServer(const WebApi::CUserInfo& info);
		void SetUserAvatar(const std::string pathToFile);

		void DrawConfigCombo(const char* label, int* CurrentItem, const std::vector<WebApi::CConfig>& list)
		{
			auto tmpArr = std::unique_ptr<const char*[]>(new const char* [list.size()]);

			for (int i = 0; i < list.size(); ++i)
			{
				tmpArr[i] = list[i].m_Settings.m_Name.c_str();
			};
			ImGui::Combo(label, CurrentItem, tmpArr.get(), list.size());
		}
	};
}