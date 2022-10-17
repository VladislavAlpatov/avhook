#pragma once
#include "IWebObject.h"
#include "../Utils/marker.h"
#include "../Utils/xorstr.h"

nlohmann::json WebApi::IWebObject::ImColorToJsn(const ImColor& color)
{

	nlohmann::json jsn;
	POLY_MARKER;
	jsn[xorstr("R")] = color.Value.x;
	jsn[xorstr("G")] = color.Value.y;
	jsn[xorstr("B")] = color.Value.z;
	jsn[xorstr("A")] = color.Value.w;

	return jsn;
}

ImColor WebApi::IWebObject::ImportImColorFromJson(const nlohmann::json& jsn)
{
	POLY_MARKER;
	return {
		jsn[xorstr("R")].get<float>(),
		jsn[xorstr("G")].get<float>(),
		jsn[xorstr("B")].get<float>(),
		jsn[xorstr("A")].get<float>()
	};
}
