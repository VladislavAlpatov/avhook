#pragma once
#include "IBaseInterface.h"
#include "../Utils/Vec3.h"
#include <cstdint>


#define DECL_ALIGN(x) __declspec(align(x))
#define ALIGN16 DECL_ALIGN(16)
#define ALIGN16_POST DECL_ALIGN(16)

#define	CONTENTS_SOLID			0x1		// an eye is never valid in a solid
#define	CONTENTS_WINDOW			0x2		// translucent, but not watery (glass)
#define	CONTENTS_GRATE			0x8		// alpha-tested "grate" textures.  Bullets/sight pass through, but solids don't
#define CONTENTS_MOVEABLE		0x4000
#define	CONTENTS_MONSTER		0x2000000
#define	CONTENTS_MONSTERCLIP	0x20000
#define	CONTENTS_DEBRIS			0x4000000
#define CONTENTS_HITBOX			0x40000000

#define MASK_NPCWORLDSTATIC	    ( CONTENTS_SOLID | CONTENTS_WINDOW | CONTENTS_MONSTERCLIP | CONTENTS_GRATE )
#define STANDARD_TRACE_MASK     ( MASK_NPCWORLDSTATIC | CONTENTS_MOVEABLE | CONTENTS_MONSTER | CONTENTS_DEBRIS | CONTENTS_HITBOX )
#define   MASK_SHOT                     (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)

#define   DISPSURF_FLAG_SURFACE           (1<<0)
#define   DISPSURF_FLAG_WALKABLE          (1<<1)
#define   DISPSURF_FLAG_BUILDABLE         (1<<2)
#define   DISPSURF_FLAG_SURFPROP1         (1<<3)
#define   DISPSURF_FLAG_SURFPROP2         (1<<4)

namespace SSDK
{
    class ALIGN16 VectorAligned : public ImVec3
    {
    public:
        VectorAligned() {};

        void Init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f)
        {
            x = ix; y = iy; z = iz;
        }

        explicit VectorAligned(const ImVec3& vOther)
        {
            Init(vOther.x, vOther.y, vOther.z);
        }

        VectorAligned& operator=(const ImVec3& vOther)
        {
            Init(vOther.x, vOther.y, vOther.z);
            return *this;
        }

        float w;	// this space is used anyway
    } ALIGN16_POST;

    struct cplane_t
    {
        ImVec3 normal;
        float dist;
        uint8_t type;   // for fast side tests
        uint8_t signbits;  // signx + (signy<<1) + (signz<<1)
        uint8_t pad[2];
    };

    struct surface_t
    {
        char* name; //0x0000
        int16_t surface_prop; //0x0004
        uint16_t flags; //0x0006
    };

    struct Ray_t
    {
        VectorAligned  m_Start;  // starting point, centered within the extents
        VectorAligned  m_Delta;  // direction + length of the ray
        VectorAligned  m_StartOffset; // Add this to m_Start to Get the actual ray start
        VectorAligned  m_Extents;     // Describes an axis aligned box extruded along a ray
        const void* m_pWorldAxisTransform;
        bool m_IsRay;  // are the extents zero?
        bool m_IsSwept;     // is delta != 0?

        Ray_t() : m_pWorldAxisTransform(NULL) {}

        void Init(ImVec3 const& start, ImVec3 const& end);

        void Init(ImVec3 const& start, ImVec3 const& end, ImVec3 const& mins, ImVec3 const& maxs);

        ImVec3 InvDelta() const;
    };


    enum class TraceType
    {
        TRACE_EVERYTHING = 0,
        TRACE_WORLD_ONLY,
        TRACE_ENTITIES_ONLY,
        TRACE_EVERYTHING_FILTER_PROPS,
    };

    class ITraceFilter
    {
    public:
        virtual bool ShouldHitEntity(void* pEntity, int contentsMask) = 0;
        virtual TraceType GetTraceType() const = 0;
    };


    // This is the one most normal traces will inherit from
    class CTraceFilter : public ITraceFilter
    {
    public:
        bool ShouldHitEntity(void* pEntityHandle, int /*contentsMask*/)
        {
            return !(pEntityHandle == m_pSkip);
        }
        virtual TraceType GetTraceType() const
        {
            return TraceType::TRACE_EVERYTHING;
        }
        void* m_pSkip;
    };

    class CBaseTrace
    {
    public:
        bool IsDispSurface(void) { return ((dispFlags & DISPSURF_FLAG_SURFACE) != 0); }
        bool IsDispSurfaceWalkable(void) { return ((dispFlags & DISPSURF_FLAG_WALKABLE) != 0); }
        bool IsDispSurfaceBuildable(void) { return ((dispFlags & DISPSURF_FLAG_BUILDABLE) != 0); }
        bool IsDispSurfaceProp1(void) { return ((dispFlags & DISPSURF_FLAG_SURFPROP1) != 0); }
        bool IsDispSurfaceProp2(void) { return ((dispFlags & DISPSURF_FLAG_SURFPROP2) != 0); }

    public:

        // these members are aligned!!
        ImVec3         startpos;            // start position
        ImVec3         endpos;              // final position
        cplane_t       plane;               // surface normal at impact

        float          fraction;            // time completed, 1.0 = didn't hit anything

        int            contents;            // contents on other side of surface hit
        unsigned short dispFlags;           // displacement flags for marking surfaces with data

        bool           allsolid;            // if true, plane is not valid
        bool           startsolid;          // if true, the initial point was in a solid area

        CBaseTrace() {}

    };

    class CGameTrace : public CBaseTrace
    {
    public:
        //bool DidHitWorld() const;
        //bool DidHitNonWorldEntity() const;
        //int GetEntityIndex() const;
        bool DidHit() const;
        bool IsVisible() const;

    public:

        float               fractionleftsolid;  // time we left a solid, only valid if we started in solid
        surface_t          surface;            // surface hit (impact surface)
        int                 hitgroup;           // 0 == generic, non-zero is specific body part
        short               physicsbone;        // physics bone hit by trace in studio
        unsigned short      worldSurfaceIndex;  // Index of the msurface2_t, if applicable
        //IClientEntity* m_pHitEntity;
        void* m_pHitEntity;
        int                 hitbox;                       // box hit by trace in studio

        CGameTrace() {}

    private:
        // No copy constructors allowed
        CGameTrace(const CGameTrace& other) :
            fractionleftsolid(other.fractionleftsolid),
            surface(other.surface),
            hitgroup(other.hitgroup),
            physicsbone(other.physicsbone),
            worldSurfaceIndex(other.worldSurfaceIndex),
            m_pHitEntity(other.m_pHitEntity),
            hitbox(other.hitbox)
        {
            startpos = other.startpos;
            endpos = other.endpos;
            plane = other.plane;
            fraction = other.fraction;
            contents = other.contents;
            dispFlags = other.dispFlags;
            allsolid = other.allsolid;
            startsolid = other.startsolid;
        }

        CGameTrace& operator=(const CGameTrace& other)
        {
            startpos = other.startpos;
            endpos = other.endpos;
            plane = other.plane;
            fraction = other.fraction;
            contents = other.contents;
            dispFlags = other.dispFlags;
            allsolid = other.allsolid;
            startsolid = other.startsolid;
            fractionleftsolid = other.fractionleftsolid;
            surface = other.surface;
            hitgroup = other.hitgroup;
            physicsbone = other.physicsbone;
            worldSurfaceIndex = other.worldSurfaceIndex;
            m_pHitEntity = other.m_pHitEntity;
            hitbox = other.hitbox;
            return *this;
        }
    };

    inline bool CGameTrace::DidHit() const
    {
        return fraction < 1 || allsolid || startsolid;
    }

    inline bool CGameTrace::IsVisible() const
    {
        return fraction > 0.97f;
    }

    class IEngineTrace : public IBaseInterface
    {
    public:
        void  TraceRay(Ray_t& ray, unsigned int fMask, CTraceFilter* pTraceFilter, CGameTrace* pTrace)
        {
            typedef void(__thiscall* tTraceRay)(void* pThis, Ray_t& ray, unsigned int fMask, CTraceFilter* pTraceFilter, CGameTrace* pTrace);
            GetVirtualFunction<tTraceRay>(5)(this, ray, fMask, pTraceFilter, pTrace);

        }

    private:

    };
}