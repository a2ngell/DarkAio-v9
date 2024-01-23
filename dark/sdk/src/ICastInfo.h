#pragma once

#include <memory>
#include <vector>

#include "Vector3.h"
#include "Enums.h"

class IGameObject;
class ISpellInfo;
class ICastInfo
{
public:
	virtual ~ICastInfo() = default;

public:
	virtual std::unique_ptr<ISpellInfo> info() = 0;
	
	virtual SpellSlot slot() = 0;

	virtual float castTime() = 0;

	virtual unsigned short casterIndex() = 0;

	virtual IGameObject* caster() = 0;

	virtual unsigned short targetIndex() = 0;

	virtual IGameObject* target() = 0;

	virtual unsigned int missileNetworkID() = 0;

	virtual float autoAttackStartTime() = 0;

	virtual float autoAttackEndTime() = 0;

	virtual float castDelay() = 0;

	virtual float attackTime() = 0;

	virtual Vector3 startPos() = 0;

	virtual Vector3 endPos() = 0;

	virtual float startTime() = 0;

	virtual float endTime() = 0;

	virtual bool isBasicAttack() = 0;

	virtual bool isSpecialAttack() = 0;

	virtual bool isAutoAttack() = 0;

	virtual uint32_t nameHash() = 0;

	virtual uintptr_t address() = 0;
};