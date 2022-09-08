#pragma once
#include "CBaseWindow.h"
#include "../Settings.h"

namespace UI
{
	class CRadarWindow final : public IBaseDrawObject
	{
	public:
		CRadarWindow(Settings::CRadarSettings* settings)
		{
			m_pRadarSettings = settings;
		}
		void Show() override
		{
			if (!m_pRadarSettings->m_bActive)
				return;

			ImGuiStyle& style = ImGui::GetStyle();

			const float windowBgColorBackUp = style.Colors[ImGuiCol_WindowBg].w;

			// Remove window bg color for a while and them restore it to make radar transparent.
			style.Colors[ImGuiCol_WindowBg].w = 0.f;
			Render();
			style.Colors[ImGuiCol_WindowBg].w = windowBgColorBackUp;
		}

	private:
		Settings::CRadarSettings* m_pRadarSettings;
		void Render() override;
		void UseGameRadar() const;
		void RenderCustomRadar();

		void KeepWindowInScreenArea() override;
		ImVec2 WorldToRadar(const ImVec3& EntityOrigin, const ImVec3& LocalPlayerOrigin, const ImVec3& LocalPlayerViewAngles, int width, float scale);
	};
}