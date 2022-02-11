#include "CustomDirectX9Device.h"


ImVec2 CustomDirect3D9Device::GetWindowSize()
{
	D3DVIEWPORT9 view_port;
	this->GetViewport(&view_port);

	return ImVec2(view_port.Width, view_port.Height);
}