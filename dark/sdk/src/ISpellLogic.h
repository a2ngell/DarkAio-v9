#pragma once

#include <memory>

#include "Enums.h"

class ISpellInstance;
class ISpellLogic
{
public:
	virtual ~ISpellLogic() = default;

public:
	virtual bool levelSpell(SpellSlot slot) = 0;

	virtual SpellSlot slotBySpellInfo(uintptr_t spellInfo) = 0;

	// State 0 = down
	// State 1 = up
	virtual void triggerSpell(unsigned int slot, int method, unsigned int state, bool triggerEvent = true) = 0;

	virtual bool isChargeingSpell() = 0;

	virtual bool spellFindTarget(SpellSlot slot) = 0;
};