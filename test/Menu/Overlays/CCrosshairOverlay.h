#pragma once
#include "../IBaseDrawObject.h"
#include "../../imgui/imgui.h"
class CCrosshairOverlay : public UI::IBaseDrawObject
{
public:	
	void Render() override;
private:
	void DrawCrosshair() const;
	void DrawHealthBar(const ImVec2& vecDrawPos, float fHealthRatio, float thickness, float fHight) const;
};

