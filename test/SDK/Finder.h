//========= Copyright Alpatov Softworks, All rights reserved. ============//
//
// Finds game functions and stucts by using patter scan
//
//===============================================================================




#pragma once
#include <Windows.h>


namespace SSDK
{
	uintptr_t FindCreatemove();
	uintptr_t FindDrawIndexedPrimitive();
	uintptr_t FindRenderGlowEffects();
	uintptr_t FindPresent();
}