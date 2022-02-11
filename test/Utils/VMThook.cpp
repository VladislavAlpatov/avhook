#include "VMThook.h"

VMThook::VMThook(void* class_ptr)
{
	this->vm_table = *reinterpret_cast<uintptr_t**>(class_ptr);
}

void VMThook::HookVirtualMethod(int vm_index, uintptr_t hook_func_ptr)
{
	this->original_ptrs.emplace(vm_index, this->vm_table[vm_index]);
	DWORD old_proc;

	VirtualProtect(&this->vm_table[vm_index], 4, PAGE_EXECUTE_READWRITE, &old_proc);
	this->vm_table[vm_index] = (uintptr_t)hook_func_ptr;
	VirtualProtect(&this->vm_table[vm_index], 4, old_proc, &old_proc);
}

void VMThook::RemoveHook(int vm_index)
{
	DWORD old_proc;

	VirtualProtect(&this->vm_table[vm_index], 4, PAGE_EXECUTE_READWRITE, &old_proc);
	this->vm_table[vm_index] = (uintptr_t)this->original_ptrs.at(vm_index);
	VirtualProtect(&this->vm_table[vm_index], 4, old_proc, &old_proc);

	this->original_ptrs.erase(vm_index);
}

unsigned int VMThook::GetOriginalVMptr(int vm_index)
{
	return this->original_ptrs.at(vm_index);
}