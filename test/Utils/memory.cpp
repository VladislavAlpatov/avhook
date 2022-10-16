#include "memory.h"
#include "xorstr.h"
#include "Marker.h"
#include <vector>

BYTE GetBit(char chr)
{
	chr = tolower(chr);

	if ('a' <= chr and chr <= 'z')
		return chr - 'a' + 10;
	return chr - '0';

}
std::vector<BYTE> GetSignatureBytes(const char* str)
{
	std::vector<BYTE> bytes;
	const auto length = strlen(str);

	for (size_t i = 0; i < length;)
	{
		if (str[i] == ' ')
		{
			i += 1;
			continue;
		}
		if (str[i] == '?')
		{
			bytes.push_back('\?');
			i+1 < length and str[i+1] == '?' ? i += 2 : i++;
			continue;
		}
		bytes.push_back(GetBit(str[i]) * 16 + GetBit(str[i + 1]));
		i += 2;
	}

	return bytes;
}

uintptr_t Memory::FindPattern(const char* moduleName, const char* signature)
{
	POLY_MARKER;

	const auto base = (uintptr_t)GetModuleHandleA(moduleName);

	const auto imageNTHeaders = (PIMAGE_NT_HEADERS)(base + ((PIMAGE_DOS_HEADER)base)->e_lfanew);


	POLY_MARKER;


	const auto pattern = GetSignatureBytes(signature);

	const auto start    = imageNTHeaders->OptionalHeader.BaseOfCode;
	const auto scanSize = imageNTHeaders->OptionalHeader.SizeOfCode;

	for (uintptr_t i = start; i < scanSize - pattern.size(); i++)
	{
		bool found = true;

		for (uintptr_t j = 0; j < pattern.size(); j++)
		{
			found = pattern[j] == '\?' or pattern[j] == *(BYTE*)(base + i + j);
			if (not found)
				break;
		}
		if (found)
			return base + i;
	}

	return NULL;
}