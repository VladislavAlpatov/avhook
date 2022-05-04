#pragma once
#include "memory.h"
#include <sstream>
#include <boost/algorithm/string.hpp>
#include "xorstr.h"
#include "Marker.h"

MODULEINFO CMemory::GetModuleInfo(const char* szModule)
{
	MODULEINFO modinfo = { 0 };
	HMODULE hModule = GetModuleHandleA(szModule);
	if (hModule == NULL)
		return modinfo;

	GetModuleInformation(GetCurrentProcess(), hModule, &modinfo, sizeof(MODULEINFO));
	return modinfo;
}

unsigned int CMemory::HexdecimalStringToInt(const std::string& str)
{
	unsigned int iOutNumber;
	std::stringstream ss;
	ss << std::hex << str;
	ss >> iOutNumber;
	return iOutNumber;
}

SPattern CMemory::ParsePattern(const std::string& str)
{
	auto pattern = SPattern();
	std::vector<std::string> strs;

	boost::split(strs, str, boost::is_any_of(" "));
	
	for (auto& strHex : strs)
	{
		if (strHex == xorstr("??"))
		{
			pattern.data.push_back(NULL);
			pattern.mask += xorstr("?");
			continue;
		}

		pattern.data.push_back(HexdecimalStringToInt(strHex));
		pattern.mask += xorstr("x");

	}
	return pattern;
}

void CMemory::PatchBytes(BYTE* dst, BYTE* src, unsigned int size)
{
	DWORD oproc;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oproc);
	memcpy(dst, src, size);
	VirtualProtect(dst, size, oproc, &oproc);
}

uintptr_t CMemory::FindPattern(const char* module, const char* signature)
{
	MODULEINFO mInfo = GetModuleInfo(module);
	uintptr_t base = (uintptr_t)mInfo.lpBaseOfDll;
	uintptr_t size = (uintptr_t)mInfo.SizeOfImage;
	auto pattern = ParsePattern(signature);

	POLY_MARKER;

	for (uintptr_t i = 0; i < size - pattern.data.size(); i++)
	{
		bool found = true;
		for (uintptr_t j = 0; j < pattern.data.size(); j++)
		{
			found &= pattern.mask[j] == '?' || pattern.data[j] == *(BYTE*)(base + i + j);
		}
		if (found)
		{
			return base + i;
		}
	}

	return NULL;
}