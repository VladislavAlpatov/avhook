#pragma once
#include <d3dx9.h>

#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"
#include "../Utils/xorstr.h"
#include "../resource.h"
#include "../Utils/Marker.h"
#include "../imgui/misc/freetype/imgui_freetype.h"

class IBaseDrawObject
{
public:
	virtual void Show()   = 0;
protected:
	virtual void Render()        = 0;
	virtual void KeepWindowInSreenArea() {} ;
};