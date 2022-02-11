#pragma once

#include <d3d9.h>
#include <d3dx9core.h>

#include "../imgui/imgui.h"


class CustomDirect3D9Device : public IDirect3DDevice9
{
public:
	ImVec2 GetWindowSize();
};