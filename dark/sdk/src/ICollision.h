#pragma once

#include "Vector3.h"
#include "Enums.h"
#include <vector>

class IGameObject;

struct CollisionInput
{
	int collisionCount = 1; // Example: LuxQ
	std::vector<Collisions> collisions;

	IGameObject* source = nullptr;
	IGameObject* target = nullptr;

	Vector3 from;
	Vector3 to;

	float radius = 1;
	float delay = 0;
	float missileSpeed = FLT_MAX;
};

struct CollisionPoint
{
	Vector3 position;
	Collisions type;
	IGameObject* object;
};

struct CollisionOutput
{
	bool isCollision;
	std::vector<CollisionPoint> collisions;
};

class ICollision
{
public:
	virtual ~ICollision() = default;

public:
	virtual CollisionOutput collisionCheck(const CollisionInput& input) = 0;
};