#pragma once
#include <Windows.h>
#include <any>
#include <map>


class VMThook
{
public:
	VMThook(void* pClassPtr);
	VMThook() {};
	void         HookVirtualMethod(int index, uintptr_t pDetour);
	void         RemoveHook(int index);
	uintptr_t GetOriginalVMptr(int index);

private:
	uintptr_t* m_pVft;
	std::map<int, uintptr_t> m_mOriginalFunctionAddrs;
};