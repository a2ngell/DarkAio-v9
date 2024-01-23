#pragma once

#include "ObjectList.h"
#include <map>
#include "IMenu.h"

struct GapcloseInfo
{
	ChampionID championID;
	uint32_t spellHash;
	std::string add;
	PathType type;
	bool isFixedRange;
	float range;
	float maxDashSpeed;
	bool speedMove;
	float minRange;
};

class IGapcloseMenu;
class IGapclose
{
public:
	virtual ~IGapclose() = default;
												
public:
	virtual std::unique_ptr<IGapcloseMenu> createGapcloseMenu(TabChildPtr parent) = 0;
};