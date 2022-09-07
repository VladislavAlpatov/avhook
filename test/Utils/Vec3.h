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
    ImVec3() : ImVec2()
	{
        z = 0.f;
	};
    bool operator==(const ImVec3& src) const;
    bool operator!=(const ImVec3& src) const;

    ImVec3& operator+=(const ImVec3& v);
    ImVec3& operator-=(const ImVec3& v);
    ImVec3& operator*=(float fl);
    ImVec3& operator*=(const ImVec3& v);
    ImVec3& operator/=(const ImVec3& v);
    ImVec3& operator+=(float fl);
    ImVec3& operator/=(float fl);
    ImVec3& operator-=(float fl);

    float DistTo(const ImVec3& vOther) const;
    ImVec3& Abs();
    float DistToSqr(const ImVec3& vOther) const;
    float Dot(const ImVec3& vOther) const;
    float Length() const;
    float LengthSqr(void) const;
    float Length2D() const;

    ImVec3& operator=(const ImVec3& vOther);

    ImVec3 operator-(void) const;
    ImVec3 operator+(const ImVec3& v) const;
    ImVec3 operator-(const ImVec3& v) const;
    ImVec3 operator*(float fl) const;
    ImVec3 operator*(const ImVec3& v) const;
    ImVec3 operator/(float fl) const;
    ImVec3 operator/(const ImVec3& v) const;
    ImVec3 Transform(const ImVec3& angles, const float length) const;
    float  Sum() const;
    float  Sum2D() const;
};
