#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Enums.h"

class INavMesh
{
public:
	virtual ~INavMesh() = default;

public:
	virtual float heightForPosition(float x, float z) = 0;

	virtual float heightForPosition(const Vector2& position) = 0;

	virtual float heightForPosition(const Vector3& position) = 0;

	virtual Vector3 toWorldVector(const Vector2& position) = 0;

	virtual int getCellFlags(const Vector3& position) = 0; 

	virtual bool isWall(const Vector3& position) = 0;

	virtual bool isWall(const Vector2& position) = 0;

	virtual bool isBush(const Vector3& position) = 0;

	virtual bool isBush(const Vector2& position) = 0;

	virtual Vector3 minWorldPos() = 0;
	
	virtual Vector3 maxWorldPos() = 0;

	virtual Vector3 getWorldSize() = 0;

	virtual bool isArenaMap() = 0;

	virtual bool isSummonersRiftMap() = 0;

	virtual bool isAramMap() = 0;
};