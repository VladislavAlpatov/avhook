#pragma once
#include "../imgui/imgui.h"


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
    float DistTo(const ImVec3& vOther) const;
    ImVec3& Abs();
    float DistToSqr(const ImVec3& vOther) const;
    float Dot(const ImVec3& vOther) const;
    float Length() const;
    float LengthSqr(void) const;
    float Length2D() const;

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
    ImVec3 Transform(const ImVec3& agles, const float legth) const;
};
