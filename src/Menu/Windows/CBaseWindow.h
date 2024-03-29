#pragma once
#include "../IBaseDrawObject.h"
#include "../../imgui/imgui.h"
#include <string>
#include <d3d9.h>
#include <memory>


namespace UI
{
	class CBaseWindow : public IBaseDrawObject
	{
		friend class COverlay;

	public:

		CBaseWindow(LPDIRECT3DDEVICE9 pDevice);
		CBaseWindow() = default;
		virtual ~CBaseWindow() = default;
		virtual std::string GetAlias() const;
		void Toggle();
		void SetShowState(const bool isShow) { m_bIsShow = isShow; }
	protected:
		void Show() override;
		bool m_bIsShow = false;
		// Show will be executed even if m_bIsShow is equal to false
		bool m_bForceShow = false;

		LPDIRECT3DDEVICE9 m_pDevice = nullptr;

		// Global style for all windows
		const int m_iImGuiStyle = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;
		// Keep Window from moving into out of screen
		void KeepWindowInScreenArea() override;

		void DrawIconAndTittle(const char* tittle) const;
		void DrawCloseWindowButton();

		// Execute code when user open the window
		virtual void OnClose() {}

		// Execute code while window is opening
		virtual void OnOpen() {}

		PDIRECT3DTEXTURE9 m_pTextureIcon = nullptr;

		void DrawImageWithBorder(ImTextureID textureID, const ImVec2& size);
		void DrawTextCentered(const char* text);
		void DrawInputTextWithTextOnBackGround(const char* label, const char* backGroundLabel, char* text, size_t bufferSize, ImGuiInputTextFlags flags = 0);
		void DrawInputIntWithTextOnBackGroundEx(const char* label, const char* backGroundLabel, int* pVal, size_t bufferSize, const ImColor& bgLabelCol, ImGuiInputTextFlags flags = 0);
		void DrawInputTextWithTextOnBackGroundEx(const char* label, const char* backGroundLabel, char* text, size_t bufferSize, const ImColor& bgLabelCol, ImGuiInputTextFlags flags = 0);
		void DrawMultiLineInputTextWithTextOnBackGround(const char* label, const char* backGroundLabel, char* text, size_t bufferSize, ImGuiInputTextFlags flags = 0);
		void DrawToolTip(const char* text);

		std::unique_ptr<ImFont> m_pFontSmall;
		std::unique_ptr<ImFont> m_pFontSmallBold;
		std::unique_ptr<ImFont> m_pFontMedium;
		std::unique_ptr<ImFont> m_pFontMediumBold;

	};
}