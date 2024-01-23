#pragma once

#include "Vector2.h"
#include "Vector3.h"

class IWorld
{
public:
	virtual ~IWorld() = default;
	
public:
	virtual Vector2 w2s(const Vector3& world, bool* onScreen = nullptr) = 0;

	virtual Vector2 w2m(const Vector3& world) = 0;
	
	virtual bool isOnScreen(const Vector3& world, float tolerance = 0.f) = 0;

	virtual bool isOnScreen(const Vector2& screen, float tolerance = 0.f) = 0;

	virtual Vector2 minimapPosition() = 0;

	virtual Vector2 minimapSize() = 0;
};