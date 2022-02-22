#pragma once
#include "CBaseWindow.h"
#include "../../Globals/GlobalVars.h"

namespace UI
{
	class CRadarWindow : public IBaseDrawObject
	{
	public:
		CRadarWindow(Settings::CRadarSettings* settings)
		{
			m_pRadarSettings = settings;
		}
		virtual void Show()
		{
			if (!m_pRadarSettings->m_bActive)
				return;

			ImGuiStyle& style = ImGui::GetStyle();

			float windowBgColorBackUp = style.Colors[ImGuiCol_WindowBg].w;

			style.Colors[ImGuiCol_WindowBg].w = 0.f;
			Render();
			style.Colors[ImGuiCol_WindowBg].w = windowBgColorBackUp;
		}

	private:
		Settings::CRadarSettings* m_pRadarSettings;
		virtual void Render();
		virtual void KeepWindowInSreenArea();
		ImVec2 WorldToRadar(const ImVec3& EntityOrigin, const ImVec3& LocalPlayerOrigin, const ImVec3& LocalPlayerViewAngles, int width, float scale);
	};
}