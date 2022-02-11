#pragma once
#include <Windows.h>
#include <Psapi.h>


class Memory
{
private:
	static MODULEINFO GetModuleInfo(const char* szModule)
	{
		MODULEINFO modinfo{ 0 };
		HMODULE hModule = GetModuleHandle(szModule);
		if (hModule == 0)
			return modinfo;
		GetModuleInformation(GetCurrentProcess(), hModule, &modinfo, sizeof(MODULEINFO));
		return modinfo;
	}
public:
	static void PatchBytes(BYTE* dst, BYTE* src, unsigned int size)
	{
		DWORD oproc;
		VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oproc);
		memcpy(dst, src, size);
		VirtualProtect(dst, size, oproc, &oproc);
	}

	// for finding a signature/pattern in memory of another process
	static DWORD FindPattern(const char* module,const char* pattern,const  char* mask)
	{
		MODULEINFO mInfo	= GetModuleInfo(module);
		DWORD base          = (DWORD)mInfo.lpBaseOfDll;
		DWORD size			= (DWORD)mInfo.SizeOfImage;
		DWORD patternLength = (DWORD)strlen(mask);

		for (DWORD i = 0; i < size - patternLength; i++)
		{
			bool found = true;
			for (DWORD j = 0; j < patternLength; j++)
			{
				found &= mask[j] == '?' || pattern[j] == *(char*)(base + i + j);
			}
			if (found)
			{
				return base + i;
			}
		}

		return NULL;
	}
};