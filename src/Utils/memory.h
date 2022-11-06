#pragma once
#include <Windows.h>

namespace memory
{
	uintptr_t FindPattern(const char* moduleName, const char* signature);

}