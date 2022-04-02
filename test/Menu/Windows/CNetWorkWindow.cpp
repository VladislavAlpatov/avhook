#include "CNetWorkWindow.h"
#include <thread>
#include "../../Globals/GlobalVars.h"
#include <fmt/format.h>

UI::CNetWorkWindow::CNetWorkWindow(LPDIRECT3DDEVICE9 pDevice, HMODULE  hModule, CMessageLineList* pMessageLineList) : CBaseWindow(pDevice, hModule)
{
	D3DXCreateTextureFromResourceA(m_pDevice, m_hModule, MAKEINTRESOURCEA(IDB_BITMAP12), &m_pTexureDefaulteAvatar);
	D3DXCreateTextureFromResourceA(m_pDevice, m_hModule, MAKEINTRESOURCEA(IDB_BITMAP13), &m_pTextureIcon);

	m_pMessageLineList = pMessageLineList;
	auto avatarRawData = m_ApiClient.GetRawAvatarData();

	D3DXCreateTextureFromFileInMemory(m_pDevice, avatarRawData.c_str(), avatarRawData.size(), &m_pTextureUserAvatar);

}
void UI::CNetWorkWindow::Render()
{

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
			DrawInputTextWithTextOnBackGround(xorstr("###Name"), xorstr("<Nickname>"), m_CurrentUserData.m_sName, 32);
			ImGui::PopItemWidth();

			ImVec2 cursorPos = ImGui::GetCursorPos();
			ImGui::SetCursorPos(textPos);
			if (m_CurrentUserData.m_iAccountType == -1)
				ImGui::TextColored(ImColor(255, 0, 0), xorstr("Connection: Failed"));
			else
				ImGui::TextColored(ImColor(0, 255, 0), xorstr("Connection: Synced"));

			textPos.y += 14;
			ImGui::SetCursorPos(textPos);
			ImGui::Text(xorstr("Account: %s"), m_CurrentUserData.AccountTypeIdToString());

			textPos.y += 14;
			ImGui::SetCursorPos(textPos);
			ImGui::Text(xorstr("AVHUID: %d"), m_CurrentUserData.m_iUid);

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
				DrawMultiLineInputTextWithTextOnBackGround(xorstr("###Status"), xorstr("<Custom status>"), m_CurrentUserData.m_sStatus, 256);
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
						GlobalVars::settings.m_Name = pSelectedCfg->m_Settings.m_Name;

						bool status = m_ApiClient.UpdateConfig(pSelectedCfg->m_iUid, GlobalVars::settings.ToJson());

						if (!status)
						{
							m_pMessageLineList->Add(xorstr("An error occurred while trying to update the config."), 3000);
							return;
						}

						m_pMessageLineList->Add(xorstr("Config has been successfully updated."), 3000);
						pSelectedCfg->m_Settings = GlobalVars::settings;
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
					GlobalVars::settings = m_ConfgsList[selectedCfgId].m_Settings;
					m_pMessageLineList->Add(fmt::format(xorstr("Config is loaded from the cloud: {}"), m_ConfgsList[selectedCfgId].m_Settings.m_Name), 3000);
				}
				ImGui::SameLine();
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
						GlobalVars::settings                   = defaultSettings;
						
					};
					std::thread(payload).detach();
				}
				DrawConfigCombo(xorstr("Configs"), &selectedCfgId, m_ConfgsList);
			}

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
UI::CNetWorkWindow::~CNetWorkWindow()
{
	POLY_MARKER;

	if (m_pTextureUserAvatar != nullptr)
		m_pTextureUserAvatar->Release();

	m_pTexureDefaulteAvatar->Release();
}
void UI::CNetWorkWindow::OnClose()
{
	POLY_MARKER;

	if (m_OldUserData != m_CurrentUserData)
	{
		std::thread([this] {SendNewUserInfoToServer(m_CurrentUserData); }).detach();
		m_pMessageLineList->Add(xorstr("User data successfully updated."), 2000);

	}
}
void UI::CNetWorkWindow::UpdateUserInfo()
{
	POLY_MARKER;
	m_ConfgsList       = m_ApiClient.GetListOfConfigs();
	m_OldUserData      = m_ApiClient.GetUserInfo();
	m_CurrentUserData = m_OldUserData;
}
void UI::CNetWorkWindow::SendNewUserInfoToServer(const WebApi::CUserInfo & info)
{

	m_ApiClient.ChangeUserNameAndStatus(info.m_sName, info.m_sStatus);
}
void UI::CNetWorkWindow::SetUserAvatar(const std::string pathToFile)
{

	std::ifstream file(pathToFile, std::ios::binary | std::ios::ate);


	int fileSize = file.tellg();
	if (!file.is_open())
	{
		m_pMessageLineList->Add(xorstr("Could not open the file!"), 2000, ImColor(255, 0, 0));
		return;
	}
	else if (fileSize > 20 * 1024)
	{
		m_pMessageLineList->Add(xorstr("The file size is too large.\nMaximum file size: 20 kilobytes!"), 2000, ImColor(255, 0, 0));
		return;
	}

	char* tmpFileData = new char[fileSize];
	file.seekg(0, std::ios::beg);
	file.read(tmpFileData, fileSize);
	m_avatarUploadStatus =  m_ApiClient.SetUserAvatar(std::string(tmpFileData, fileSize));

	auto avatarRawData = m_ApiClient.GetRawAvatarData();

	D3DXCreateTextureFromFileInMemory(m_pDevice, avatarRawData.c_str(), avatarRawData.size(), &m_pTextureUserAvatar);
	m_pMessageLineList->Add(xorstr("The avatar has been uploaded successfully."), 2000);

	delete[] tmpFileData;

}