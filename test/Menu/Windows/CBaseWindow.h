#pragma once
#include "../IBaseDrawObject.h"
#include "../../imgui/imgui.h"
#include <string>
#include <d3d9.h>
/*
Use as base class for others UI windows
*/


namespace UI
{
	class CBaseWindow : public IBaseDrawObject
	{
	public:

		CBaseWindow(LPDIRECT3DDEVICE9 pDevice);
		CBaseWindow() {};
		virtual ~CBaseWindow() { };

		virtual void Show();

		virtual std::string GetAlias();
		void Toggle();
		void SetShowState(bool isShow) { m_bIsShow = isShow; };
	protected:

		bool m_bIsShow = false;
		// Show will be executed even if m_bIsShow is equal to false
		bool m_bForceShow = false;

		LPDIRECT3DDEVICE9 m_pDevice = nullptr;

		// Global style for all windows
		const int m_iImGuiStyle = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;
		// Keep Window from moving into out of screen
		virtual void KeepWindowInSreenArea();

		void DrawIconAndTittle(const char* tittle);
		void DrawCloseWindowButton();

		// Execute code when user open the window
		virtual void OnClose() {};

		// Execute code while window is opening
		virtual void OnOpen() {};

		PDIRECT3DTEXTURE9 m_pTextureIcon = nullptr;

		void DrawImageWithBorder(ImTextureID textureID, const ImVec2& size);
		void DrawTextCentered(const char* text);
		void DrawInputTextWithTextOnBackGround(const char* label, const char* backGroundLabel, char* text, size_t bufferSize, ImGuiInputTextFlags flags = 0);
		void DrawInputIntWithTextOnBackGroundEx(const char* label, const char* backGroundLabel, int* pVal, size_t bufferSize, const ImColor& bgLabelCol, ImGuiInputTextFlags flags = 0);
		void DrawInputTextWithTextOnBackGroundEx(const char* label, const char* backGroundLabel, char* text, size_t bufferSize, const ImColor& bgLabelCol, ImGuiInputTextFlags flags = 0);
		void DrawMultiLineInputTextWithTextOnBackGround(const char* label, const char* backGroundLabel, char* text, size_t bufferSize, ImGuiInputTextFlags flags = 0);
		void DrawToolTip(const char* text);

		ImFont* m_pFontSmall      = nullptr;
		ImFont* m_pFontSmallBold  = nullptr;
		ImFont* m_pFontMedium     = nullptr;
		ImFont* m_pFontMediumBold = nullptr;

	};
}