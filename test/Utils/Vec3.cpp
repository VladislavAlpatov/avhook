#define _USE_MATH_DEFINES

#include "Vec3.h"
#include <cmath>



bool ImVec3::operator==(const ImVec3& src) const
{
    return (src.x == x) and (src.y == y) and (src.z == z);
}

bool ImVec3::operator!=(const ImVec3& src) const
{
    return (src.x != x) or (src.y != y) or (src.z != z);
}

ImVec3& ImVec3::operator+=(const ImVec3& v)
{
    x += v.x;
    y += v.y;
    z += v.z;

    return *this;
}

ImVec3& ImVec3::operator-=(const ImVec3& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;

    return *this;
}

ImVec3& ImVec3::operator*=(const float fl)
{
    x *= fl;
    y *= fl;
    z *= fl;

    return *this;
}

ImVec3& ImVec3::operator*=(const ImVec3& v)
{
    x *= v.x;
    y *= v.y;
    z *= v.z;

    return *this;
}

ImVec3& ImVec3::operator/=(const ImVec3& v)
{
    x /= v.x;
    y /= v.y;
    z /= v.z;

    return *this;
}

ImVec3& ImVec3::operator+=(const float fl)
{
    x += fl;
    y += fl;
    z += fl;

    return *this;
}

ImVec3& ImVec3::operator/=(const float fl)
{
    x /= fl;
    y /= fl;
    z /= fl;

    return *this;
}

ImVec3& ImVec3::operator-=(const float fl)
{
    x -= fl;
    y -= fl;
    z -= fl;

    return *this;
}

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

ImVec3& ImVec3::operator=(const ImVec3& vOther)
{
    x = vOther.x;
    y = vOther.y;
    z = vOther.z;

    return *this;
}

ImVec3 ImVec3::operator-(void) const
{
    return {-x, -y, -z};
}

ImVec3 ImVec3::operator+(const ImVec3& v) const
{
    return {x + v.x, y + v.y, z + v.z};
}

ImVec3 ImVec3::operator-(const ImVec3& v) const
{
    return {x - v.x, y - v.y, z - v.z};
}

ImVec3 ImVec3::operator*(float fl) const
{
    return {x * fl, y * fl, z * fl};
}

ImVec3 ImVec3::operator*(const ImVec3& v) const
{
    return {x * v.x, y * v.y, z * v.z};
}

ImVec3 ImVec3::operator/(float fl) const
{
    return {x / fl, y / fl, z / fl};
}

ImVec3 ImVec3::operator/(const ImVec3& v) const
{
    return {x / v.x, y / v.y, z / v.z};
}

ImVec3 ImVec3::Transform(const ImVec3& angles, const float length) const
{
    ImVec3 trasnformedVec;
    trasnformedVec.x = x + (cosf(angles.y * (M_PI / 180.f)) * length);
    trasnformedVec.y = y + (sinf(angles.y * (M_PI / 180.f)) * length);
    trasnformedVec.z = z - (tanf(angles.x * (M_PI / 180.f)) * length);

    return trasnformedVec;
}

float ImVec3::Sum() const
{
    return x + y + z;
}

float ImVec3::Sum2D() const
{
    return x + y;
}
