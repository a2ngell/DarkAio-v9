#pragma once

#include <string>
#include <memory>

class ISpellTargetingData;
class ISpellInfo;
class ISpellInstance
{
public:
	virtual ~ISpellInstance() = default;

public:
	virtual uintptr_t ptr() = 0;

	virtual int level() = 0;
	
	virtual bool isLearned() = 0;
	
	virtual float cooldownExpires() = 0;

	virtual int charges() = 0;

	virtual float chargeCooldownExpires() = 0;

	virtual std::string name() = 0;

	virtual float currentCooldown() = 0;

	virtual bool isReady() = 0;

	virtual std::unique_ptr<ISpellTargetingData> targetingData() = 0;

	virtual std::unique_ptr<ISpellInfo> info() = 0;

	virtual float getCooldownTimeRemaining() = 0;

	virtual uint32_t spellHash() = 0;
};