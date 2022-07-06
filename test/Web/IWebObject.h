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

		bool SetValueIfFiledExistInJson(const nlohmann::json& jsn, const char* filedName, ImColor* var)
		{
			if (jsn.contains(filedName))
			{
				*var = ImportImColorFromJson(jsn[filedName].get<nlohmann::json>());
				return true;
			}
			return false;
		}

		template<typename T>
		bool SetValueIfFiledExistInJson(const nlohmann::json& jsn, const char* filedName, T* var)
		{
			if (jsn.contains(filedName))
			{
				*var = jsn[filedName].get<T>();
				return true;
			}
			return false;
		}
	};
}