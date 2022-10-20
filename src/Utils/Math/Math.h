#pragma once
#include "../Vec3.h"

namespace Utils
{
	float RadToDeg(const float rads);
	float DegToRad(const float degrees);
	ImVec3 NormalizeViewAngles(ImVec3 vecViewAngle);
	ImVec3 ClampViewAngles(ImVec3 vecViewAngles);
	float  HamToMet(float  hamunit);
}