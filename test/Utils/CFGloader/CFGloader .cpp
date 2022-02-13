#include "CFGloader.h"


void CConfigLoader::DumpConfigFile(std::string path)
{
	json outCfgJson;
	outCfgJson[xorstr("AimBot")]       = m_pSettings->m_AimBotSettings.ToJson();
	outCfgJson[xorstr("BarEsp")]       = m_pSettings->m_BarEspSettings.ToJson();
	outCfgJson[xorstr("BoxEsp")]       = m_pSettings->m_BoxEspSettings.ToJson();
	outCfgJson[xorstr("BunnyHop")]     = m_pSettings->m_BunnyHopSettings.ToJson();
	outCfgJson[xorstr("LabelEsp")]     = m_pSettings->m_LabelEspSettings.ToJson();
	outCfgJson[xorstr("Misc")]         = m_pSettings->m_MiscSettings.ToJson();
	outCfgJson[xorstr("Radar")]        = m_pSettings->m_RadarSettings.ToJson();
	outCfgJson[xorstr("SnapLinesEsp")] = m_pSettings->m_SnapLinesSettings.ToJson();
	outCfgJson[xorstr("TriggerBot")]   = m_pSettings->m_TriggerBotSettings.ToJson();

	std::string outStr = outCfgJson.dump();
	std::ofstream file(path + xorstr(".avcfg"));
	file.write((const char*)outStr.c_str(), outStr.length());
	file.close();
}

bool CConfigLoader::LoadConfigFile(std::string path)
{
	char configBuffer[2048] = { 0 };
	std::ifstream file(path + xorstr(".avcfg"));

	if (!file.is_open())
		return false;

	file.read(configBuffer, sizeof(configBuffer));
	auto jsn = json::parse(configBuffer);

	m_pSettings->m_AimBotSettings     = AimBotSettings(jsn[xorstr("AimBot")].get<json>());
	m_pSettings->m_BarEspSettings     = BarEspSettings(jsn[xorstr("BarEsp")].get<json>());
	m_pSettings->m_BoxEspSettings     = BoxEspSettings(jsn[xorstr("BoxEsp")].get<json>());
	m_pSettings->m_BunnyHopSettings   = CBunnyHopSettings(jsn[xorstr("BunnyHop")].get<json>());
	m_pSettings->m_LabelEspSettings   = CLabelEspSettings(jsn[xorstr("LabelEsp")].get<json>());
	m_pSettings->m_MiscSettings       = MiscSettings(jsn[xorstr("Misc")].get<json>());
	m_pSettings->m_RadarSettings      = CRadarSettings(jsn[xorstr("Radar")].get<json>());
	m_pSettings->m_SnapLinesSettings  = SnapLinesSettings(jsn[xorstr("SnapLinesEsp")].get<json>());
	m_pSettings->m_TriggerBotSettings = TriggerBotSettings(jsn[xorstr("TriggerBot")].get<json>());
	
	return true;
}