#include "../IBaseDrawObject.h"


class CBindListenerOverlay : public IBaseDrawObject
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