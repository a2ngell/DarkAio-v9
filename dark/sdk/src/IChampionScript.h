#pragma once

#include "Enums.h"

class IChampionScript
{
public:
	virtual ~IChampionScript() = default;

public:
	virtual void load() = 0;
	virtual void unload() = 0;
	virtual ChampionID championID() = 0;
};