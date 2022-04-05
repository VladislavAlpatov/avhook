#pragma once
#include <Windows.h>
#include <Psapi.h>
#include <string>
#include <vector>

struct SPattern
{
	std::vector<BYTE> data;
	std::string       mask;
};

class CMemory
{
private:
	static MODULEINFO GetModuleInfo(const char* szModule);
	static unsigned int HexdecimalStringToInt(const std::string& str);
	static SPattern ParsePattern(const std::string& str);
public:
	static void PatchBytes(BYTE* dst, BYTE* src, unsigned int size);
	// for finding a signature/pattern in memory of another process
	static uintptr_t FindPattern(const char* module, const char* signature);
};