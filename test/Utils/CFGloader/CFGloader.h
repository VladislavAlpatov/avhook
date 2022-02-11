#pragma once
#include "../../Menu/Settings.h"
#include <fstream>
#include <nlohmann/json.hpp>
class Config
{
public:
	Config() {};
	Config(const char* name, SAllSettings* settings)
	{

		strcpy_s(m_sName, name);

		m_pSettings = *settings;
	}

	char m_sName[32];
	SAllSettings m_pSettings;

	void DumpConfigFile(std::string path)
	{
		json outCfgJson;
		outCfgJson["AimBot"] = m_pSettings.m_AimBotSettings.ToJson();
		outCfgJson["BarEsp"] = m_pSettings.m_BarEspSettings.ToJson();
		outCfgJson["BoxEsp"] = m_pSettings.m_BoxEspSettings.ToJson();
		outCfgJson["BunnyHop"] = m_pSettings.m_BunnyHopSettings.ToJson();
		outCfgJson["LabelEsp"] = m_pSettings.m_LabelEspSettings.ToJson();
		outCfgJson["Misc"] = m_pSettings.m_MiscSettings.ToJson();
		outCfgJson["Radar"] = m_pSettings.m_RadarSettings.ToJson();
		outCfgJson["SnapLinesEsp"] = m_pSettings.m_SnapLinesSettings.ToJson();
		outCfgJson["TriggerBot"] = m_pSettings.m_TriggerBotSettings.ToJson();

		std::string outStr = outCfgJson.dump();
		std::ofstream file(path + xorstr(".avcfg"));
		file.write((const char*)outStr.c_str(), outStr.length());
		file.close();
	}
	static bool LoadConfigFile(std::string path, Config* pCfg)
	{
		std::ifstream file(path + xorstr(".avcfg"), std::ios::binary);
		file.read((char*)pCfg, sizeof(Config));
		auto rslt = file.is_open();
		file.close();
		return rslt;
	}
};