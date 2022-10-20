#pragma once
#include "../IBaseInterface.h"
#include "ConVar.h"


namespace SSDK
{
	class ICvarSystem : public SSDK::IBaseInterface
	{
	public:

		ConVar* FindVar(const char* cvarName);
	};

}

