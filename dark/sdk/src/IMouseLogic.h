#pragma once

#include "Vector3.h"

class IMouseLogic
{
public:
	virtual ~IMouseLogic() = default;

public:
	virtual Vector3 mousePosition() = 0;

	virtual void setMousePosition(const Vector3& pos) = 0;

	virtual unsigned short hoveredMouseIndex() = 0;

	virtual char screenPointToTargetResolver(__int64 screenX, __int64 screenY, uintptr_t* outTarget1, uintptr_t* outTarget2) = 0;
};