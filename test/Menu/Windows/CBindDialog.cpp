#include "CBindDialog.h"

CBindDialog::CBindDialog(unsigned int* pKeyValue) : CBaseWindow()
{
	m_pKeyValue = pKeyValue;
}
void CBindDialog::Render()
{
	auto pDrawList = ImGui::GetForegroundDrawList();

}