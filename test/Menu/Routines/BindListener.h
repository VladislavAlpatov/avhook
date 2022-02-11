#pragma once
#include <thread>
#include <Windows.h>
#include "../../RazerSDK/CRazer.h"
#include "../../Globals/GlobalVars.h"
class CBindListener
{
public:
	CBindListener() 
	{
		m_pVirtualKeyValue = nullptr;
		m_pShowKeyBinderDialog = nullptr;
	}
	CBindListener(int* pVirtualKeyValue, bool* pShowKeyBinderDialog);
	int* m_pVirtualKeyValue;
	bool*         m_pShowKeyBinderDialog;

	void Listen();
private:
	static void RutineThread(int* pVirtualKeyValue, bool* pShowKeyBinderDialog);
	static void ChromaEffect(int keyNum);

};
