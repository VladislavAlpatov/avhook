#pragma once
#include <Windows.h>

namespace Memory
{
	uintptr_t FindPattern(const char* moduleName, const char* signature);
}