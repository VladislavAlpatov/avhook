#include "CSkynetWindow.h"

CSkyNetWindow::CSkyNetWindow(LPDIRECT3DDEVICE9 pDevice, HMODULE  hModule) : CBaseWindow(pDevice, hModule)
{

}
void CSkyNetWindow::Render()
{
	ImGui::Begin(xorstr("###Skynet"), NULL, m_iImGuiStyle);
	ImGui::SetWindowSize(ImVec2(800, 340));

	DrawIconAndTittle(xorstr("Skynet"));
	DrawCloseWindowButton();

	ImGui::BeginChild(xorstr("Child###xd"), ImVec2(785, 300), true, ImGuiWindowFlags_NoScrollbar);
	{
		//ImGui::Text(GlobalVars::buff);
	}
	ImGui::EndChild();
	ImGui::End();
}