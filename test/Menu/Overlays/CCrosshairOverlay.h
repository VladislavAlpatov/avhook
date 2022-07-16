#pragma once
#include "../IBaseDrawObject.h"
#include "../../imgui/imgui.h"
class CCrosshairOverlay : public UI::IBaseDrawObject
{
public:	
	void Render() override;
};

