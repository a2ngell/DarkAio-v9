#pragma once

#include "ObjectList.h"
#include <map>

class IInterruptibleSpellMenu;
class IInterruptibleSpell
{
public:
	virtual ~IInterruptibleSpell() = default;

public:
	virtual std::unique_ptr<IInterruptibleSpellMenu> createInterruptibleSpellMenu(TabChildPtr parent) = 0;
};