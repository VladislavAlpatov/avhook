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
		static nlohmann::json ImColorToJsn(const ImColor& color);
		static ImColor        ImportImColorFromJson(const nlohmann::json& jsn);

		bool SetValueIfFiledExistInJson(const nlohmann::json& jsn, const char* filedName, ImColor* var) const
		{
			if (jsn.contains(filedName))
			{
				*var = ImportImColorFromJson(jsn[filedName].get<nlohmann::json>());
				return true;
			}
			return false;
		}

		template<typename T>
		static bool SetValueIfFiledExistInJson(const nlohmann::json& jsn, const char* filedName, T* var)
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