#pragma once
#include "CBaseEntity.h"
#include  "../Utils/Math/matrix.h"

namespace SSDK
{

	namespace ClientBase
	{
		matrix GetViewMatrix();
		CBaseEntity* GetLocalPlayer();
	}
}