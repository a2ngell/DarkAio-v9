#pragma once

#include "Enums.h"

class IUnitComponentInfo
{
public:
	virtual ~IUnitComponentInfo() = default;

public:
	virtual float baseHealth() = 0;

	virtual float pathfindingRadius() = 0;

	virtual ChampionID championID() = 0;
};