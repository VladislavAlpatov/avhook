#include "IGlowObjectManager.h"


SSDK::GlowObjectDefinition* SSDK::IGlowObjectManager::GetGlowObject(size_t index) const
{
	auto arr = ((GlowObjectDefinition**)this)[0];

	return &arr[index];
}

int SSDK::IGlowObjectManager::GetGlowEntitiesCount() const 
{

	return *(int*)( (uintptr_t)this+0xC );
}
