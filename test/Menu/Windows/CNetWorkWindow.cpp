#include "CNetWorkWindow.h"

CNetWorkWindow::CNetWorkWindow(LPDIRECT3DDEVICE9 pDevice, HMODULE  hModule) : CBaseWindow(pDevice, hModule)
{
	D3DXCreateTextureFromResourceA(m_pDevice, m_hModule, MAKEINTRESOURCE(IDB_BITMAP12), &m_pTexureDefaulteAvatar);
	D3DXCreateTextureFromResourceA(m_pDevice, m_hModule, MAKEINTRESOURCE(IDB_BITMAP13), &m_pTextureIcon);
}
void CNetWorkWindow::Render()
{
	ImGui::Begin(xorstr("###Network"), nullptr, m_iImGuiStyle);
	{
		DrawIconAndTittle(xorstr("Network"));
		DrawCloseWindowButton();
		ImGui::BeginChild(xorstr("###Profile"), ImVec2(220, 210), true, m_iImGuiStyle);
		{
			if (m_pTextureUserAvatar != nullptr)
				DrawImageWithBorder(m_pTextureUserAvatar, ImVec2(64, 64));
			else
				DrawImageWithBorder(m_pTexureDefaulteAvatar, ImVec2(64, 64));

			ImGui::SameLine();
			ImVec2 textPos = ImGui::GetCursorPos();
			textPos.y += 20;

			POLY_MARKER

			ImGui::PushItemWidth(125);
			DrawInputTextWithTextOnBackGround(xorstr("###Name"), xorstr("<Nickname>"), m_CurrentUserData.m_sName, 32);
			ImGui::PopItemWidth();

			ImVec2 cursorPos = ImGui::GetCursorPos();
			ImGui::SetCursorPos(textPos);
			ImGui::TextColored(ImColor(0, 255, 0), xorstr("Connection: Synced"));

			textPos.y += 14;
			ImGui::SetCursorPos(textPos);
			ImGui::Text(xorstr("Account: %s"), m_CurrentUserData.AccountTypeIdToString());

			textPos.y += 14;
			ImGui::SetCursorPos(textPos);
			ImGui::Text(xorstr("AVHUID: %d"), m_CurrentUserData.m_iUid);

			ImGui::SetCursorPos(cursorPos);

			ImGui::PushItemWidth(197);
			DrawMultiLineInputTextWithTextOnBackGround(xorstr("###Status"),xorstr("<Custom status>"), m_CurrentUserData.m_sStatus, 256);
			ImGui::PopItemWidth();

			ImGui::EndChild();
		}
		ImGui::SameLine();
		ImGui::BeginChild(xorstr("###Cloud"), ImVec2(220, 210), true);
		{
			ImGui::EndChild();
		}
		KeepWindowInSreenArea();
		ImGui::End();
	}
}

void CNetWorkWindow::OnOpen()
{
	POLY_MARKER;
	if (m_pTextureUserAvatar != nullptr)
	{
		m_pTextureUserAvatar->Release();
		m_pTextureUserAvatar = nullptr;
	}
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

	auto serverClient = CAVHookServerApi();
	m_OldUserData = serverClient.GetUserInfo(GlobalVars::userEmail);
	auto avatarRawData = serverClient.GetRawAvatarDataByUserId(m_OldUserData.m_iUid);

	if (m_pTextureUserAvatar)
		m_pTextureUserAvatar->Release();

	D3DXCreateTextureFromFileInMemory(m_pDevice, avatarRawData.c_str(), avatarRawData.size(), &m_pTextureUserAvatar);
	m_CurrentUserData = m_OldUserData;
}
void CNetWorkWindow::SendNewUserInfoToServer(const CUserInfo& info)
{
	CAVHookServerApi().SetUserNameAndStatus(GlobalVars::userEmail, info.m_sName, info.m_sStatus);
}