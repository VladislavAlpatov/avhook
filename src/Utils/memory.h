#pragma once
#include <Windows.h>

namespace memory
{
	uintptr_t FindPattern(const char* moduleName, const char* signature);
	void Copy(PVOID dst, PVOID src, size_t len);
	void Set(PVOID dst, BYTE val, size_t len);


	class CFunctionHook
	{
	 public:
		CFunctionHook(PVOID pTarget, PVOID pDetour, size_t len);
		CFunctionHook(CFunctionHook&& other);
		CFunctionHook() = default;
		CFunctionHook& operator=(CFunctionHook&& other) noexcept;
		CFunctionHook& operator=(CFunctionHook& other);
		bool operator==(const CFunctionHook& rhs) const;
		bool operator!=(const CFunctionHook& rhs) const;
		~CFunctionHook();
		void Disable();
		const PVOID GetPointerToNewOrigin() const;
		void Enable();
	 private:
		bool m_bEnabled = false;
		size_t m_iLength = 0;
		BYTE*  m_pNewOrigin = nullptr;
		PVOID  m_pTarget = nullptr;
		PVOID  m_pDetour = nullptr;
		void SetJump(PVOID pSource, PVOID pDestination);
	};
}