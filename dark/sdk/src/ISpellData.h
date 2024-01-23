#pragma once

#include <string>

class ISpellData
{
public:
	virtual ~ISpellData() = default;

public:
	virtual std::string iconName() const = 0;

	virtual float baseCooldown(int level) const = 0;

	virtual float missileSpeed() const = 0;

	virtual float manaCost(int level) const = 0;
};