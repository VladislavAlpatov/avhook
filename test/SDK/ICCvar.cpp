#include "ICCvar.h"

void SSDK::ICCvar::ConsolePrint(const ImColor& col, const char* text)
{
	typedef bool(__cdecl* tConsolePrintf)(void*, BYTE*, const char*);
	BYTE colorBytes[] = { col.Value.x * 255, col.Value.y * 255, col.Value.z * 255, col.Value.w * 255 };
	GetVirtualFunction<tConsolePrintf>(26)(this, colorBytes, text);
}
