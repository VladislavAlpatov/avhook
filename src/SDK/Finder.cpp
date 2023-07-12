
#include "Finder.h"

#include "../Utils/memory.h"
#include "../Utils/xorstr.h"

#include <stdexcept>
#include "../Utils/Marker.h"


uintptr_t SSDK::FindCreatemove()
{
    POLY_MARKER;
    static auto addr = memory::FindPattern(xorstr("client.dll"), xorstr("55 8B EC 56 8D 75 04 8B"));

    if (!addr)
        throw std::runtime_error(xorstr("Failed to find CreateMove"));

    return addr;
}

uintptr_t SSDK::FindDrawIndexedPrimitive()
{
    POLY_MARKER;
    static auto addr = memory::FindPattern(xorstr("d3d9.dll"), xorstr("8B FF 55 8B EC 6A FF 68 ? ? ? ? 64 A1 ? ? ? ? 50 83 EC 28"));
    
    if (!addr)
        throw std::runtime_error(xorstr("Failed to find DrawIndexedPrimitive"));

    return addr;
}

uintptr_t SSDK::FindRenderGlowEffects()
{
    POLY_MARKER;
    static auto addr = memory::FindPattern(xorstr("client.dll"), xorstr("55 8B EC A1 ? ? ? ? 83 EC 18 57"));

    if (!addr)
        throw std::runtime_error(xorstr("Failed to find DrawIndexedPrimitive"));

    return addr;
}

uintptr_t SSDK::FindPresent()
{
    POLY_MARKER;
    static auto addr = memory::FindPattern(xorstr("d3d9.dll"), xorstr("?? ?? ?? ?? ?? 83 E4 F8 51 51 56 8B 75 08 8B CE F7 D9 57 1B C9 8D 46 04 23 C8 6A ?? 51 8D 4C 24 10 E8 ?? ?? ?? ?? F7 46 ?? ?? ?? ?? ?? 74 07 BF ?? ?? ?? ?? EB 17"));
    
    if (!addr)
        throw std::runtime_error(xorstr("Failed to find Present"));

    return addr;
}

BYTE* SSDK::GetForceAttack()
{
    POLY_MARKER;
    static auto addr = *(BYTE**)(memory::FindPattern(xorstr("client.dll"), xorstr("89 0D ? ? ? ? 8B 0D ? ? ? ? 8B F2 8B C1 83 CE 04")) + 2);

    if (!addr)
        throw std::runtime_error(xorstr("Failed to find ForceAttack"));

    return addr;

}

