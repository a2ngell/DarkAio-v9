#pragma once

#include "Enums.h"

class IGameObject;
class IDamageLib
{
public:
	virtual ~IDamageLib() = default;
	
public:
	virtual float calculateSpellDamage(IGameObject* src, IGameObject* target, float magicalAmount, float physicalAmount, float trueAmount, bool triggerOnHit = false, float onHitEffectiveness = 1.f) = 0;

	virtual float calculateOnHitDamage(IGameObject* src, IGameObject* target) = 0;

	virtual float calculateAutoAttackDamage(IGameObject* src, IGameObject* target) = 0;

	virtual bool isKillableWithDamage(IGameObject* src, IGameObject* target, float calculatedDamage, bool isSpell) = 0;

	virtual float getSpellDamage(IGameObject* src, IGameObject* target, SpellSlot slot) = 0;

	virtual float calculateRawAutoAttackDamage(IGameObject* src, IGameObject* target) = 0;
};