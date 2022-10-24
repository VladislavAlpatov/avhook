/*
 * Copyright (c) 2022.
 * Created by Alpatov Softworks with love in Russia.
 */

#include "memory.h"
#include "xorstr.h"
#include "Marker.h"
#include <vector>
#include <stdexcept>
#include <algorithm>


#define SIZE_OF_JMP 5
#define JMP_INSTRUCTION_CODE 0xE9
BYTE GetBit(char chr)
{
	POLY_MARKER;
	chr = tolower(chr);

	if ('a' <= chr and chr <= 'z')
		return chr - 'a' + 10;
	return chr - '0';

}
std::vector<BYTE> GetSignatureBytes(const char* str)
{
	POLY_MARKER;
	std::vector<BYTE> bytes;
	const auto length = strlen(str);

	for (size_t i = 0; i < length;)
	{
		POLY_MARKER;
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
		POLY_MARKER;
		bytes.push_back(GetBit(str[i]) * 16 + GetBit(str[i + 1]));
		i += 2;
	}
	POLY_MARKER;
	return bytes;
}

uintptr_t memory::FindPattern(const char* moduleName, const char* signature)
{
	POLY_MARKER;

	const auto base = (uintptr_t)GetModuleHandleA(moduleName);

	const auto imageNTHeaders = (PIMAGE_NT_HEADERS)(base + ((PIMAGE_DOS_HEADER)base)->e_lfanew);


	POLY_MARKER;


	const auto pattern = GetSignatureBytes(signature);

	// Define .code segment as scan area
	const auto start    = imageNTHeaders->OptionalHeader.BaseOfCode;
	const auto scanSize = imageNTHeaders->OptionalHeader.SizeOfCode;

	for (uintptr_t i = start; i < scanSize - pattern.size(); i++)
	{
		bool found = true;

		for (uintptr_t j = 0; j < pattern.size(); j++)
		{
			found = pattern[j] == '\?' or pattern[j] == *(BYTE*)(base + i + j);
			if (not found) break;
		}
		if (found) return base + i;
	}

	return NULL;
}

class SHookData
{
	LPVOID m_pOrigin;
	LPVOID m_pOriginal;
	size_t m_iLength;
};

void memory::CFunctionHook::SetJump(PVOID pDestination, PVOID pSource)
{
	// Allcatec data for jmp 1 byte for JMP code
	// and 5 bytes for offset
	BYTE shell[SIZE_OF_JMP];
	shell[0] = JMP_INSTRUCTION_CODE;
	// Write jmp offset
	*(int*)(shell+1) = (uintptr_t)pDestination - (uintptr_t)pSource - 5;
	memory::Copy(pSource, shell, SIZE_OF_JMP);

}
void memory::Copy(PVOID dst, PVOID src, size_t len)
{
	DWORD oldProc;
	VirtualProtect(dst, len, PAGE_EXECUTE_READWRITE, &oldProc);
	memcpy_s(dst,len, src, len);
	VirtualProtect(dst, len, oldProc, &oldProc);
}
memory::CFunctionHook::CFunctionHook(PVOID pTarget, PVOID pDetour, size_t len)
{
	m_iLength = len;
	m_pTarget = pTarget;
	m_pDetour = pDetour;

	m_pNewOrigin = new BYTE[m_iLength+SIZE_OF_JMP];
	// Copy bytes to new origin
	memory::Copy(m_pNewOrigin, m_pTarget, m_iLength);

	// Jump from new origin to hooked function
	SetJump((BYTE*)m_pTarget + m_iLength, (BYTE*)m_pNewOrigin + m_iLength);

	// Jump from function to detour
	SetJump(m_pDetour,m_pTarget);

}
memory::CFunctionHook::~CFunctionHook()
{
	if (m_bEnabled)
		Disable();
	delete m_pNewOrigin;
}
void memory::CFunctionHook::Disable()
{
	if (!m_bEnabled) return;
	memory::Copy(m_pTarget, m_pNewOrigin, m_iLength);

	m_bEnabled = !m_bEnabled;
}
void memory::CFunctionHook::Enable()
{
	if (m_bEnabled) return;

	SetJump(m_pDetour, m_pTarget);

	m_bEnabled = !m_bEnabled;
}
memory::CFunctionHook::CFunctionHook(memory::CFunctionHook&& other)
{
	m_bEnabled   = other.m_bEnabled;
	m_pTarget    = other.m_pTarget;
	m_pDetour    = other.m_pDetour;
	m_pNewOrigin = other.m_pNewOrigin;
	m_iLength    = other.m_iLength;


	// Mark other hook as "disabled"
	// and remove pointer to origin
	other.m_bEnabled = false;
	other.m_pNewOrigin = nullptr;
}
const PVOID memory::CFunctionHook::GetPointerToNewOrigin() const
{
	return m_pNewOrigin;
}
bool memory::CFunctionHook::operator==(const memory::CFunctionHook& rhs) const
{
	return m_bEnabled == rhs.m_bEnabled &&
		m_iLength == rhs.m_iLength &&
		m_pNewOrigin == rhs.m_pNewOrigin &&
		m_pTarget == rhs.m_pTarget &&
		m_pDetour == rhs.m_pDetour;
}
bool memory::CFunctionHook::operator!=(const memory::CFunctionHook& rhs) const
{
	return !(rhs == *this);
}
memory::CFunctionHook& memory::CFunctionHook::operator=(memory::CFunctionHook&& other) noexcept
{
	m_iLength  = other.m_iLength;
	m_bEnabled = other.m_bEnabled;
	m_pDetour  = other.m_pDetour;
	m_pTarget  = other.m_pTarget;

	std::swap(m_pNewOrigin, other.m_pNewOrigin);

	return *this;

}
