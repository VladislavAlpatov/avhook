#pragma once
#include "../imgui/imgui.h"
#include <cmath>


class ImVec3 : public ImVec2
{
public:
	float z = 0;

	ImVec3(float x, float y, float z) : ImVec2(x,y)
	{
		this->z = z;
	}
	ImVec3()
	{

	};
    bool operator==(const ImVec3& src) const
    {
        return (src.x == x) && (src.y == y) && (src.z == z);
    }
    bool operator!=(const ImVec3& src) const
    {
        return (src.x != x) || (src.y != y) || (src.z != z);
    }

    ImVec3& operator+=(const ImVec3& v)
    {
        x += v.x; y += v.y; z += v.z;
        return *this;
    }
    ImVec3& operator-=(const ImVec3& v)
    {
        x -= v.x; y -= v.y; z -= v.z;
        return *this;
    }
    ImVec3& operator*=(float fl)
    {
        x *= fl;
        y *= fl;
        z *= fl;
        return *this;
    }
    ImVec3& operator*=(const ImVec3& v)
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        return *this;
    }
    ImVec3& operator/=(const ImVec3& v)
    {
        x /= v.x;
        y /= v.y;
        z /= v.z;
        return *this;
    }
    ImVec3& operator+=(float fl)
    {
        x += fl;
        y += fl;
        z += fl;
        return *this;
    }
    ImVec3& operator/=(float fl)
    {
        x /= fl;
        y /= fl;
        z /= fl;
        return *this;
    }
    ImVec3& operator-=(float fl)
    {
        x -= fl;
        y -= fl;
        z -= fl;
        return *this;
    }
    float DistTo(const ImVec3& vOther) const
    {
        ImVec3 delta;

        delta.x = x - vOther.x;
        delta.y = y - vOther.y;
        delta.z = z - vOther.z;

        return delta.Length();
    }
    ImVec3& Abs()
    {
        x = fabsf(x);
        y = fabsf(y);
        z = fabsf(z);

        return *this;
    }
    float DistToSqr(const ImVec3& vOther) const
    {
        ImVec3 delta;

        delta.x = x - vOther.x;
        delta.y = y - vOther.y;
        delta.z = z - vOther.z;

        return delta.LengthSqr();
    }
    float Dot(const ImVec3& vOther) const
    {
        return (x * vOther.x + y * vOther.y + z * vOther.z);
    }
    float Length() const
    {
        return sqrt(x * x + y * y + z * z);
    }
    float LengthSqr(void) const
    {
        return (x * x + y * y + z * z);
    }
    float Length2D() const
    {
        return sqrt(x * x + y * y);
    }

    ImVec3& operator=(const ImVec3& vOther)
    {
        x = vOther.x; y = vOther.y; z = vOther.z;
        return *this;
    }

    ImVec3 operator-(void) const
    {
        return ImVec3(-x, -y, -z);
    }
    ImVec3 operator+(const ImVec3& v) const
    {
        return ImVec3(x + v.x, y + v.y, z + v.z);
    }
    ImVec3 operator-(const ImVec3& v) const
    {
        return ImVec3(x - v.x, y - v.y, z - v.z);
    }
    ImVec3 operator*(float fl) const
    {
        return ImVec3(x * fl, y * fl, z * fl);
    }
    ImVec3 operator*(const ImVec3& v) const
    {
        return ImVec3(x * v.x, y * v.y, z * v.z);
    }
    ImVec3 operator/(float fl) const
    {
        return ImVec3(x / fl, y / fl, z / fl);
    }
    ImVec3 operator/(const ImVec3& v) const
    {
        return ImVec3(x / v.x, y / v.y, z / v.z);
    }
};
