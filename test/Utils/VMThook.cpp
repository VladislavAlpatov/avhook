#include "VMThook.h"

VMThook::VMThook(void* class_ptr)
{
	this->m_pVft = *reinterpret_cast<uintptr_t**>(class_ptr);
}

void VMThook::HookVirtualMethod(int vm_index, uintptr_t hook_func_ptr)
{
	m_mOriginalFunctionAddrs.emplace(vm_index, this->m_pVft[vm_index]);
	DWORD old_proc;

	VirtualProtect(&m_pVft[vm_index], sizeof(uintptr_t), PAGE_EXECUTE_READWRITE, &old_proc);
	m_pVft[vm_index] = (uintptr_t)hook_func_ptr;
	VirtualProtect(&m_pVft[vm_index], sizeof(uintptr_t), old_proc, &old_proc);
}

void VMThook::RemoveHook(int vm_index)
{
	DWORD old_proc;

	VirtualProtect(&m_pVft[vm_index], sizeof(uintptr_t), PAGE_EXECUTE_READWRITE, &old_proc);
	m_pVft[vm_index] = (uintptr_t)m_mOriginalFunctionAddrs.at(vm_index);
	VirtualProtect(&m_pVft[vm_index], sizeof(uintptr_t), old_proc, &old_proc);

	m_mOriginalFunctionAddrs.erase(vm_index);
}

unsigned int VMThook::GetOriginalVMptr(int vm_index)
{
	return this->m_mOriginalFunctionAddrs.at(vm_index);
}