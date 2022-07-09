#include "Vec3.h"


#define _USE_MATH_DEFINES
#include <cmath>



float ImVec3::DistTo(const ImVec3& vOther) const
{
    ImVec3 delta;

    delta.x = x - vOther.x;
    delta.y = y - vOther.y;
    delta.z = z - vOther.z;

    return delta.Length();
}

ImVec3& ImVec3::Abs()
{
    x = fabsf(x);
    y = fabsf(y);
    z = fabsf(z);

    return *this;
}

float ImVec3::DistToSqr(const ImVec3& vOther) const
{
    ImVec3 delta;

    delta.x = x - vOther.x;
    delta.y = y - vOther.y;
    delta.z = z - vOther.z;

    return delta.LengthSqr();
}

float ImVec3::Dot(const ImVec3& vOther) const
{
    return (x * vOther.x + y * vOther.y + z * vOther.z);
}

float ImVec3::Length() const
{
    return sqrt(x * x + y * y + z * z);
}

float ImVec3::LengthSqr(void) const
{
    return (x * x + y * y + z * z);
}

float ImVec3::Length2D() const
{
    return sqrt(x * x + y * y);

}

ImVec3 ImVec3::Transform(const ImVec3& agles, const float legth) const
{
    ImVec3 trasnformedVec;
    trasnformedVec.x = x + (cosf(agles.y * (M_PI / 180.f)) * legth);
    trasnformedVec.y = y + (sinf(agles.y * (M_PI / 180.f)) * legth);
    trasnformedVec.z = z - (tanf(agles.x * (M_PI / 180.f)) * legth);

    return trasnformedVec;
}
