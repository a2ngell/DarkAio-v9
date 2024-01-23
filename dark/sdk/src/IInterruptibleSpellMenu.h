#pragma once

#include "Enums.h"

class IInterruptibleSpellMenu
{
public:
	virtual ~IInterruptibleSpellMenu() = default;

public:
	virtual bool isSpellEnabled(ChampionID id, SpellSlot slot) = 0;
};