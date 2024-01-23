#pragma once

#include "IChampion.h"

class IChampionManager
{
public:
	virtual ~IChampionManager() = default;

public:
	virtual const std::vector<std::shared_ptr<IChampion>>& champions() = 0;

	virtual std::shared_ptr<IChampion> getChampionByName(const std::string& name) = 0;
};