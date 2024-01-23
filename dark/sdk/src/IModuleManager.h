#pragma once

class IEvade;
class ISpellFarming;
class ITracker;
class ICollision;
class IPrediction;
class IInterruptibleSpell;
class IDamageDrawings;
class IGapclose;
class ITargetspell;
class ITargetSelector;
class IPermaShow;
class IMinionHealthPrediction;
class IHealthPrediction;
class IDamageLib;
class IOrbwalker;
class IModuleManager
{
public:
	virtual ~IModuleManager() = default;
	
public:
	virtual IDamageLib* damageLib() = 0;
	virtual void setDamageLib(IDamageLib* damageLib) = 0;

	virtual IOrbwalker* orbwalker() = 0;
	virtual void setOrbwalker(IOrbwalker* orbwalker) = 0;

	virtual IHealthPrediction* healthPrediction() = 0;
	virtual void setHealthPrediction(IHealthPrediction* healthPrediction) = 0;

	virtual IMinionHealthPrediction* minionHealthPrediction() = 0;
	virtual void setMinionHealthPrediction(IMinionHealthPrediction* minionHealthPrediction) = 0;

	virtual IPermaShow* permaShow() = 0;
	virtual void setPermaShow(IPermaShow* permaShow) = 0;

	virtual ITargetSelector* targetSelector() = 0;
	virtual void setTargetSelector(ITargetSelector* targetSelector) = 0;

	virtual ITargetspell* targetspell() = 0;
	virtual void setTargetspell(ITargetspell* targetspell) = 0;

	virtual IGapclose* gapclose() = 0;
	virtual void setGapclose(IGapclose* gapclose) = 0;

	virtual IDamageDrawings* damageDrawings() = 0;
	virtual void setDamageDrawings(IDamageDrawings* damageDrawings) = 0;

	virtual IInterruptibleSpell* interruptibleSpell() = 0;
	virtual void setInterruptibleSpell(IInterruptibleSpell* interruptibleSpell) = 0;

	virtual IPrediction* prediction() = 0;
	virtual void setPrediction(IPrediction* prediction) = 0;

	virtual ICollision* collision() = 0;
	virtual void setCollision(ICollision* collision) = 0;

	virtual ITracker* tracker() = 0;
	virtual void setTracker(ITracker* tracker) = 0;

	virtual ISpellFarming* spellFarming() = 0;
	virtual void setSpellFarming(ISpellFarming* spellFarming) = 0;

	virtual IEvade* evade() = 0;
	virtual void setEvade(IEvade* evade) = 0;
};