#include "../IBaseDrawObject.h"
#include "../../imgui/imgui.h"


class CBindListenerOverlay : public UI::IBaseDrawObject
{
public:
	CBindListenerOverlay(ImFont* pFont)
	{
		m_pFont = pFont;
	}
	virtual void Show();

private:
	ImFont* m_pFont = nullptr;
	virtual void Render();
};