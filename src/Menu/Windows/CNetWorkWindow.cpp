#pragma once

#include <d3dx9.h>
#include <fmt/format.h>
#include <thread>

#include "CNetWorkWindow.h"

#include "../../Globals/Settings.h"
#include "../../RawData/Images.h"
#include "../../Utils/Marker.h"
#include <string>

UI::CNetWorkWindow::CNetWorkWindow(LPDIRECT3DDEVICE9 pDevice, CMessageLineList* pMessageLineList) : CBaseWindow(pDevice)
{
	POLY_MARKER;
    m_pApiClient = WebApi::CAVHookServerApi::Get();
	D3DXCreateTextureFromFileInMemory(m_pDevice, Images::DefaultAvatar, sizeof(Images::DefaultAvatar), &m_pTextureDefaultAvatar);
	D3DXCreateTextureFromFileInMemory(m_pDevice, Images::ProfileIcon,   sizeof(Images::ProfileIcon),   &m_pTextureIcon);

	
	m_pMessageLineList = pMessageLineList;
#ifdef CLOUD_SUPPORT
	const auto avatarRawData = m_pApiClient->GetRawAvatarData();

	D3DXCreateTextureFromFileInMemory(m_pDevice, avatarRawData.c_str(), avatarRawData.size(), &m_pTextureUserAvatar);
#endif
}
void UI::CNetWorkWindow::Render()
{
	POLY_MARKER;
	static int iTab = 0;
	ImGui::Begin(xorstr("###Network"), nullptr, m_iImGuiStyle);
	{
		ImGui::SetWindowSize({ 450.f, 250.f });
		DrawIconAndTittle(xorstr("Network"));
		DrawCloseWindowButton();
        ImGui::PushFont(m_pFontSmallBold.get());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(-1, 0));

		if (ImGui::Button("Profile"))
			iTab = 0;

        ImGui::SameLine();
		if (ImGui::Button("Chat"))
			iTab = 1;
        ImGui::SameLine();
        ImGui::PopStyleVar();
		if (ImGui::Button("Cloud"))
			iTab = 2;
        ImGui::PopFont();
		
		switch (iTab)
		{
		case 0:
			DrawProfileSection(); break;
		case 1:
			break;
		case 2:
			DrawCloudSection();   break;
		}
		KeepWindowInScreenArea();

		ImGui::End();
	}
}
void UI::CNetWorkWindow::OnOpen()
{
	POLY_MARKER;
	m_bAvatarSetWindow = false;
#ifdef CLOUD_SUPPORT
	std::thread([this] {UpdateUserInfo(); }).detach();
#endif

}
std::string UI::CNetWorkWindow::GetAlias() const
{
	POLY_MARKER;
	return xorstr("Network");
}
UI::CNetWorkWindow::~CNetWorkWindow()
{
	POLY_MARKER;

	if (m_pTextureUserAvatar)
		m_pTextureUserAvatar->Release();

	m_pTextureDefaultAvatar->Release();
}
void UI::CNetWorkWindow::OnClose()
{
	POLY_MARKER;
#ifdef CLOUD_SUPPORT
	std::thread([this] {SendNewUserInfoToServer(m_UserData); }).detach();
	m_pMessageLineList->Add(xorstr("User data successfully updated."), 2000);
#endif

}
void UI::CNetWorkWindow::UpdateUserInfo()
{
	POLY_MARKER;
	m_ConfigsList       = m_pApiClient->GetListOfConfigs();
	m_UserData          = m_pApiClient->GetUserInfo();
	m_LoaderTheme	    = m_pApiClient->GetLoaderTheme();

}
void UI::CNetWorkWindow::SendNewUserInfoToServer(const WebApi::CUserInfo & info) const
{
	POLY_MARKER;
    m_pApiClient->ChangeUserNameAndStatus(info.m_sName, info.m_sStatus);
    m_pApiClient->UpdateLoaderTheme(m_LoaderTheme);
}
void UI::CNetWorkWindow::SetUserAvatar(const std::string& pathToFile)
{
	m_pMessageLineList->Add(xorstr("The avatar has been uploaded successfully."), 2000);
}

void UI::CNetWorkWindow::DrawConfigCombo(const char* label, int* CurrentItem, const std::vector<WebApi::CConfig>& list) const
{
	POLY_MARKER;
	auto tmpArr = std::unique_ptr<const char* []>(new const char* [list.size()]);

	for (size_t i = 0; i < list.size(); ++i)
	{
		tmpArr[i] = list[i].m_Settings.m_Name.c_str();
	};
	ImGui::Combo(label, CurrentItem, tmpArr.get(), list.size());
}
void UI::CNetWorkWindow::DrawProfileSection()
{
	PDIRECT3DTEXTURE9 validAvatar = m_pTextureUserAvatar ? m_pTextureUserAvatar : m_pTextureDefaultAvatar;


	{
		const bool avatarButtonStatus = ImGui::ImageButton(validAvatar, ImVec2(64, 64), ImVec2(), ImVec2(1, 1), 1);
		DrawToolTip(xorstr("Click on the avatar to change it."));
		if (avatarButtonStatus)
			m_bAvatarSetWindow = !m_bAvatarSetWindow;
	}

	ImGui::SameLine();
	ImVec2 textPos = ImGui::GetCursorPos();
	textPos.y += 20;

	ImGui::PushItemWidth(125);
	DrawInputTextWithTextOnBackGround(xorstr("###Name"), xorstr("<Nickname>"), m_UserData.m_sName, 32);
	ImGui::PopItemWidth();

	const ImVec2 cursorPos = ImGui::GetCursorPos();
	ImGui::SetCursorPos(textPos);
	if (m_UserData.m_iAccountType == -1)
		ImGui::TextColored(ImColor(255, 0, 0), xorstr("Connection: Failed"));
	else
		ImGui::TextColored(ImColor(0, 255, 0), xorstr("Connection: Synced"));

	textPos.y += 14;
	ImGui::SetCursorPos(textPos);
	ImGui::Text(xorstr("Account: %s"), m_UserData.AccountTypeIdToString().c_str());

	textPos.y += 14;
	ImGui::SetCursorPos(textPos);
	ImGui::Text(xorstr("AVHUID: %d"), m_UserData.m_iUid);

	ImGui::SameLine();

	if (m_bAvatarSetWindow)
	{
		ImGui::BeginChild(xorstr("###changeavatr"), ImVec2(197, 80), true, m_iImGuiStyle | ImGuiWindowFlags_NoScrollbar);
		{
			DrawInputTextWithTextOnBackGround(xorstr("###AvatarPath"), xorstr("<Avatar Path>"), m_AvatarPath, sizeof(m_AvatarPath));


			if (ImGui::Button(xorstr("Upload")))
			{
				std::thread([this] {SetUserAvatar(m_AvatarPath); }).detach();
			}

			ImGui::EndChild();
		}
	}
	else
	{
		ImGui::PushItemWidth(197);
		DrawMultiLineInputTextWithTextOnBackGround(xorstr("###Status"), xorstr("<Custom status>"), m_UserData.m_sStatus, 256);
		ImGui::PopItemWidth();
	}
}
void UI::CNetWorkWindow::DrawCloudSection()
{
	static int selectedCfgId = 0;
	ImGui::BeginChild(xorstr("###CheatConfigs"), {240, 110}, true);
	{
		ImGui::Text(xorstr("Settings Cloud"));
		if (m_ConfigsList.empty())
		{
			ImGui::EndChild();
			return;
		}

		if (ImGui::Button(xorstr("Upload"), ImVec2(70, 20)))
		{
			auto payload = [this]
			{
				const auto pSelectedCfg = &m_ConfigsList[selectedCfgId];
				GlobalVars::g_AllSettings.m_Name = pSelectedCfg->m_Settings.m_Name;

				if (const bool status = m_pApiClient->UpdateConfig(pSelectedCfg->m_iUid, GlobalVars::g_AllSettings.ToJson()); !status)
				{
					m_pMessageLineList->Add(xorstr("An error occurred while trying to update the config."), 3000);
					return;
				}

				m_pMessageLineList->Add(xorstr("Config has been successfully updated."), 3000);
				pSelectedCfg->m_Settings = GlobalVars::g_AllSettings;
			};

			std::thread(payload).detach();

		}

		ImGui::SameLine();

		ImGui::PushItemWidth(125);
		DrawInputTextWithTextOnBackGround(xorstr("###ConfigName"), xorstr("<Config name>"), (char*)m_ConfigsList[selectedCfgId].m_Settings.m_Name.c_str(),
			m_ConfigsList[selectedCfgId].m_Settings.m_Name.size());

		ImGui::PopItemWidth();

		if (ImGui::Button(xorstr("Import"), ImVec2(70, 20)))
		{
			GlobalVars::g_AllSettings = m_ConfigsList[selectedCfgId].m_Settings;
			m_pMessageLineList->Add(fmt::format("Config is loaded from the cloud: {}", m_ConfigsList[selectedCfgId].m_Settings.m_Name), 3000);
		}
		ImGui::SameLine();
		ImGui::PushItemWidth(125);
		DrawConfigCombo(xorstr("##CfgList"), &selectedCfgId, m_ConfigsList);
		ImGui::PopItemWidth();
		if (ImGui::Button(xorstr("Restore"), ImVec2(70, 20)))
		{
			auto payload = [this]
			{
				auto defaultSettings = Settings::CAllSettings();
				//defaultSettings.m_Name = fmt::format("Config - {}", selectedCfgId);
				//defaultSettings.m_Name.resize(32);

				if (const bool status = m_pApiClient->UpdateConfig(m_ConfigsList[selectedCfgId].m_iUid, defaultSettings.ToJson()); !status)
				{
					m_pMessageLineList->Add(xorstr("An error occurred while trying to restore the config."), 3000);
					return;
				}

				m_pMessageLineList->Add(xorstr("Config was successfully restored to the default settings."), 3000);

				m_ConfigsList[selectedCfgId].m_Settings = defaultSettings;
				GlobalVars::g_AllSettings = defaultSettings;

			};
			std::thread(payload).detach();

		}

		ImGui::EndChild();
	}

	ImGui::ColorEdit3(xorstr("Loader Icon (Not Active)"), (float*)&m_LoaderTheme.m_IconColor, ImGuiColorEditFlags_NoInputs);
	ImGui::ColorEdit3(xorstr("Loader Icon (Activated)"), (float*)&m_LoaderTheme.m_ActiveIconColor, ImGuiColorEditFlags_NoInputs);
	ImGui::ColorEdit3(xorstr("Loader Icon (Injected)"), (float*)&m_LoaderTheme.m_InjectedColor, ImGuiColorEditFlags_NoInputs);
	ImGui::ColorEdit3(xorstr("Loading Bar"), (float*)&m_LoaderTheme.m_LoadingColor, ImGuiColorEditFlags_NoInputs);
}
