#pragma once
#include "CBaseWindow.h"
#include "../Settings.h"

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

			// Remove window bg color for a while and them restore it to make radar transparent.
			style.Colors[ImGuiCol_WindowBg].w = 0.f;
			Render();
			style.Colors[ImGuiCol_WindowBg].w = windowBgColorBackUp;
		}

	private:
		Settings::CRadarSettings* m_pRadarSettings;
		virtual void Render();
		void UseGameRadar() const;
		void RenderCustomRadar();

		virtual void KeepWindowInSreenArea();
		ImVec2 WorldToRadar(const ImVec3& EntityOrigin, const ImVec3& LocalPlayerOrigin, const ImVec3& LocalPlayerViewAngles, int width, float scale);
	};
}