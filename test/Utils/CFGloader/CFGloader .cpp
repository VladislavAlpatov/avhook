#include "CFGloader.h"


void CConfigLoader::DumpConfigFile(std::string path)
{
	nlohmann::json outCfgJson;
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
	auto jsn = nlohmann::json::parse(configBuffer);

	m_pSettings->m_AimBotSettings     = Settings::CAimBotSettings(jsn[xorstr("AimBot")].get<nlohmann::json>());
	m_pSettings->m_BarEspSettings     = Settings::BarEspSettings(jsn[xorstr("BarEsp")].get<nlohmann::json>());
	m_pSettings->m_BoxEspSettings     = Settings::BoxEspSettings(jsn[xorstr("BoxEsp")].get<nlohmann::json>());
	m_pSettings->m_BunnyHopSettings   = Settings::CBunnyHopSettings(jsn[xorstr("BunnyHop")].get<nlohmann::json>());
	m_pSettings->m_LabelEspSettings   = Settings::CLabelEspSettings(jsn[xorstr("LabelEsp")].get<nlohmann::json>());
	m_pSettings->m_MiscSettings       = Settings::MiscSettings(jsn[xorstr("Misc")].get<nlohmann::json>());
	m_pSettings->m_RadarSettings      = Settings::CRadarSettings(jsn[xorstr("Radar")].get<nlohmann::json>());
	m_pSettings->m_SnapLinesSettings  = Settings::SnapLinesSettings(jsn[xorstr("SnapLinesEsp")].get<nlohmann::json>());
	m_pSettings->m_TriggerBotSettings = Settings::TriggerBotSettings(jsn[xorstr("TriggerBot")].get<nlohmann::json>());
	
	return true;
}