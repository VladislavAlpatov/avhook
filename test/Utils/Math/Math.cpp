#include "Math.h"
#define _USE_MATH_DEFINES
#include <cmath>


float Utils::RadiansToDegrees(const float rads)
{
	return rads *  180 / M_PI;
}

float Utils::DergreesToRadians(const float degrees)
{
	return degrees * M_PI / 180;
}
