#pragma once
#include <Windows.h>


template <typename T>
T* GetInterface(const char* dllname, const char* interfacename)
{
	typedef void* (__cdecl* tCreateInterface)(const char* name, int* returncode);
	tCreateInterface CreateInterFace = reinterpret_cast<tCreateInterface>(GetProcAddress(GetModuleHandle(dllname), xorstr("CreateInterface")));

	int returnCode = 0;

	return reinterpret_cast<T*>(CreateInterFace(interfacename, &returnCode));

}
