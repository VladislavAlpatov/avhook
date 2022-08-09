#pragma once
#include <Windows.h>
#include "../../Menu/COverlay.h"

namespace hooks
{
	void Attach(HMODULE ihModule);
	void Detach();
}