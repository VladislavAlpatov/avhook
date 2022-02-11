#pragma once
#include "CBaseWindow.h"

class CBindDialog : public CBaseWindow
{
public:
	CBindDialog(unsigned int* pKeyValue);
	virtual void Render();
private:
	unsigned int* m_pKeyValue = nullptr;
};