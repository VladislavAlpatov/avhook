#include "SnowFlake.h"

SnowFlake::SnowFlake(const ImVec2& velocity, float generationWidthRange, float flakeOffest)
{
    this->m_vecOrigin = ImVec2(this->RandomFloat(0, generationWidthRange), this->RandomFloat(-350, 0));
    this->m_vecVelocity = velocity;
    this->m_fFlakeOffset = flakeOffest;
    this->m_fGenerationWindthRange = generationWidthRange;
}

float SnowFlake::RandomFloat(float minValue, float maxValue)
{
    std::random_device randomDevice;
    std::mt19937 mt(randomDevice());
    std::uniform_real_distribution<> dist(minValue, maxValue);

    return (float)dist(mt);
}
void SnowFlake::Update()
{
    this->m_vecOrigin.x += m_vecVelocity.x;
    this->m_vecOrigin.y += m_vecVelocity.y;

    this->m_vecOrigin.x += RandomFloat(-m_fFlakeOffset, m_fFlakeOffset);
}
ImVec2 SnowFlake::GetOrigin()
{
    return m_vecOrigin;
}
void SnowFlake::RegenerateOrigin()
{
    this->m_vecOrigin = ImVec2(this->RandomFloat(0, this->m_fGenerationWindthRange), this->RandomFloat(-150, 0));
}