#pragma once
#include <Windows.h>
#include "../Utils/xorstr.h"

namespace SSDK
{
	class AbstractInterface
	{
	protected:
		template<typename FuncType>
		FuncType GetVirtualFunction(unsigned int index)
		{
			uintptr_t* pVTable = *reinterpret_cast<unsigned int**>(this);
			uintptr_t function_address = pVTable[index];
			return reinterpret_cast<FuncType>(function_address);
		}

	};

	template <typename T>
	T* GetInterface(const char* dllname, const char* interfacename)
	{
		typedef void* (__cdecl* tCreateInterface)(const char* name, int* returncode);
		tCreateInterface CreateInterFace = reinterpret_cast<tCreateInterface>(GetProcAddress(GetModuleHandle(dllname), xorstr("CreateInterface")));

		int returnCode = 0;

		return reinterpret_cast<T*>(CreateInterFace(interfacename, &returnCode));

	}

}

