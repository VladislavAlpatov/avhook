#include "CRadarWindow.h"

ImVec2 UI::CRadarWindow::WorldToRadar(const ImVec3& EntityOrigin, const ImVec3& LocalPlayerOrigin, const ImVec3& LocalPlayerViewAngles, int width, float scale = 16.f)
{
	float x_diff = EntityOrigin.x - LocalPlayerOrigin.x;
	float y_diff = EntityOrigin.y - LocalPlayerOrigin.y;

	int iRadarRadius = width;

	float flOffset = atanf(y_diff / x_diff);
	flOffset *= 180;
	flOffset /= 3.14159f;

	if ((x_diff < 0) && (y_diff >= 0))
		flOffset = 180 + flOffset;

	else if ((x_diff < 0) && (y_diff < 0))
		flOffset = 180 + flOffset;

	else if ((x_diff >= 0) && (y_diff < 0))
		flOffset = 360 + flOffset;

	y_diff = -1 * (sqrtf((x_diff * x_diff) + (y_diff * y_diff)));
	x_diff = 0;

	flOffset = LocalPlayerViewAngles.y - flOffset;

	flOffset *= 3.14159f;
	flOffset /= 180;

	float xnew_diff = x_diff * cosf(flOffset) - y_diff * sinf(flOffset);
	float ynew_diff = x_diff * sinf(flOffset) + y_diff * cosf(flOffset);

	xnew_diff /= scale;
	ynew_diff /= scale;

	xnew_diff = (iRadarRadius / 2) + static_cast<int>(xnew_diff);
	ynew_diff = (iRadarRadius / 2) + static_cast<int>(ynew_diff);

	if (xnew_diff > iRadarRadius)
		xnew_diff = static_cast<float>(iRadarRadius - 4);
	else if (xnew_diff < 4)
		xnew_diff = 4;

	if (ynew_diff > iRadarRadius)
		ynew_diff = static_cast<float>(iRadarRadius);
	else if (ynew_diff < 4)
		ynew_diff = 0;

	return ImVec2(xnew_diff, ynew_diff);
}
void UI::CRadarWindow::KeepWindowInSreenArea()
{
	ImVec2 currentWindowPosition      = ImGui::GetWindowPos();
	ImVec2 currentWindowSize          = ImGui::GetWindowSize();
	ImVec2 viewPortSize               = ImGui::GetMainViewport()->Size;
	ImVec2 newWindowPosition          = ImGui::GetWindowPos();

	if (currentWindowPosition.x + currentWindowSize.x > viewPortSize.x)
		newWindowPosition.x = viewPortSize.x - currentWindowSize.x;

	else if (currentWindowPosition.y + currentWindowSize.y > viewPortSize.y)
		newWindowPosition.y = viewPortSize.y - currentWindowSize.y;

	else if (currentWindowPosition.x < 0)
		newWindowPosition.x = 0;

	else if (currentWindowPosition.y < 0)
		newWindowPosition.y = 0;

	ImGui::SetWindowPos(newWindowPosition);
	
}
void UI::CRadarWindow::Render()
{
	if (m_pRadarSettings->m_bDrawBorders)
		ImGui::Begin(xorstr("###Radar"), NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
	else
		ImGui::Begin(xorstr("###Radar"), NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground);
	{
		ImGui::SetWindowSize(ImVec2(384, 256));

		const auto windowPosition = ImGui::GetWindowPos();
		const auto windowCenter   = windowPosition + ImGui::GetWindowSize() / 2.f;

		auto pDrawList = ImGui::GetWindowDrawList();

		pDrawList->AddCircleFilled(windowCenter, 254.f / 2.f, m_pRadarSettings->m_BackGroundColor);

		// Draw cross
		pDrawList->AddLine(windowCenter + ImVec2(0, 254.f / 2.f), windowCenter - ImVec2(0, 254.f / 2.f), m_pRadarSettings->m_CrossColor, 2.f);
		pDrawList->AddLine(windowCenter + ImVec2(254.f / 2.f, 0), windowCenter - ImVec2(254.f / 2.f, 0), m_pRadarSettings->m_CrossColor, 2.f);
		// Draw Circle Border
		pDrawList->AddCircle(windowCenter, 254.f / 2.f, m_pRadarSettings->m_CyrcleBorderColor, 0, 2.f);

		// if player not in game then dont draw
		if (!GlobalVars::pIEngineClient->IsInGame() or !GlobalVars::pIEngineClient->IsConnected() or !GlobalVars::client->pLocalPlayer)
		{
			KeepWindowInSreenArea();
			ImGui::End();
			return;
		}

		for (int i = 1; i < 33; ++i)
		{
			auto pEnt = GlobalVars::pIEntityList->GetClientEntity(i);

			if (!pEnt or !pEnt->IsAlive() or pEnt->m_iTeamNum == GlobalVars::client->pLocalPlayer->m_iTeamNum)
				continue;
			auto windowPosition = ImGui::GetWindowPos();
			
			auto vecEntityRadarPosition = WorldToRadar(pEnt->m_vecOrigin, GlobalVars::client->pLocalPlayer->m_vecOrigin, GlobalVars::veLocalPlayerViewAngles, 256);

			ImColor enemyColor = ImColor(255, 255, 255);
			if (GlobalVars::settings.m_AimBotSettings.m_pCurrentTarget == pEnt)
				enemyColor = ImColor(255, 0, 255);
			pDrawList->AddCircleFilled(ImVec2(windowPosition.x + vecEntityRadarPosition.x + 384.f / 6.0f, windowPosition.y + vecEntityRadarPosition.y), 4, ImColor(0,0,0));
			pDrawList->AddCircleFilled(ImVec2(windowPosition.x + vecEntityRadarPosition.x + 384.f / 6.0f, windowPosition.y + vecEntityRadarPosition.y), 3, enemyColor);
		}

		KeepWindowInSreenArea();
		ImGui::End();
	}
}
