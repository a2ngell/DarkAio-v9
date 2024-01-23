#pragma once

#include <vector>

#include "Vector3.h"

class IPathController
{
public:
	virtual ~IPathController() = default;

public:
	virtual uintptr_t address() = 0;

	virtual Vector3 clickedPosition() = 0;

	virtual Vector3 serverPosition() = 0;

	virtual float dashSpeed() = 0;
	
	virtual bool isDashing() = 0;

	virtual bool isMoving() = 0;

	virtual std::vector<Vector3> currentPath() = 0;

	virtual std::vector<Vector3> realPath() = 0;

	virtual int currentNav() = 0;

	virtual std::vector<Vector3> createPath(Vector3& endPosition, bool smooth = true) = 0;
};