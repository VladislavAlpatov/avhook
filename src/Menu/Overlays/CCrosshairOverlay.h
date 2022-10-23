/*
 * Copyright (c) 2022.
 * Created by Alpatov Softworks with love in Russia.
 */

#pragma once
#include "../IBaseDrawObject.h"
#include "../../imgui/imgui.h"
class CCrosshairOverlay final : public UI::IBaseDrawObject
{
public:	
	void Render() override;
private:
	void DrawCrosshair() const;
	void DrawHealthBar(const ImVec2& vecDrawPos, float fHealthRatio, float thickness, float fHight) const;
	void DrawSpeedBar(const ImVec2& vecDrawPos, float fSpeedPerBar, float thickness, float fHeight) const;
};

