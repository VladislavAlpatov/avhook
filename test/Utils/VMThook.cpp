#include "VMThook.h"

VMThook::VMThook(void* pClassPtr)
{
	m_pVft = *(uintptr_t**)(pClassPtr);
}

void VMThook::HookVirtualMethod(int index, uintptr_t pDetour)
{
	m_mOriginalFunctionAddrs.emplace(index, m_pVft[index]);
	DWORD oldProc;

	VirtualProtect(&m_pVft[index], sizeof(pDetour), PAGE_EXECUTE_READWRITE, &oldProc);
	m_pVft[index] = (uintptr_t)pDetour;
	VirtualProtect(&m_pVft[index], sizeof(pDetour), oldProc, &oldProc);
}

void VMThook::RemoveHook(int index)
{
	DWORD oldProc;

	VirtualProtect(&m_pVft[index], sizeof(uintptr_t), PAGE_EXECUTE_READWRITE, &oldProc);
	m_pVft[index] = (uintptr_t)m_mOriginalFunctionAddrs.at(index);
	VirtualProtect(&m_pVft[index], sizeof(uintptr_t), oldProc, &oldProc);

	m_mOriginalFunctionAddrs.erase(index);
}

uintptr_t VMThook::GetOriginalVMptr(int index)
{
	return this->m_mOriginalFunctionAddrs.at(index);
}