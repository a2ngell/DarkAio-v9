#pragma once

#include <vector>
#include <memory>
#include <string>

struct Skin
{
	unsigned int id;
	std::string name;
};


class IChampion
{
public:
	virtual ~IChampion() = default;

public:
	virtual std::string name() = 0;

	virtual const std::vector<Skin>& skins() = 0;
};