#pragma once
#include "CFGloader.h"
#include <fstream>
#include "nlohmann/json.hpp"

void CConfigLoader::DumpConfigFile(std::string path)
{

	std::string outStr = m_pSettings->ToJson().dump();
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

	*m_pSettings =  Settings::CAllSettings(jsn);
	
	return true;
}