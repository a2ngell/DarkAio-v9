#include "Spells.h"
#include "SDK.h"

SpellBase::SpellBase(SpellSlot slot)
	: m_slot(slot)
{
}

SpellSlot SpellBase::slot() const
{
	return m_slot;
}

float SpellBase::castDelay() const
{
	return m_castDelay;
}

bool SpellBase::canCastWhileDashing() const
{
	return m_canCastWhileDashing;
}

void SpellBase::setCastDelay(float delay)
{
	m_castDelay = delay;
}

void SpellBase::setCanCastWhileDashing(bool canCast)
{
	m_canCastWhileDashing = canCast;
}

bool SpellBase::isReady() const
{
	return g_localPlayer->hasSpellState(m_slot, SpellState::Ready);
}

bool SpellBase::isLearned() const
{
	return g_localPlayer->spell(m_slot)->isLearned();
}

bool SpellBase::canCast() const
{
	if (!g_localPlayer->hasActionState(ActionState::CanCast))
		return false;

	if (!g_localPlayer->isAlive() && !g_localPlayer->hasBuff(BUFF_HASH("KarthusDeathDefiedBuff")))
		return false;

	if (m_castDelayCheck)
		if (m_castDelay > 0)
			if (g_moduleManager->orbwalker()->isCastingSpell())
				return false;

	if (g_game->tickCount() - m_lastCastTick < g_game->getPing() * 1.5)
		return false;

	if (g_hud->spellLogic()->isChargeingSpell())
	{
		return false;
	}

	return true;
}
void SpellBase::setUseCastDelayCheck(bool use)
{
	m_castDelayCheck = use;
}

SelfSpell::SelfSpell(SpellSlot slot)
	: SpellBase(slot)
{
}

bool SelfSpell::cast()
{
	if (!isReady())
		return false;
	if (!canCast())
		return false;


	if (g_localPlayer->castSpell(m_slot))
	{
		m_lastCastTick = g_game->tickCount();
		return true;
	}
	return false;
}

SelfSpellAoe::SelfSpellAoe(SpellSlot slot)
	: SpellBase(slot)
{
	
}

bool SelfSpellAoe::cast()
{
	if (!isReady())
		return false;
	if (!canCast())
		return false;

	if (g_localPlayer->castSpell(m_slot))
	{
		m_lastCastTick = g_game->tickCount();
		return true;
	}
	return false;
}

bool SelfSpellAoe::isInRange(const Vector3& position) const
{
	return g_localPlayer->serverPosition().distance(position) < m_effectRange;
}

bool SelfSpellAoe::isInRange(IGameObject* target) const
{
	return isInRange(target->position());
}

bool SelfSpellAoe::castPrediction(IGameObject* target, Hitchance minHitchance)
{
	if (!isReady())
		return false;
	if (!canCast())
		return false;

	PredictionInput input = getDefaultPredictionInput();
	input.target = target;
	auto pred = g_moduleManager->prediction()->getPrediction(input);
	if (!pred.isHitchanceMatching(minHitchance))
		return false;

	if (!isInRange(pred.unitPosition))
		return false;

	if (g_localPlayer->castSpell(m_slot))
	{
		m_lastCastTick = g_game->tickCount();
		return true;
	}
	return false;
}

bool SelfSpellAoe::castMultiPrediction(int minTargets, Hitchance minimumHitchance, std::function<bool(IGameObject*)> filter)
{
	if (!isReady())
		return false;
	if (!canCast())
		return false;
	ObjectList castableEnemies;
	auto enemies = g_objectManager->players().alive().visible().targetable().enemies().inRange(g_localPlayer, m_effectRange);
	if (filter)
		enemies = enemies.filter(filter);
	for (auto p : enemies)
	{
		PredictionInput input = getDefaultPredictionInput();
		input.target = p;
		auto pred = g_moduleManager->prediction()->getPrediction(input);
		if (pred.isHitchanceMatching(minimumHitchance))
			if (isInRange(pred.unitPosition))
				castableEnemies.push_back(p);
	}

	if (castableEnemies.size() < minTargets)
		return false;

	if (g_localPlayer->castSpell(m_slot))
	{
		m_lastCastTick = g_game->tickCount();
		return true;
	}
	return false;
}

PredictionInput SelfSpellAoe::getDefaultPredictionInput() const
{
	PredictionInput input;
	input.from = g_localPlayer->serverPosition();
	input.rangeCheckFrom = g_localPlayer->serverPosition();
	input.delay = m_castDelay;
	input.range = m_effectRange;
	input.caster = g_localPlayer;
	input.type = SkillshotType::Circle;
	return input;
}

IGameObject* SelfSpellAoe::target(float overrideRange, std::function<ObjectList(const ObjectList&)> filter) const
{
	auto enemies = g_objectManager->players().alive().visible().targetable().enemies().inRange(g_localPlayer, m_effectRange);
	if (filter)
		enemies = filter(enemies);
	return g_moduleManager->targetSelector()->getTarget(enemies);
}

float SelfSpellAoe::effectRange() const
{
	return m_effectRange;
}

void SelfSpellAoe::setEffectRange(float range)
{
	m_effectRange = range;
}

RangedSpell::RangedSpell(SpellSlot slot)
	: SpellBase(slot)
{
	
}

bool RangedSpell::isInRange(const Vector3& position) const
{
	return g_localPlayer->distance(position) <= range();
}

bool RangedSpell::isInRange(IGameObject* target) const
{
	float range = m_range
		+ (m_useSourceBoundingRadiusRangeCheck ? g_localPlayer->boundingRadius() : 0)
		+ (m_useTargetBoundingRadiusRangeCheck ? target->boundingRadius() : 0);

	return g_localPlayer->distance(target) <= range;
}

float RangedSpell::range() const
{
	return m_range + (m_useSourceBoundingRadiusRangeCheck ? g_localPlayer->boundingRadius() : 0);
}

float RangedSpell::radius() const
{
	return m_radius;
}

float RangedSpell::speed() const
{
	return m_speed;
}

float RangedSpell::minMissileSpeed() const
{
	return m_minMissileSpeed;
}

float RangedSpell::maxMissileSpeed() const
{
	return m_maxMissileSpeed;
}

float RangedSpell::missileAcceleration() const
{
	return m_missileAcceleration;
}

bool RangedSpell::useSourceBoundingRadiusRangeCheck() const
{
	return m_useSourceBoundingRadiusRangeCheck;
}

bool RangedSpell::useTargetBoundingRadiusRangeCheck() const
{
	return m_useTargetBoundingRadiusRangeCheck;
}

const std::vector<Collisions>& RangedSpell::collisions() const
{
	return m_collisions;
}

size_t RangedSpell::collisionCount() const
{
	return m_collisionCount;
}

void RangedSpell::setRange(float range)
{
	m_range = range;
}

void RangedSpell::setRadius(float radius)
{
	m_radius = radius;
}

void RangedSpell::setSpeed(float speed)
{
	m_speed = speed;
}

void RangedSpell::setMinMissileSpeed(float speed)
{
	m_minMissileSpeed = speed;
}

void RangedSpell::setMaxMissileSpeed(float speed)
{
	m_maxMissileSpeed = speed;
}

void RangedSpell::setMissileAcceleration(float acceleration)
{
	m_missileAcceleration = acceleration;
}

void RangedSpell::setUseSourceBoundingRadiusRangeCheck(bool use)
{
	m_useSourceBoundingRadiusRangeCheck = use;
}

void RangedSpell::setUseTargetBoundingRadiusRangeCheck(bool use)
{
	m_useTargetBoundingRadiusRangeCheck = use;
}

void RangedSpell::setCollisions(const std::vector<Collisions>& collisions)
{
	m_collisions = collisions;
}

void RangedSpell::setCollisionCount(size_t count)
{
	m_collisionCount = count;
}

TargetSpell::TargetSpell(SpellSlot slot)
	: RangedSpell(slot)
{
}

bool TargetSpell::cast(IGameObject* target)
{
	if (!isReady())
		return false;
	if (!canCast())
		return false;
	if (!canHit(target))
		return false;
	if (g_localPlayer->castSpell(m_slot, target))
	{
		m_lastCastTick = g_game->tickCount();
		return true;
	}

	return false;
}

bool TargetSpell::canHit(IGameObject* target)
{
	if (!isInRange(target))
		return false;

	CollisionInput input;
	input.collisions = m_collisions;
	input.delay = m_castDelay;
	input.from = g_localPlayer->position();
	input.missileSpeed = m_speed;
	input.radius = m_radius;
	input.source = g_localPlayer;
	input.target = target;
	input.to = target->position();
	auto result = g_moduleManager->collision()->collisionCheck(input);
	if (result.isCollision)
	{
		return false;
	}

	return true;
}

IGameObject* TargetSpell::target(float overrideRange, std::function<bool(IGameObject*)> filter) const
{
	float range = overrideRange != FLT_MAX ? overrideRange : this->range();
	auto enemies = g_objectManager->players().alive().visible().targetable().enemies().inRange(g_localPlayer, range, m_useTargetBoundingRadiusRangeCheck);
	if (filter)
		enemies = enemies.filter(filter);
	return g_moduleManager->targetSelector()->getTarget(enemies);
}

PositionSpell::PositionSpell(SpellSlot slot)
	: RangedSpell(slot)
{
}

bool PositionSpell::isInRange(const Vector3& position) const
{
	return g_localPlayer->distance(position) <= range();
}

bool PositionSpell::cast(const Vector3& position)
{
	if (!isReady())
		return false;
	if (!isInRange(position))
		return false;
	if (!canCast())
		return false;
	
	if (g_localPlayer->castSpell(m_slot, position))
	{
		m_lastCastTick = g_game->tickCount();
		return true;
	}
	return false;
}

bool PositionSpell::castPrediction(IGameObject* target, Hitchance minHitchance, bool castOnUnitPosition)
{
	if (isReady() && canCast())
	{
		PredictionInput input = getDefaultPredictionInput();
		input.target = target;
		auto output = g_moduleManager->prediction()->getPrediction(input);
		if (output.isHitchanceMatching(minHitchance))
		{
			if (isInRange(output.castPosition))
			{
				if (g_localPlayer->castSpell(m_slot, castOnUnitPosition ? output.unitPosition : output.castPosition))
				{
					m_lastCastTick = g_game->tickCount();
					return true;
				}
			}
		}
	}
	return false;
}

bool PositionSpell::castMultiPrediction(int minTargets, Hitchance minimumHitchance, std::function<bool(IGameObject*)> filter)
{
	if (!isReady())
		return false;
	if (!canCast())
		return false;

	auto multiInput = getDefaultMultiPredictionInput(minTargets, minimumHitchance);
	multiInput.additionalTargetFilter = filter;
	auto out = g_moduleManager->prediction()->getMultiPrediction(multiInput);
	if (out.isValid)
	{ 
		if (this->cast(out.castPosition))
		{
			m_lastCastTick = g_game->tickCount();
			return true;
		}
	}
	return false;
}

bool PositionSpell::canHit(IGameObject* target, Hitchance minHitchance)
{
	if (!isReady())
		return false;
	PredictionInput input = getDefaultPredictionInput();
	input.target = target;
	auto output = g_moduleManager->prediction()->getPrediction(input);
	if (!output.isHitchanceMatching(minHitchance))
		return false;
	if (!isInRange(output.castPosition))
		return false;
	return true;
}

PredictionInput PositionSpell::getDefaultPredictionInput() const
{
	PredictionInput input;
	input.from = g_localPlayer->serverPosition();
	input.rangeCheckFrom = g_localPlayer->serverPosition();
	input.delay = m_castDelay;
	input.radius = m_radius;
	input.range = this->range();
	input.caster = g_localPlayer;
	input.missileSpeed = m_speed;
	input.minMissileSpeed = m_minMissileSpeed;
	input.maxMissileSpeed = m_maxMissileSpeed;
	input.missileAcceleration = m_missileAcceleration;
	input.type = m_skillshotType;
	input.collisions = m_collisions;
	input.collisionCount = m_collisionCount;
	input.useBoundingRadius = m_boundingRadiusCollision;
	return input;
}

MultiPredictionInput PositionSpell::getDefaultMultiPredictionInput(int minTargets, Hitchance minimumHitchance) const
{
	MultiPredictionInput input;
	input.from = g_localPlayer->serverPosition();
	input.rangeCheckFrom = g_localPlayer->serverPosition();
	input.delay = m_castDelay;
	input.radius = m_radius;
	input.range = this->range();
	input.caster = g_localPlayer;
	input.missileSpeed = m_speed;
	input.minMissileSpeed = m_minMissileSpeed;
	input.maxMissileSpeed = m_maxMissileSpeed;
	input.missileAcceleration = m_missileAcceleration;
	input.type = m_skillshotType;
	input.collisions = m_collisions;
	input.collisionCount = m_collisionCount;
	input.useBoundingRadius = m_boundingRadiusCollision;
	input.minimumTargets = minTargets;
	input.minimumHitchance = minimumHitchance;
	return input;
}

IGameObject* PositionSpell::target(float overrideRange, std::function<bool(IGameObject*)> filter) const
{
	float range = overrideRange != FLT_MAX ? overrideRange : this->range();
	if (m_skillshotType == SkillshotType::Circle)
		range += m_radius;
	auto enemies = g_objectManager->players().alive().enemies().inRange(g_localPlayer, range, m_useTargetBoundingRadiusRangeCheck);
	if (filter)
		enemies = enemies.filter(filter);

	auto selectedEnemies = g_moduleManager->targetSelector()->getTargetsSorted(enemies, false, false);
	
	auto predInput = getDefaultPredictionInput();
	predInput.range = range;
	for (auto enemy : selectedEnemies)
	{
		predInput.target = enemy;
		auto predOutput = g_moduleManager->prediction()->getPrediction(predInput);
		if (predOutput.isHitchanceMatching(Hitchance::Instant))
			return enemy;
	}
	return nullptr;
}

SkillshotType PositionSpell::skillshotType() const
{
	return m_skillshotType;
}

bool PositionSpell::boundingRadiusCollision() const
{
	return m_boundingRadiusCollision;
}

void PositionSpell::setSkillshotType(SkillshotType type)
{
	m_skillshotType = type;
}

void PositionSpell::setBoundingRadiusCollision(bool f)
{
	m_boundingRadiusCollision = f;
}

ChargeableSpell::ChargeableSpell(SpellSlot slot)
	: PositionSpell(slot), m_overrideIsChargeingFunction(nullptr)
{
}

bool ChargeableSpell::startChargeing(const Vector3& position)
{
	if (!isReady())
		return false;
	if (!canCast())
		return false;
	if (g_game->tickCount() - m_lastStartTick < 30 + g_game->getPing())
		return false;
	if (isChargeing())
		return false;

	if (g_localPlayer->castSpell(m_slot, position, false))
	{
		m_lastStartTick = g_game->tickCount();
		return true;
	}
	return false;
}

bool ChargeableSpell::startChargeingPrediction(IGameObject* target, Hitchance minHitchance)
{
	if (!isReady())
		return false;
	if (!canCast())
		return false;
	if (g_game->tickCount() - m_lastStartTick < 30 + g_game->getPing())
		return false;
	if (isChargeing())
		return false;

	PredictionInput input = getDefaultPredictionInput();
	input.target = target;
	auto output = g_moduleManager->prediction()->getPrediction(input);
	if (!output.isHitchanceMatching(minHitchance))
		return false;

	if (g_localPlayer->castSpell(m_slot, output.castPosition, false))
	{
		m_lastStartTick = g_game->tickCount();
		return true;
	}
	return false;
}

bool ChargeableSpell::cast(const Vector3& position)
{
	if (!isChargeing())
		return false;
	if (!isInRange(position))
		return false;

	m_lastCastTick = g_game->tickCount();
	g_localPlayer->releaseChargeableSpell(m_slot, position);
	return true;
}

bool ChargeableSpell::castPrediction(IGameObject* target, Hitchance minHitchance, bool castOnUnitPosition)
{
	if (!isChargeing())
		return false;
	
	PredictionInput input = getDefaultPredictionInput();
	input.target = target;
	auto output = g_moduleManager->prediction()->getPrediction(input);
	if (!output.isHitchanceMatching(minHitchance))
		return false;
	if (!isInRange(output.castPosition))
		return false;

	m_lastCastTick = g_game->tickCount();
	g_localPlayer->releaseChargeableSpell(m_slot, castOnUnitPosition ? output.unitPosition : output.castPosition);
	return true;
}

bool ChargeableSpell::isChargeing() const
{
	if (m_overrideIsChargeingFunction)
		return m_overrideIsChargeingFunction();

	if (g_hud->spellLogic()->isChargeingSpell())
	{
		return true;
	}

	auto activeSpell = g_localPlayer->activeSpell();
	if (activeSpell)
	{
		if (activeSpell->slot() == m_slot)
			return true;
	}
	return false;
}

void ChargeableSpell::setMaxChargeingTime(int time)
{
	m_maxChargeingTime = time;
}

int ChargeableSpell::maxChargeingTime() const
{
	return m_maxChargeingTime;
}

void ChargeableSpell::overrideIsChargeingFunction(std::function<bool()> func)
{
	m_overrideIsChargeingFunction = func;
}

DashSpell::DashSpell(SpellSlot slot)
	: SpellBase(slot)
{
}

bool DashSpell::cast(const Vector3& position)
{
	if (!canUseDash(position))
		return false;

	if (g_localPlayer->castSpell(m_slot, position))
	{
		m_lastCastTick = g_game->tickCount();
		return true;
	}

	return false;
}

bool DashSpell::cast(IGameObject* target, const Vector3& position)
{
	if (!canUseDash(position))
		return false;


	if (g_localPlayer->castSpell(m_slot, target))
	{
		m_lastCastTick = g_game->tickCount();
		return true;
	}

	return false;
}

bool DashSpell::cast(IGameObject* target)
{
	return cast(target, target->position());
}

DashType DashSpell::dashType() const
{
	return m_dashType;
}

float DashSpell::range() const
{
	return m_range + (m_useSourceBoundingRadiusRangeCheck ? g_localPlayer->boundingRadius() : 0);
}

float DashSpell::speed() const
{
	return m_speed;
}

void DashSpell::setDashType(DashType type)
{
	m_dashType = type;
}

void DashSpell::setRange(float range)
{
	m_range = range;
}

void DashSpell::setSpeed(float speed)
{
	m_speed = speed;
}

bool DashSpell::useSourceBoundingRadiusRangeCheck() const
{
	return m_useSourceBoundingRadiusRangeCheck;
}

bool DashSpell::useTargetBoundingRadiusRangeCheck() const
{
	return m_useTargetBoundingRadiusRangeCheck;
}

void DashSpell::setUseSourceBoundingRadiusRangeCheck(bool use)
{
	m_useSourceBoundingRadiusRangeCheck = use;
}

void DashSpell::setUseTargetBoundingRadiusRangeCheck(bool use)
{
	m_useTargetBoundingRadiusRangeCheck = use;
}

bool DashSpell::isInRange(const Vector3& position) const
{
	return g_localPlayer->distance(position) <= range();
}

bool DashSpell::isInRange(IGameObject* target) const
{
	float range = m_range
		+ (m_useSourceBoundingRadiusRangeCheck ? g_localPlayer->boundingRadius() : 0)
		+ (m_useTargetBoundingRadiusRangeCheck ? target->boundingRadius() : 0);

	return g_localPlayer->distance(target) <= range;
}

bool DashSpell::canDashToPosition(const Vector3& position) const
{
	if (m_dashType == DashType::Normal)
	{
		if (!g_moduleManager->evade()->isSafePath({ g_localPlayer->position(), position }, m_castDelay, m_speed))
			return false;
	}
	else
	{
		if (!g_moduleManager->evade()->isSafeToBlink({ position }, m_castDelay))
			return false;
	}
	return true;
}

bool DashSpell::canUseDash(const Vector3& position) const
{
	if (!isReady())
		return false;
	if (!isInRange(position))
		return false;
	if (!canCast())
		return false;
	if (!canDashToPosition(position))
		return false;

	return true;
}

DoublePositionSpell::DoublePositionSpell(SpellSlot slot)
	: RangedSpell(slot)
{
}

bool DoublePositionSpell::cast(const Vector3& startPosition, const Vector3& endPosition)
{
	if (!isReady())
		return false;
	if (!canCast())
		return false;

	if (g_localPlayer->castSpell(m_slot, startPosition, endPosition))
	{
		m_lastCastTick = g_game->tickCount();
		return true;
	}
	return false;
}

IGameObject* DoublePositionSpell::target(float overrideRange, std::function<bool(IGameObject*)> filter) const
{
	float range = overrideRange != FLT_MAX ? overrideRange : this->range();
	auto enemies = g_objectManager->players().alive().visible().targetable().enemies().inRange(g_localPlayer, range, m_useTargetBoundingRadiusRangeCheck);
	if (filter)
		enemies = enemies.filter(filter);
	return g_moduleManager->targetSelector()->getTarget(enemies);
}
