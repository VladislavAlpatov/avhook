
#ifndef _RZCHROMASDK_H_
#define _RZCHROMASDK_H_

#pragma once

#include "RzErrors.h"
#include "RzChromaSDKDefines.h"
#include "RzChromaSDKTypes.h"

using namespace ChromaSDK;
using namespace ChromaSDK::Keyboard;
using namespace ChromaSDK::Mouse;
using namespace ChromaSDK::Headset;
using namespace ChromaSDK::Mousepad;
using namespace ChromaSDK::Keypad;
using namespace ChromaSDK::ChromaLink;

// Exported functions
#ifdef __cplusplus
extern "C"
{
#endif

    RZRESULT Init(void);

    RZRESULT InitSDK(APPINFOTYPE* pAppInfo);

    RZRESULT UnInit(void);

    RZRESULT CreateEffect(RZDEVICEID DeviceId, ChromaSDK::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID* pEffectId);

    RZRESULT CreateKeyboardEffect(ChromaSDK::Keyboard::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID* pEffectId);

    RZRESULT CreateMouseEffect(ChromaSDK::Mouse::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID* pEffectId);

    RZRESULT CreateHeadsetEffect(ChromaSDK::Headset::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID* pEffectId);

    RZRESULT CreateMousepadEffect(ChromaSDK::Mousepad::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID* pEffectId);

    RZRESULT CreateKeypadEffect(ChromaSDK::Keypad::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID* pEffectId);

    RZRESULT CreateChromaLinkEffect(ChromaSDK::ChromaLink::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID* pEffectId);

    RZRESULT DeleteEffect(RZEFFECTID EffectId);

    RZRESULT SetEffect(RZEFFECTID EffectId);

    RZRESULT RegisterEventNotification(HWND hWnd);

    RZRESULT UnregisterEventNotification();

    RZRESULT QueryDevice(RZDEVICEID DeviceId, DEVICE_INFO_TYPE& DeviceInfo);

#ifdef __cplusplus
}
#endif

#endif
