#pragma once

#include <d3dx9.h>
#include <fmt/format.h>
#include <thread>

#include "CNetWorkWindow.h"

#include "../../Globals/Settings.h"
#include "../../RawData/Images.h"
#include "../../Utils/Marker.h"

UI::CNetWorkWindow::CNetWorkWindow(LPDIRECT3DDEVICE9 pDevice, CMessageLineList* pMessageLineList) : CBaseWindow(pDevice)
{
	POLY_MARKER;

	D3DXCreateTextureFromFileInMemory(m_pDevice, Images::DefaultAvatar, sizeof(Images::DefaultAvatar), &m_pTexureDefaulteAvatar);
	D3DXCreateTextureFromFileInMemory(m_pDevice, Images::ProfileIcon,   sizeof(Images::ProfileIcon),   &m_pTextureIcon);

	
	m_pMessageLineList = pMessageLineList;
	auto avatarRawData = m_ApiClient.GetRawAvatarData();

	D3DXCreateTextureFromFileInMemory(m_pDevice, avatarRawData.c_str(), avatarRawData.size(), &m_pTextureUserAvatar);

}
void UI::CNetWorkWindow::Render()
{
	POLY_MARKER;

	ImGui::Begin(xorstr("###Network"), nullptr, m_iImGuiStyle);
	{
		DrawIconAndTittle(xorstr("Network"));
		DrawCloseWindowButton();
		ImGui::BeginChild(xorstr("###Profile"), ImVec2(220, 210), true, m_iImGuiStyle);
		{
			PDIRECT3DTEXTURE9 validAvatar = NULL;

			if (m_pTextureUserAvatar != nullptr)
				validAvatar = m_pTextureUserAvatar;
			else
				validAvatar = m_pTexureDefaulteAvatar;

			{
				bool avatarButtonStatus = ImGui::ImageButton(validAvatar, ImVec2(64, 64), ImVec2(), ImVec2(1, 1), 1);
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

			ImVec2 cursorPos = ImGui::GetCursorPos();
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

			ImGui::SetCursorPos(cursorPos);

			if (m_bAvatarSetWindow)
			{
				ImGui::BeginChild(xorstr("###changeavatr"), ImVec2(197, 80), true, m_iImGuiStyle | ImGuiWindowFlags_NoScrollbar);
				{
					DrawInputTextWithTextOnBackGround(xorstr("###AvatarPath"), xorstr("<Avatar Path>"), m_AvatarPath, sizeof(m_AvatarPath));

					std::ifstream file(m_AvatarPath);

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

			ImGui::EndChild();
		}
		ImGui::SameLine();
		ImGui::BeginChild(xorstr("###Cloud"), ImVec2(220, 210), true, m_iImGuiStyle);
		{
			static int selectedCfgId = 0;
			if (!m_ConfgsList.empty())
			{
				if (ImGui::Button(xorstr("Upload"), ImVec2(70, 20)))
				{
					auto payload = [this]
					{
						auto pSelectedCfg           = &m_ConfgsList[selectedCfgId];
						GlobalVars::g_AllSettings.m_Name = pSelectedCfg->m_Settings.m_Name;

						bool status = m_ApiClient.UpdateConfig(pSelectedCfg->m_iUid, GlobalVars::g_AllSettings.ToJson());

						if (!status)
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
				DrawInputTextWithTextOnBackGround(xorstr("###ConfigName"), xorstr("<Config name>"), (char*)m_ConfgsList[selectedCfgId].m_Settings.m_Name.c_str(),
					m_ConfgsList[selectedCfgId].m_Settings.m_Name.size());

				ImGui::PopItemWidth();

				if (ImGui::Button(xorstr("Import"), ImVec2(70, 20)))
				{
					GlobalVars::g_AllSettings = m_ConfgsList[selectedCfgId].m_Settings;
					m_pMessageLineList->Add(fmt::format(xorstr("Config is loaded from the cloud: {}"), m_ConfgsList[selectedCfgId].m_Settings.m_Name), 3000);
				}
				ImGui::SameLine();
				ImGui::PushItemWidth(125);
				DrawConfigCombo(xorstr("##CfgList"), &selectedCfgId, m_ConfgsList);
				ImGui::PopItemWidth();
				if (ImGui::Button(xorstr("Restore"), ImVec2(70, 20)))
				{
					auto payload = [this]
					{
						auto defaultSettings = Settings::CAllSettings();
						defaultSettings.m_Name = fmt::format(xorstr("Config - {}"), selectedCfgId);
						defaultSettings.m_Name.resize(32);

						bool status = m_ApiClient.UpdateConfig(m_ConfgsList[selectedCfgId].m_iUid, defaultSettings.ToJson());

						if (!status)
						{
							m_pMessageLineList->Add(xorstr("An error occurred while trying to restore the config."), 3000);
							return;
						}

						m_pMessageLineList->Add(xorstr("Config was successfully restored to the default settings."), 3000);

						m_ConfgsList[selectedCfgId].m_Settings = defaultSettings;
						GlobalVars::g_AllSettings = defaultSettings;
						
					};
					std::thread(payload).detach();
				}
			}


			ImGui::ColorEdit3(xorstr("Loader Icon (Not Active)"), (float*)&m_LoaderTheme.m_IconColor, ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit3(xorstr("Loader Icon (Activated)"),  (float*)&m_LoaderTheme.m_ActiveIconColor, ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit3(xorstr("Loader Icon (Injected)"),   (float*)&m_LoaderTheme.m_InjectedColor, ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit3(xorstr("Loading Bar"),              (float*)&m_LoaderTheme.m_LoadingColor, ImGuiColorEditFlags_NoInputs);

			ImGui::EndChild();
		}
		KeepWindowInSreenArea();
		ImGui::End();
	}
}
void UI::CNetWorkWindow::OnOpen()
{
	POLY_MARKER;
	m_bAvatarSetWindow = false;
	std::thread([this] {UpdateUserInfo(); }).detach();
}
std::string UI::CNetWorkWindow::GetAlias()
{
	POLY_MARKER;
	return xorstr("Network");
}
UI::CNetWorkWindow::~CNetWorkWindow()
{
	POLY_MARKER;

	if (m_pTextureUserAvatar)
		m_pTextureUserAvatar->Release();

	m_pTexureDefaulteAvatar->Release();
}
void UI::CNetWorkWindow::OnClose()
{
	POLY_MARKER;

	std::thread([this] {SendNewUserInfoToServer(m_UserData); }).detach();
	m_pMessageLineList->Add(xorstr("User data successfully updated."), 2000);
}
void UI::CNetWorkWindow::UpdateUserInfo()
{
	POLY_MARKER;
	m_ConfgsList       = m_ApiClient.GetListOfConfigs();
	m_UserData = m_ApiClient.GetUserInfo();
	m_LoaderTheme	   = m_ApiClient.GetLoaderTheme();

}
void UI::CNetWorkWindow::SendNewUserInfoToServer(const WebApi::CUserInfo & info)
{
	POLY_MARKER;
	m_ApiClient.ChangeUserNameAndStatus(info.m_sName, info.m_sStatus);
	m_ApiClient.UpdateLoaderTheme(m_LoaderTheme);
}
void UI::CNetWorkWindow::SetUserAvatar(const std::string& pathToFile)
{
	POLY_MARKER;
	std::ifstream file(pathToFile, std::ios::binary | std::ios::ate);

	if (!file.is_open())
	{
		m_pMessageLineList->Add(xorstr("Could not open the file!"), 2000, ImColor(255, 0, 0));
		return;
	}

	int fileSize = file.tellg();

	if (fileSize > 20 * 1024)
	{
		m_pMessageLineList->Add(xorstr("The file size is too large.\nMaximum file size: 20 kilobytes!"), 2000, ImColor(255, 0, 0));
		return;
	}

	auto tmpFileData = std::unique_ptr<char[]>(new char[fileSize]);
	file.seekg(0, std::ios::beg);
	file.read(tmpFileData.get(), fileSize);
	m_avatarUploadStatus =  m_ApiClient.SetUserAvatar(std::string(tmpFileData.get(), fileSize));

	auto avatarRawData = m_ApiClient.GetRawAvatarData();

	D3DXCreateTextureFromFileInMemory(m_pDevice, avatarRawData.c_str(), avatarRawData.size(), &m_pTextureUserAvatar);
	m_pMessageLineList->Add(xorstr("The avatar has been uploaded successfully."), 2000);
}

void UI::CNetWorkWindow::DrawConfigCombo(const char* label, int* CurrentItem, const std::vector<WebApi::CConfig>& list)
{
	POLY_MARKER;
	auto tmpArr = std::unique_ptr<const char* []>(new const char* [list.size()]);

	for (int i = 0; i < list.size(); ++i)
	{
		tmpArr[i] = list[i].m_Settings.m_Name.c_str();
	};
	ImGui::Combo(label, CurrentItem, tmpArr.get(), list.size());
}
