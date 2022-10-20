#include "IGlowObjectManager.h"
#include "../Utils/Marker.h"

SSDK::GlowObjectDefinition* SSDK::IGlowObjectManager::GetGlowObject(size_t index) const
{
	POLY_MARKER;
	const auto arr = ((GlowObjectDefinition**)this)[0];

	return &arr[index];
}

int SSDK::IGlowObjectManager::GetGlowEntitiesCount() const 
{
	POLY_MARKER;
	return *(int*)( (uintptr_t)this+0xC );
}
