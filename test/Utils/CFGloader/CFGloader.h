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

		m_pSettings = *settings;
	}

	char m_sName[32];
	SAllSettings m_pSettings;

	void DumpConfigFile(std::string path);
	bool LoadConfigFile(std::string path);
};