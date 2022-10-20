#pragma once
#include "../Utils/xorstr.h"
#include <Windows.h>

namespace SSDK
{
	class IBaseInterface
	{
	protected:
		template<typename FuncType>
		FuncType GetVirtualFunction(unsigned int index) const
		{
			return reinterpret_cast<FuncType>((*(void***)this)[index]);
		}

	};
	
	template <typename T>
	T* GetInterface(const char* dllname, const char* interfacename)
	{
		typedef void* (__cdecl* tCreateInterface)(const char* name, int* returncode);
		const auto CreateInterFace = reinterpret_cast<tCreateInterface>(GetProcAddress(GetModuleHandleA(dllname), xorstr("CreateInterface")));

		int returnCode = 0;

		return static_cast<T*>(CreateInterFace(interfacename, &returnCode));
	}

}

