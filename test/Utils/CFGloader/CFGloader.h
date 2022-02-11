#pragma once
#include "../../Menu/Settings.h"
#include <fstream>

class Config
{
public:
	Config() {};
	Config(const char* name, SAllSettings* settings)
	{

		strcpy_s(m_sName, name);

		m_Settings = *settings;
	}

	char m_sName[32];
	SAllSettings m_Settings;

	void DumpConfigFile(std::string path)
	{
		std::ofstream file(path + xorstr(".avcfg"), std::ios::binary);
		file.write((const char*)this, sizeof(Config));
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