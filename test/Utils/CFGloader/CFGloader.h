#pragma once
#include "../../Menu/Settings.h"

class CConfigLoader
{
public:
	CConfigLoader(const char* name, Settings::CAllSettings* settings)
	{

		strcpy_s(m_sName, name);

		m_pSettings = settings;
	}

	char m_sName[32];
	Settings::CAllSettings* m_pSettings;

	void DumpConfigFile(std::string path);
	bool LoadConfigFile(std::string path);
};