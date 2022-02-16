#pragma once
#include <Windows.h>
#include <any>
#include <map>


class VMThook
{
public:
	VMThook(void* class_ptr);
	VMThook() {};
	void         HookVirtualMethod(int vm_index, uintptr_t hook_func_ptr);
	void         RemoveHook(int vm_index);
	uintptr_t GetOriginalVMptr(int vm_index);

private:
	uintptr_t* m_pVft;
	std::map<unsigned int, uintptr_t> m_mOriginalFunctionAddrs;
};