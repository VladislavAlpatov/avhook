#pragma once
#include "memory.h"
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <Psapi.h>
#include "xorstr.h"
#include "Marker.h"


MODULEINFO GetModuleInfo(const char* szModule)
{
	MODULEINFO modinfo = { 0 };
	HMODULE hModule = GetModuleHandleA(szModule);

	if (hModule == NULL)
		return modinfo;

	GetModuleInformation(GetCurrentProcess(), hModule, &modinfo, sizeof(MODULEINFO));
	return modinfo;
}

UINT StrHexToByte(const std::string& str)
{
	UINT iOutNumber;
	std::stringstream ss;
	ss << std::hex << str;
	ss >> iOutNumber;


	return iOutNumber;
}

std::vector<BYTE> GetSignatureBytes(const std::string& str)
{
	POLY_MARKER;

	std::vector<std::string> strs;
	std::vector<BYTE> bytes;
	boost::split(strs, str, boost::is_any_of(" "));

	for (auto& strHex : strs)
	{
		if (strHex == xorstr("??") or strHex == xorstr("?"))
		{
			bytes.push_back('\?');
			continue;
		}

		bytes.push_back(StrHexToByte(strHex));

	}

	return bytes;
}

uintptr_t Memory::FindPattern(const char* moduleName, const char* signature)
{
	POLY_MARKER;

	MODULEINFO mInfo = GetModuleInfo(moduleName);
	uintptr_t base = (uintptr_t)mInfo.lpBaseOfDll;

	POLY_MARKER;

	uintptr_t size = (uintptr_t)mInfo.SizeOfImage;

	auto pattern = GetSignatureBytes(signature);

	for (uintptr_t i = 0; i < size - pattern.size(); i++)
	{
		bool found = true;
		for (uintptr_t j = 0; j < pattern.size(); j++)
		{
			found &= pattern[j] == '\?' or pattern[j] == *(BYTE*)(base + i + j);
			if (not found)
				break;
		}
		if (found)
			return base + i;
	}

	return NULL;
}