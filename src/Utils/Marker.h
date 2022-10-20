#pragma once

namespace Marker
{
    __forceinline void PolyMarker()
    {
#ifndef _DEBUG
        __asm
        {
            nop
            nop
            nop
            nop
            nop
            nop
            nop
            nop
            nop
            nop
            nop
            nop
            nop
            nop
            nop
            nop
            nop
            nop
            nop
            nop
            nop
            nop
            nop
            nop
            nop
            nop
            nop
            nop
            nop
            nop
            nop
            nop
        }
#endif
    }
}
#define POLY_MARKER Marker::PolyMarker();

