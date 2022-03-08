#pragma once
#include "CBaseWindow.h"
#include "../../Web/httplib.h"

#include <thread>
#include "../../Globals/GlobalVars.h"
#include "../../Web/CAVhookServerApi.h"
#include "../MessageLine/CMessageLine.h"

namespace UI
{
	class CNetWorkWindow : public CBaseWindow
	{
	public:
		CNetWorkWindow(LPDIRECT3DDEVICE9 pDevice, HMODULE  hModule, CMessageLineList* pMessageLineList);
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
		WebApi::CUserInfo          m_OldUserData;
		WebApi::CUserInfo          m_CurrentUserData;
		WebApi::CAVHookServerApi   m_ApiClient;
		CMessageLineList*          m_pMessageLineList;

		WebApi::AvatarUploadStatus m_avatarUploadStatus;
		
		void UpdateUserInfo();
		void SendNewUserInfoToServer(const WebApi::CUserInfo& info);
		void SetUserAvatar(const std::string pathToFile);

		void DrawVectorCombo(const char* label, int* CurrentItem, const std::vector<std::string>& list)
		{
			const char** tmpArr = new const char*[list.size()];

			for (int i = 0; i < list.size(); ++i)
			{
				tmpArr[i] = list[i].c_str();
			};
			ImGui::Combo(label, CurrentItem, tmpArr, list.size());

			delete[] tmpArr;
		}
	};
}