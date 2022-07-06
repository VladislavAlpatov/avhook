#include "IEngineTrace.h"

void SSDK::Ray_t::Init(ImVec3 const& start, ImVec3 const& end)
{
    m_Delta = end - start;

    m_IsSwept = (m_Delta.LengthSqr() != 0);

    m_Extents.Init();

    m_pWorldAxisTransform = NULL;
    m_IsRay = true;

    // Offset m_Start to be in the center of the box...
    m_StartOffset.Init();
    m_Start = start;
}

void SSDK::Ray_t::Init(ImVec3 const& start, ImVec3 const& end, ImVec3 const& mins, ImVec3 const& maxs)
{
    m_Delta = end - start;

    m_pWorldAxisTransform = NULL;
    m_IsSwept = (m_Delta.LengthSqr() != 0);

    m_Extents = maxs - mins;
    m_Extents *= 0.5f;
    m_IsRay = (m_Extents.LengthSqr() < 1e-6);

    // Offset m_Start to be in the center of the box...
    m_StartOffset = maxs + mins;
    m_StartOffset *= 0.5f;
    m_Start = start + m_StartOffset;
    m_StartOffset *= -1.0f;
}

ImVec3 SSDK::Ray_t::InvDelta() const
{
    ImVec3 vecInvDelta;
    for (int iAxis = 0; iAxis < 3; ++iAxis) {
        if (m_Delta[iAxis] != 0.0f) {
            vecInvDelta[iAxis] = 1.0f / m_Delta[iAxis];
        }
        else {
            vecInvDelta[iAxis] = FLT_MAX;
        }
    }
    return vecInvDelta;
}
