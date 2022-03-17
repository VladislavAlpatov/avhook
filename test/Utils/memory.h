#pragma once
#include <Windows.h>
#include <Psapi.h>
#include <vector>

class CMemory
{
private:
	static MODULEINFO GetModuleInfo(const char* szModule);
public:
	static void PatchBytes(BYTE* dst, BYTE* src, unsigned int size);

	// for finding a signature/pattern in memory of another process
	static std::vector<DWORD> FindPattern(const char* module, const char* pattern, const  char* mask, bool exitOnFirstMatch = true);
};