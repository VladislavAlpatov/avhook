#include "CRazer.h"

RZRESULT CRazer::Init()
{
	typedef RZRESULT(__cdecl* tInit)();
	tInit init = (tInit)GetProcAddress(m_RazerModule, xorstr("Init"));

	return init();
}

RZRESULT CRazer::InitSDK(APPINFOTYPE* pAppInfo)
{
	APPINFOTYPE appInfo;
	tInitSDK func = (tInitSDK)GetProcAddress(m_RazerModule, xorstr("InitSDK"));
	return func(pAppInfo);
}
RZRESULT CRazer::UnInit()
{
	tUnInit func = (tUnInit)GetProcAddress(m_RazerModule, xorstr("UnInit"));
	return func();
}
RZRESULT CRazer::CreateEffect(RZDEVICEID DeviceId, ChromaSDK::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID* pEffectId)
{
	tCreateEffect func = (tCreateEffect)GetProcAddress(m_RazerModule, xorstr("CreateEffect"));
	return func(DeviceId, Effect, pParam, pEffectId);
}

RZRESULT CRazer::CreateKeyboardEffect(ChromaSDK::Keyboard::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID* pEffectId)
{
	tCreateKeyboardEffect func = (tCreateKeyboardEffect)GetProcAddress(m_RazerModule, xorstr("CreateKeyboardEffect"));
	return func(Effect, pParam, pEffectId);
}
RZRESULT CRazer::DeleteEffect(RZEFFECTID EffectId)
{
	tDeleteEffect func = (tDeleteEffect)GetProcAddress(m_RazerModule, xorstr("DeleteEffect"));
	return func(EffectId);
}
RZRESULT CRazer::SetEffect(RZEFFECTID EffectId)
{
	tSetEffect func = (tSetEffect)GetProcAddress(m_RazerModule, xorstr("SetEffect"));
	return func(EffectId);
}