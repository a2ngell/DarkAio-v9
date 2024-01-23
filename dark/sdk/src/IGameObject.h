#pragma once

#include <Windows.h>
#include <string>
#include <memory>
#include <vector>

#include "Enums.h"
#include "Vector3.h"
#include "Perk.h"
#include "ICharacterDataStack.h"
#include "Hashes.h"

struct BoundingBox
{
	Vector3 min;
	Vector3 max;
};

class ICastInfo;
class IPathController;
class IUnitComponentInfo;
class ISpellInfo;
class IInventorySlot;
class ISpellInstance;
class IBuff;
class IObjectStats;
class IGameObject
{
public:
	virtual ~IGameObject() = default;

public:
	virtual bool isValid() = 0;

	virtual uintptr_t address() = 0;
	virtual unsigned short index() = 0;
	virtual int networkID() = 0;

	virtual ObjectType type() = 0;
	virtual ObjectTeam team() = 0;
	virtual CombatType combatType() = 0;

	virtual std::string name() = 0;
	virtual std::string modelName() = 0;

	virtual uint32_t nameHash() = 0;
	virtual uint32_t modelNameHash() = 0;

	virtual Vector3 position() = 0;
	virtual Vector3 serverPosition() = 0;
	virtual Vector3 direction() = 0;
	virtual Vector3 baseDrawPosition() = 0;

	virtual Vector2 healthBarPosition() = 0;

	virtual float distance(IGameObject* object) = 0;
	virtual float distance(const Vector3& position) = 0;

	virtual BoundingBox boundingBox() = 0;

	virtual IGameObject* getOwner() = 0; //for minions

	virtual bool isAlive() = 0;
	virtual bool isDead() = 0;
	virtual bool isZombie() = 0;
	virtual bool isAlly() = 0;
	virtual bool isEnemy() = 0;
	virtual bool isMe() = 0;
	virtual bool isTargetable() = 0;
	virtual bool isVisible() = 0;
	virtual bool isOnScreen() = 0;
	virtual bool isRanged() = 0;
	virtual bool isMelee() = 0;

	virtual bool hasActionState(ActionState state) = 0;

	virtual float autoAttackRange(IGameObject* object, float add = 0) = 0;
	virtual bool isInAutoAttackRange(IGameObject* object, float add = 0) = 0;

	virtual MinionType minionType() = 0;
	virtual bool isLaneMinion() = 0;
	virtual bool isMeleeMinion() = 0;
	virtual bool isRangedMinion() = 0;
	virtual bool isSiegeMinion() = 0;
	virtual bool isSuperMinion() = 0;
	
	virtual ResourceType resourceType() = 0;
	virtual float resource() = 0;
	virtual float maxResource() = 0;

	virtual float health() = 0;
	virtual float maxHealth() = 0;
	virtual float grayHealth() = 0;
	virtual float healthPercent() = 0;

	virtual float objectScale() = 0;

	virtual float allShield() = 0;
	virtual float physicalShield() = 0;
	virtual float magicalShield() = 0;
	
	virtual int specialStacks() = 0; //example: Samira 

	virtual int level() = 0;
	virtual int evolvePoints() = 0;

	virtual float totalExp() = 0;
	virtual float currentExp() = 0;
	virtual float maxExp() = 0;
	virtual float expPercent() = 0;

	virtual float boundingRadius() = 0;

	virtual float attackDelay() = 0;
	virtual float attackCastDelay() = 0;

	virtual IObjectStats* stats() = 0;

	virtual float respawnTimeReaminingNeutralCamp() = 0; //Dragon, Herald and Nash only
	virtual float respawnTimeRemaining() = 0; // Hero

	virtual std::unique_ptr<ISpellInfo> getBasicAttack(SpellSlot slot = SpellSlot::BasicAttack) = 0;

	virtual float inhibitorRespawnTime() = 0;

	virtual float bonusDamageToMinions() = 0;

	virtual float reducedDamageFromMinions() = 0;

	virtual std::unique_ptr<IUnitComponentInfo> unitComponentInfo() = 0;

	virtual std::unique_ptr<IPathController> pathController() = 0;

	virtual std::string getCircleIconName() = 0;
	virtual std::string getSquareIconName() = 0;

	virtual bool isFacing(IGameObject* object, float threshholdValue) = 0;
	virtual bool isFacing(const Vector3& position, float threshholdValue) = 0;

	// BuffManager
	virtual std::vector<std::unique_ptr<IBuff>> allBuffs() = 0; // Includes non active buffs
	virtual std::vector<std::unique_ptr<IBuff>> buffs() = 0;
	virtual bool hasBuff(BuffType type) = 0;
	virtual bool hasBuff(const std::vector<BuffType>& types) = 0;
	virtual bool hasBuff(uint32_t hash) = 0;

	virtual std::unique_ptr<IBuff> buff(uint32_t hash) = 0;
	virtual std::vector<std::unique_ptr<IBuff>> buffs(BuffType type) = 0;
	virtual std::vector<std::unique_ptr<IBuff>> buffs(const std::vector<BuffType>& types) = 0;

	// Spellbook
	virtual std::unique_ptr<ISpellInstance> spell(SpellSlot slot) = 0;
	virtual std::unique_ptr<ISpellInstance> spellByName(const std::string& name) = 0;
	virtual SpellSlot spellSlotByName(const std::string& name) = 0;
	virtual std::unique_ptr<ISpellInstance> spellByHash(uint32_t hash) = 0;
	virtual SpellSlot spellSlotByHash(uint32_t hash) = 0;
	virtual SpellState spellState(SpellSlot slot) = 0;
	virtual bool hasSpellState(SpellSlot slot, SpellState state) = 0;

	virtual bool isChanneling() = 0;

	virtual std::unique_ptr<ICastInfo> activeSpell() = 0;

	virtual int targetNetworkID() = 0;

	virtual std::unique_ptr<ICharacterDataStack> characterDataStack() = 0;
	virtual void setSkinID(int skinID) = 0;

	// Inventory
	virtual std::vector<std::unique_ptr<IInventorySlot>> slots() = 0;
	virtual bool hasItem(ItemID id) = 0;
	virtual std::unique_ptr<IInventorySlot> slot(int slot) = 0;
	virtual std::vector<std::unique_ptr<IInventorySlot>> slotByID(ItemID id) = 0;
	virtual SpellSlot spellSlotByItemID(ItemID id) = 0;


	// Perks
	virtual bool hasPerk(int id) = 0;
	virtual bool hasPerk(const std::string& name) = 0;
	virtual std::vector<Perk> perks() = 0;

	// Turret
	virtual TurretType turretType() = 0;
	virtual bool isFirstTierTurret() = 0;
	virtual bool isSecondTierTurret() = 0;
	virtual bool isThirdTierTurret() = 0;
	virtual bool isNexusTurret() = 0;

	// Actions
	virtual bool attack(IGameObject* object, bool triggerEvent = true) = 0;
	virtual bool move(const Vector3& position, bool triggerEvent = true) = 0;

	virtual bool castSpell(SpellSlot slot, const Vector3& position, bool castRelease = true, bool triggerEvent = true) = 0;
	virtual bool castSpell(SpellSlot slot, const Vector3& startPosition, const Vector3& endPosition, bool triggerEvent = true) = 0;
	virtual bool castSpell(SpellSlot slot, bool castRelease = true, bool triggerEvent = true) = 0;
	virtual bool castSpell(SpellSlot slot, IGameObject* object, bool castRelease = true, bool triggerEvent = true) = 0;
	virtual void releaseChargeableSpell(SpellSlot slot, const Vector3& position, bool triggerEvent = true) = 0;

	virtual bool levelSpell(SpellSlot slot) = 0;

	// Minions
	virtual bool isMiniRaptor() = 0;
	virtual bool isRaptor() = 0;

	virtual bool isRed() = 0;
	virtual bool isBlue() = 0;

	virtual bool isKrug() = 0;
	virtual bool isMiniKrug() = 0;
	virtual bool isMiniMiniKrug() = 0;

	virtual bool isWolf() = 0;
	virtual bool isMiniWolf() = 0;

	virtual bool isGromp() = 0;

	virtual bool isVisionPlant() = 0;
	virtual bool isJumpPlant() = 0;
	virtual bool isHealthPlant() = 0;

	virtual bool isBaron() = 0;
	virtual bool isDragon() = 0;
	virtual bool isHerald() = 0;

	virtual bool isScuttler() = 0;

	virtual bool isJungleMonster() = 0;
	virtual bool isBigJunglerMoster() = 0;

	virtual bool isWard() = 0;

	virtual ChampionID championID() = 0;

	// Missile
	virtual std::unique_ptr<ICastInfo> missileCastInfo() = 0;

	virtual Vector3 troyDirection() = 0;
};