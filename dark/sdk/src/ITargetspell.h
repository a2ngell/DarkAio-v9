#pragma once

#include "ObjectList.h"
#include <map>

class ITargetspellMenu;
class ITargetspell
{
public:
	virtual ~ITargetspell() = default;

public:
	virtual std::unique_ptr<ITargetspellMenu> createTargetspellMenu(TabChildPtr parent, std::vector<TargetspellType> type) = 0;
};