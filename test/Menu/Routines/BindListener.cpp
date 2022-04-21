#pragma once
#include <thread>
#include <Windows.h>
#include "../../RazerSDK/CRazer.h"
#include "../../Globals/GlobalVars.h"

#include "BindListener.h"

using namespace Routines;


CBindListener::CBindListener(int* pVirtualKeyValue, bool* pShowKeyBinderDialog)
{
	m_pVirtualKeyValue     = pVirtualKeyValue;
	m_pShowKeyBinderDialog = pShowKeyBinderDialog;

}
void CBindListener::Listen()
{
	std::thread([this]{RutineThread();}).detach();
}
void CBindListener::RutineThread()
{
	*m_pShowKeyBinderDialog = true;
	Sleep(500);
	while (true)
	{
		for (int keyNum = 0; keyNum < 0xFE + 1; ++keyNum)
		{
			if (GetAsyncKeyState(keyNum) & 0x8000)
			{
				if (keyNum == VK_ESCAPE)
					*m_pVirtualKeyValue = NULL;
				else if (keyNum == VK_SNAPSHOT)
					continue;
				else
				{

					if (GlobalVars::bChromaSupport)
						std::thread([this](int key) { ChromaEffect(key); }, keyNum).detach();

					*m_pVirtualKeyValue = keyNum;
				}

				*m_pShowKeyBinderDialog = false;
				return;
			}
		}
		Sleep(50);
	}
}
void CBindListener::ChromaEffect(int keyNum)
{
	auto razer    = CRazer();
	int bindedKey = razer.VirtualKeyToRZkey(keyNum);

	if (bindedKey == -1)
		return;

	RZEFFECTID glowBinededKeyId;
	RZEFFECTID idleGlowColorId;


	ChromaSDK::Keyboard::STATIC_EFFECT_TYPE idleGlowColor;
	idleGlowColor.Color = RGB(255, 255, 255);


	ChromaSDK::Keyboard::CUSTOM_KEY_EFFECT_TYPE glowBinededKey = {};
	glowBinededKey.Key[HIBYTE(bindedKey)][LOBYTE(bindedKey)] = 0x01000000 | RGB(0, 255, 0);


	razer.CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_CUSTOM_KEY, &glowBinededKey,      &glowBinededKeyId);
	razer.CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_STATIC,     &idleGlowColor,       &idleGlowColorId);
	
	razer.SetEffect(glowBinededKeyId);
	Sleep(500);
	razer.SetEffect(idleGlowColorId);
	
	razer.DeleteEffect(glowBinededKeyId);
	razer.DeleteEffect(idleGlowColorId);
}