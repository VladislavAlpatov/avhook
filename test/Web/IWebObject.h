#pragma once
#include <nlohmann/json.hpp>
#include "../imgui/imgui.h"



namespace WebApi
{
	class IWebObject
	{
	public:
		virtual nlohmann::json ToJson() const = 0;

	protected:
		nlohmann::json ImColorToJsn(const ImColor& color) const;
		ImColor ImportImColorFromJson(const nlohmann::json& jsn) const;
	};
}