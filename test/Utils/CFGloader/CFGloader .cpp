#include "CFGloader.h"


void CConfigLoader::DumpConfigFile(std::string path)
{
	json outCfgJson;
	outCfgJson[xorstr("AimBot")]       = m_pSettings.m_AimBotSettings.ToJson();
	outCfgJson[xorstr("BarEsp")]       = m_pSettings.m_BarEspSettings.ToJson();
	outCfgJson[xorstr("BoxEsp")]       = m_pSettings.m_BoxEspSettings.ToJson();
	outCfgJson[xorstr("BunnyHop")]     = m_pSettings.m_BunnyHopSettings.ToJson();
	outCfgJson[xorstr("LabelEsp")]     = m_pSettings.m_LabelEspSettings.ToJson();
	outCfgJson[xorstr("Misc")]         = m_pSettings.m_MiscSettings.ToJson();
	outCfgJson[xorstr("Radar")]        = m_pSettings.m_RadarSettings.ToJson();
	outCfgJson[xorstr("SnapLinesEsp")] = m_pSettings.m_SnapLinesSettings.ToJson();
	outCfgJson[xorstr("TriggerBot")]   = m_pSettings.m_TriggerBotSettings.ToJson();

	std::string outStr = outCfgJson.dump();
	std::ofstream file(path + xorstr(".avcfg"));
	file.write((const char*)outStr.c_str(), outStr.length());
	file.close();
}

bool CConfigLoader::LoadConfigFile(std::string path)
{
	return false;
}