#pragma once

#include "Enums.h"

class IInventorySlot
{
public:
	virtual ~IInventorySlot() = default;

public:
	virtual int slot() = 0;

	virtual int count() = 0;

	virtual ItemID itemID() = 0;

	virtual short cost() = 0;

	virtual float critPercent() = 0;
};