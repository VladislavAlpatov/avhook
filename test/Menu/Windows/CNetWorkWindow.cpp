#include "CNetWorkWindow.h"

CNetWorkWindow::CNetWorkWindow(LPDIRECT3DDEVICE9 pDevice, HMODULE  hModule) : CBaseWindow(pDevice, hModule)
{
	D3DXCreateTextureFromResourceA(m_pDevice, m_hModule, MAKEINTRESOURCE(IDB_BITMAP12), &m_pTexureDefaulteAvatar);
	D3DXCreateTextureFromResourceA(m_pDevice, m_hModule, MAKEINTRESOURCE(IDB_BITMAP13), &m_pTextureIcon);

	auto avatarRawData = m_ApiClient.GetRawAvatarData();
	D3DXCreateTextureFromFileInMemory(m_pDevice, avatarRawData.c_str(), avatarRawData.size(), &m_pTextureUserAvatar);

}
void CNetWorkWindow::Render()
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
				ImGui::BeginChild(xorstr("###changeavatr"), ImVec2(197, 100), true, m_iImGuiStyle | ImGuiWindowFlags_NoScrollbar);
				{
					DrawInputTextWithTextOnBackGround(xorstr("###AvatarPath"), xorstr("<Avatar Path>"), m_AvatarPath, sizeof(m_AvatarPath));

					std::ifstream file(m_AvatarPath);

					if (m_AvatarPath[0] == NULL)
						ImGui::Text(xorstr("Path: Empty"));

					else if (file.is_open())
						ImGui::TextColored(ImColor(0, 255, 0), xorstr("Path: Valid"));

					else
						ImGui::TextColored(ImColor(255, 0, 0), xorstr("Path: Invalid Path"));

					if (m_avatarUploadStatus.m_isSucced)
					{
						ImGui::TextColored(ImColor(0, 255, 0), xorstr("Upload: Succeed"));
					}
					else
					{
						ImGui::TextColored(ImColor(255, 0, 0), std::format("Upload: {}",m_avatarUploadStatus.m_sErrorMessage).c_str());
					}

					if (ImGui::Button(xorstr("Upload")) and file.is_open())
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
			ImGui::BeginChild(xorstr("###Cloud"), ImVec2(180, 100), true);
			{
				
				ImGui::EndChild();
			}

			ImGui::EndChild();
		}
		KeepWindowInSreenArea();
		ImGui::End();
	}
}
void CNetWorkWindow::OnOpen()
{
	POLY_MARKER;
	m_bAvatarSetWindow = false;
	std::thread([this] {UpdateUserInfo(); }).detach();
}
CNetWorkWindow::~CNetWorkWindow()
{
	POLY_MARKER;

	if (m_pTextureUserAvatar != nullptr)
		m_pTextureUserAvatar->Release();

	m_pTexureDefaulteAvatar->Release();
}
void CNetWorkWindow::OnClose()
{
	POLY_MARKER;

	if (m_OldUserData != m_CurrentUserData)
		std::thread([this] {SendNewUserInfoToServer(m_CurrentUserData); }).detach();
}
void CNetWorkWindow::UpdateUserInfo()
{
	POLY_MARKER;

	m_OldUserData      = m_ApiClient.GetUserInfo();
	m_CurrentUserData = m_OldUserData;
}
void CNetWorkWindow::SendNewUserInfoToServer(const CUserInfo& info)
{
	m_ApiClient.ChangeUserNameAndStatus(info.m_sName, info.m_sStatus);
}
void CNetWorkWindow::SetUserAvatar(const std::string pathToFile)
{

	std::ifstream file(pathToFile, std::ios::binary | std::ios::ate);


	int fileSize = file.tellg();

	if (fileSize > 20 * 1024)
		return;

	char* tmpFileData = new char[fileSize];
	file.seekg(0, std::ios::beg);
	file.read(tmpFileData, fileSize);
	m_avatarUploadStatus =  m_ApiClient.SetUserAvatar(std::string(tmpFileData, fileSize));

	auto avatarRawData = m_ApiClient.GetRawAvatarData();
	D3DXCreateTextureFromFileInMemory(m_pDevice, avatarRawData.c_str(), avatarRawData.size(), &m_pTextureUserAvatar);

	delete[] tmpFileData;

}