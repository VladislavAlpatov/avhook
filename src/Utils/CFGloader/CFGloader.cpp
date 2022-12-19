#pragma once
#include "CFGloader.h"
#include <fstream>
#include "nlohmann/json.hpp"
#include <Windows.h>


void CConfigLoader::DumpConfigFile(std::string path)
{
    path+=".avcfg";
	std::string outStr = m_pSettings->ToJson().dump();
	std::ofstream file(path);
	file.write((const char*)outStr.c_str(), outStr.length());
	file.close();
}

bool CConfigLoader::LoadConfigFile(std::string path)
{

    auto hFile = CreateFile((path+xorstr(".avcfg")).c_str(), GENERIC_WRITE | GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    const auto fileSize = GetFileSize(hFile, nullptr);

	char* configBuffer = new char[fileSize+1];
    configBuffer[fileSize] = '\x0';
    ReadFile(hFile, configBuffer, fileSize, nullptr, nullptr);

	auto jsn = nlohmann::json::parse(configBuffer);
    delete[] configBuffer;

	*m_pSettings =  Settings::CAllSettings(jsn);
    CloseHandle(hFile);
	return true;
}