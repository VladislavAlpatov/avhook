#define _USE_MATH_DEFINES

#pragma once
#include "Math.h"
#include <cmath>


float Utils::RadiansToDegrees(const float rads)
{
	return rads *  180 / M_PI;
}

float Utils::DegreesToRadians(const float degrees)
{
	return degrees * M_PI / 180;
}
ImVec3 Utils::NormalizeViewAngles(ImVec3 vecViewAngle)
{
	if (vecViewAngle.x > 180)
		vecViewAngle.x -= 360.0f;

	if (vecViewAngle.x < 180)
		vecViewAngle.x += 360.0f;

	if (vecViewAngle.y > 180)
		vecViewAngle.y -= 360.0f;

	if (vecViewAngle.y < 180)
		vecViewAngle.y += 360.0f;

	return vecViewAngle;
}
ImVec3 Utils::ClampViewAngles(ImVec3 vecViewAngles)
{
	if (vecViewAngles.x > 89.0f && vecViewAngles.x <= 180.0f)
		vecViewAngles.x = 89.0f;

	if (vecViewAngles.x > 180.0f)
		vecViewAngles.x = vecViewAngles.x - 360.0f;

	if (vecViewAngles.x < -89.0f)
		vecViewAngles.x = -89.0f;

	if (vecViewAngles.y > 180.0f)
		vecViewAngles.y = vecViewAngles.y - 360.0f;

	if (vecViewAngles.y < -180.0f)
		vecViewAngles.y = vecViewAngles.y + 360.0f;

	return vecViewAngles;
}

float Utils::HamToMet(float hamunit)
{
	return hamunit * 2.54f / 100.f;
}
