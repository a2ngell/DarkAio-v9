#pragma once

class IObjectStats
{
public:
	virtual ~IObjectStats() = default;

public:
	virtual float bonusAP() = 0;
	virtual float bonusAD() = 0;
	virtual float totalAP() = 0;
	virtual float totalAD() = 0;

	virtual float abilityHaste() = 0;
	virtual float baseAttackDamage() = 0;
	virtual float flatPhysicalDamageMod() = 0;
	virtual float percentPhysicalDamageMod() = 0;
	virtual float flatBaseAttackDamageMod() = 0;
	virtual float percentBaseAttackDamageMod() = 0;
	virtual float baseAbilityDamage() = 0;
	virtual float flatMagicDamageMod() = 0;
	virtual float percentMagicDamageMod() = 0;
	virtual float flatMagicReduction() = 0;
	virtual float percentMagicReduction() = 0;
	virtual float moveSpeed() = 0;
	virtual float moveSpeedBaseIncrease() = 0;
	virtual float armor() = 0;
	virtual float bonusArmor() = 0;
	virtual float spellBlock() = 0;
	virtual float bonusSpellBlock() = 0;
	virtual float attackSpeedMod() = 0;
	virtual float percentAttackSpeedMod() = 0;
	virtual float percentMultiplicativeAttackSpeedMod() = 0;
	virtual float physicalLethality() = 0;
	virtual float flatArmorPenetration() = 0;
	virtual float percentArmorPenetration() = 0;
	virtual float percentBonusArmorPenetration() = 0;
	virtual float magicLethality() = 0;
	virtual float percentBonusMagicPenetration() = 0;
	virtual float flatMagicPenetration() = 0;
	virtual float percentMagicPenetration() = 0;
	virtual float attackRange() = 0;
	virtual float crit() = 0;
};