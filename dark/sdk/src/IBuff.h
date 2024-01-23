#pragma once

#include "Enums.h"

#include <string>

class IGameObject;
class IBuff
{
public:
	virtual ~IBuff() = default;

public:
	virtual uintptr_t address() = 0;

	virtual bool isValid() = 0;

	virtual std::string name() = 0;

	virtual uint32_t hash() = 0;

	virtual BuffType type() = 0;

	virtual float startTime() = 0;

	virtual float endTime() = 0;

	virtual float duration() = 0;

	virtual int count() = 0;

	virtual short casterIndex() = 0;

	virtual int intStacks() = 0;

	virtual float floatStacks() = 0;

	virtual bool isPermanent() = 0;

	virtual bool isActive() = 0;

	virtual bool isBuffType(BuffType type) = 0;

	virtual IGameObject* caster() = 0;
};