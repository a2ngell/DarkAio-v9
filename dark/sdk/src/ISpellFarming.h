#pragma once

#include "Spells.h"

enum LaneClearMode
{
	OnlyIfSpellKeyIsPressed,
	Always,
};

struct FarmSpellInput
{
	SpellBase* spell = nullptr;

	std::optional<std::string> informationString;

	bool isAoe = false;
	bool dontCancelAutoAttacks = true;
	bool onCancelDash = false; // example: Vayne Q 
	bool onCancelSpell = false; // example: Sivir W
	bool onPreAttackSelf = false; // example: Tristana Q
	bool onTargetSelf = false; // example: Lee Sin W1

	bool lastHitMenu = true;
	bool lastHit = false;
	std::optional<int> lastHitMinResource;

	bool laneClearMenu = true;
	bool laneClear = false;
	bool laneClearFastPush = true;
	std::optional<int> laneClearMinHits;
	std::optional<int> laneClearMinResource;
	std::optional<bool> laneClearLastHit;

	bool jungleClearMenu = true;
	bool jungleClear = false;
	bool jungleClearFastPush = true;
	std::optional<bool> jungleClearOnlyBig;
	std::optional<int> jungleClearMinResource;
	std::optional<bool> jungleClearLastHit;

	MenuTabPtr parentTab = nullptr;
	std::optional<std::string> menuName = std::nullopt;

	std::function<bool()> additionalIsReadyCheck = nullptr;
	std::function<float(IGameObject*)> overrideCalculateDamageFunction = nullptr;
	std::function<bool(IGameObject*)> extraConditionToObject = nullptr;
	std::function<void()> onSpellCasted = nullptr;
};

struct FarmSpell
{
	FarmSpellInput input;

	TabChildPtr child = nullptr;

	MenuElementPtr informationString = nullptr;

	MenuElementPtr lastHitAlways = nullptr;
	MenuElementPtr lastHitMinResource = nullptr;

	MenuElementPtr laneClearAlways = nullptr;
	MenuElementPtr laneClearFastPush = nullptr;
	MenuElementPtr laneClearMinResource = nullptr;
	MenuElementPtr laneClearMinHits = nullptr;
	MenuElementPtr laneClearLastHit = nullptr;

	MenuElementPtr jungleClearAlways = nullptr;
	MenuElementPtr jungleClearFastPush = nullptr;
	MenuElementPtr jungleClearMinResource = nullptr;
	MenuElementPtr jungleClearOnlyBig = nullptr;
	MenuElementPtr jungleClearLastHit = nullptr;
};


class ISpellFarming
{
public:
	virtual ~ISpellFarming() = default;

public:
	virtual FarmSpell* addSpell(const FarmSpellInput& input) = 0;
	virtual void removeSpell(FarmSpell* spell) = 0;

public:
	virtual bool isFarmingKeyPressed() const = 0;
};