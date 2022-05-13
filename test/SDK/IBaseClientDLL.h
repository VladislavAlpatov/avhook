#pragma once
#include "AbstractInterface.h"

namespace SSDK
{
	class IBaseClientDLL1 : public CAbstractInterface
	{
	public:
		void* GetAllClasses()
		{
			typedef void* (__thiscall* GetAllClassesT)(void*);
			return this->GetVirtualFunction<GetAllClassesT>(9)(this);
		}
		void IN_DeactivateMouse()
		{
			typedef void(__thiscall* GetAllClassesT)(void*);
			return this->GetVirtualFunction<GetAllClassesT>(15)(this);
		}
	};
}