#define _USE_MATH_DEFINES
#include "Math.h"
#include <cmath>
#include "../Marker.h"


float Utils::RadToDeg(const float rads)
{
	return rads *  180 / M_PI;
}

float Utils::DegToRad(const float degrees)
{
	return degrees * M_PI / 180;
}
ImVec3 Utils::NormalizeViewAngles(ImVec3 vecViewAngle)
{
	POLY_MARKER;
	if (vecViewAngle.x > 180)
		vecViewAngle.x -= 360.0f;
	POLY_MARKER;
	if (vecViewAngle.x < 180)
		vecViewAngle.x += 360.0f;
	POLY_MARKER;
	if (vecViewAngle.y > 180)
		vecViewAngle.y -= 360.0f;
	POLY_MARKER;
	if (vecViewAngle.y < 180)
		vecViewAngle.y += 360.0f;

	return vecViewAngle;
}
ImVec3 Utils::ClampViewAngles(ImVec3 vecViewAngles)
{
	POLY_MARKER;
	if (vecViewAngles.x > 89.0f and vecViewAngles.x <= 180.0f)
		vecViewAngles.x = 89.0f;
	POLY_MARKER;
	if (vecViewAngles.x > 180.0f)
		vecViewAngles.x = vecViewAngles.x - 360.0f;
	POLY_MARKER;
	if (vecViewAngles.x < -89.0f)
		vecViewAngles.x = -89.0f;

	if (vecViewAngles.y > 180.0f)
		vecViewAngles.y = vecViewAngles.y - 360.0f;

	if (vecViewAngles.y < -180.0f)
		vecViewAngles.y = vecViewAngles.y + 360.0f;
	POLY_MARKER;
	return vecViewAngles;
}

float Utils::HamToMet(float hamunit)
{
	return hamunit * 2.54f / 100.f;
}
