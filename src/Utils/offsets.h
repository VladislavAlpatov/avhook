#pragma once
#include <Windows.h>
#include "xorstr.h"


#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;}

#define WINDOW_NAME xorstr("Counter-Strike: Global Offensive - Direct3D 9")

namespace netvars {
	constexpr ::std::ptrdiff_t m_ArmorValue = 0x117CC;
	constexpr ::std::ptrdiff_t m_aimPunchAngle = 0x303C;
	constexpr ::std::ptrdiff_t m_bSpotted = 0x93D;
	constexpr ::std::ptrdiff_t m_dwBoneMatrix = 0x26A8;
	constexpr ::std::ptrdiff_t m_fFlags = 0x104;
	constexpr ::std::ptrdiff_t m_iCrosshairId = 0x11838;
	constexpr ::std::ptrdiff_t m_iDefaultFOV = 0x333C;
	constexpr ::std::ptrdiff_t m_iGlowIndex = 0x10488;
	constexpr ::std::ptrdiff_t m_iHealth = 0x100;
	constexpr ::std::ptrdiff_t m_iTeamNum = 0xF4;
	constexpr ::std::ptrdiff_t m_vecOrigin = 0x138;
	constexpr ::std::ptrdiff_t m_vecVelocity = 0x114;
	constexpr ::std::ptrdiff_t m_vecViewOffset = 0x108;
} // namespace netvars
namespace signatures
{
	constexpr ::std::ptrdiff_t m_bDormant = 0xED;
} // namespace signatures