#pragma once
#include "RzChromaSDK.h"
#include <unordered_map>
#include "../Utils/xorstr.h"
#include <exception>
#include "CRazerExceptions.h"

static const std::unordered_map<int, int> WinApiKeyToRzKey =
{
    {VK_LSHIFT,   ChromaSDK::Keyboard::RZKEY_LSHIFT},
    {VK_LCONTROL, ChromaSDK::Keyboard::RZKEY_LCTRL},
};

class CRazer
{
public:
	CRazer()
	{
		m_RazerModule = GetModuleHandleA(xorstr("RzChromaSDK"));
		
		if (m_RazerModule == nullptr)
            m_RazerModule = LoadLibraryA(xorstr("C:\\Windows\\SysWOW64\\RzChromaSDK.dll"));

	}
    bool isSupported()
    {
        return (bool)m_RazerModule;
    }
    RZRESULT Init();
    RZRESULT InitSDK(APPINFOTYPE* pAppInfo);
    typedef RZRESULT(__cdecl* tInitSDK)(APPINFOTYPE* pAppInfo);

    RZRESULT UnInit(void);
    typedef RZRESULT(__cdecl* tUnInit)();

    RZRESULT CreateEffect(RZDEVICEID DeviceId, ChromaSDK::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID* pEffectId);
    typedef RZRESULT(__cdecl* tCreateEffect)(RZDEVICEID DeviceId, ChromaSDK::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID* pEffectId);

    RZRESULT CreateKeyboardEffect(ChromaSDK::Keyboard::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID* pEffectId);
    typedef RZRESULT(__cdecl* tCreateKeyboardEffect)(ChromaSDK::Keyboard::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID* pEffectId);

    RZRESULT DeleteEffect(RZEFFECTID EffectId);
    typedef RZRESULT(__cdecl* tDeleteEffect)(RZEFFECTID EffectId);

    RZRESULT SetEffect(RZEFFECTID EffectId);
    typedef RZRESULT(__cdecl* tSetEffect)(RZEFFECTID EffectId);


    int VirtualKeyToRZkey(int keyNum)
    {
        using namespace ChromaSDK::Keyboard;
        
        switch (keyNum)
        {
        
        case 0x09:
            return RZKEY_TAB;
            break;

        case 0x10:
            return RZKEY_LSHIFT;
            break;

        case VK_LCONTROL:
            return RZKEY_LCTRL;
            break;

        case VK_SPACE:
            return RZKEY_SPACE;
            break;

        case VK_MENU:
            return RZKEY_LALT;
            break;

        case 0x30:
            return RZKEY_0;
            break;

        case 0x31:
            return RZKEY_1;
            break;

        case 0x32:
            return RZKEY_2;
            break;

        case 0x33:
            return RZKEY_3;
            break;

        case 0x34:
            return RZKEY_4;
            break;

        case 0x35:
            return RZKEY_5;
            break;

        case 0x36:
            return RZKEY_6;
            break;

        case 0x37:
            return RZKEY_7;
            break;

        case 0x38:
            return RZKEY_8;
            break;

        case 0x41:
            return RZKEY_A;
            break;

        case 0x42:
            return RZKEY_B;
            break;

        case 0x43:
            return RZKEY_C;
            break;

        case 0x44:
            return RZKEY_D;
            break;

        case 0x45:
            return RZKEY_E;
            break;

        case 0x46:
            return RZKEY_F;
            break;

        case 0x47:
            return RZKEY_G;
            break;

        case 0x48:
            return RZKEY_H;
            break;

        case 0x49:
            return RZKEY_I;
            break;

        case 0x4A:
            return RZKEY_J;
            break;

        case 0x4B:
            return RZKEY_K;
            break;

        case 0x4C:
            return RZKEY_L;
            break;

        case 0x4D:
            return RZKEY_M;
            break;
        case 0x4E:
            return RZKEY_N;
            break;

        case 0x4F:
            return RZKEY_O;
            break;

        case 0x50:
            return RZKEY_P;
            break;

        case 0x51:
            return RZKEY_Q;
            break;

        case 0x52:
            return RZKEY_R;
            break;

        case 0x53:
            return RZKEY_S;
            break;

        case 0x54:
            return RZKEY_T;
            break;

        case 0x55:
            return RZKEY_U;
            break;

        case 0x56:
            return RZKEY_V;
            break;

        case 0x57:
            return RZKEY_W;
            break;

        case 0x58:
            return RZKEY_X;
            break;

        case 0x59:
            return RZKEY_Y;
            break;

        case 0x5A:
            return RZKEY_Z;
            break;

        case VK_LMENU:
            return RZKEY_LALT;
            break;

        case VK_LSHIFT:
            return RZKEY_LSHIFT;
            break;

        case VK_RCONTROL:
            return RZKEY_RCTRL;
            break;

        case VK_RETURN:
            return RZKEY_ENTER;
            break;

        case VK_CAPITAL:
            return RZKEY_CAPSLOCK;
            break;

        default:
            return -1;
        }
    }
private:
	HMODULE m_RazerModule = nullptr;


};