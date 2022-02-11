#pragma once

#include <random>

#include "../../Utils/Vec3.h"


class SnowFlake
{
public:
	SnowFlake(const ImVec2& velocity, float generationWidthRange, float flakeOffest = 2.f);
	void   Update();
	void   RegenerateOrigin();
	ImVec2 GetOrigin();
private:
	ImVec2 m_vecOrigin;
	ImVec2 m_vecVelocity;
	float  m_fFlakeOffset;
	float  m_fGenerationWindthRange;
	float  RandomFloat(float minValue, float maxValue);
};