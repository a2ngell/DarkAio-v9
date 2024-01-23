#pragma once

#include "Enums.h"
#include "Vector3.h"
#include "IGameObject.h"
#include "IPrediction.h"

#include "ObjectList.h"
#include <functional>

class SpellBase
{
public:
	SpellBase(SpellSlot slot);
	~SpellBase() = default;

public:
	virtual SpellType type() const { return SpellType::Base; }

	SpellSlot slot() const;
	float castDelay() const;
	bool canCastWhileDashing() const;

	void setCastDelay(float delay);
	void setCanCastWhileDashing(bool canCast);

	bool isReady() const;

	bool isLearned() const;

	bool canCast() const;

	void setUseCastDelayCheck(bool use);

protected:
	SpellSlot m_slot;
	float m_castDelay = 250;
	bool m_canCastWhileDashing = false;
	int m_lastCastTick = 0;
	int m_castExtraTime = 50;
	bool m_castDelayCheck = true;
};

class SelfSpell : public SpellBase
{
public:
	SelfSpell(SpellSlot slot);
	~SelfSpell() = default;

public:
	virtual SpellType type() const { return SpellType::Self; }

	bool cast();
};

class SelfSpellAoe : public SpellBase
{
public:
	SelfSpellAoe(SpellSlot slot);
	~SelfSpellAoe() = default;

public:
	virtual SpellType type() const { return SpellType::SelfAoe; }

	bool cast();

	bool isInRange(const Vector3& position) const;
	bool isInRange(IGameObject* target) const;

	bool castPrediction(IGameObject* target, Hitchance minHitchance = Hitchance::Instant);
	bool castMultiPrediction(int minTargets, Hitchance minimumHitchance = Hitchance::Instant, std::function<bool(IGameObject*)> filter = nullptr);

	PredictionInput getDefaultPredictionInput() const;

	IGameObject* target(float overrideRange = FLT_MAX, std::function<ObjectList(const ObjectList&)> filter = nullptr) const;

	float effectRange() const;
	void setEffectRange(float range);

private:
	float m_effectRange;
};

class RangedSpell : public SpellBase
{
public:
	RangedSpell(SpellSlot slot);
	~RangedSpell() = default;

public:
	virtual SpellType type() const { return SpellType::Ranged; }

	virtual bool isInRange(const Vector3& position) const;
	virtual bool isInRange(IGameObject* target) const;

	float range() const;
	float radius() const;
	float speed() const;
	float minMissileSpeed() const;
	float maxMissileSpeed() const;
	float missileAcceleration() const;
	bool useSourceBoundingRadiusRangeCheck() const;
	bool useTargetBoundingRadiusRangeCheck() const;
	const std::vector<Collisions>& collisions() const;
	size_t collisionCount() const;

	void setRange(float range);
	void setRadius(float radius);
	void setSpeed(float speed);
	void setMinMissileSpeed(float speed);
	void setMaxMissileSpeed(float speed);
	void setMissileAcceleration(float acceleration);
	void setUseSourceBoundingRadiusRangeCheck(bool use);
	void setUseTargetBoundingRadiusRangeCheck(bool use);
	void setCollisions(const std::vector<Collisions>& collisions);
	void setCollisionCount(size_t count);
	
	virtual IGameObject* target(float overrideRange = FLT_MAX, std::function<bool(IGameObject*)> filter = nullptr) const = 0;

protected:
	float m_range = 500;
	float m_radius = 1;
	float m_speed = FLT_MAX;
	float m_minMissileSpeed = FLT_MAX;
	float m_maxMissileSpeed = FLT_MAX;
	float m_missileAcceleration = FLT_MAX;
	bool m_useSourceBoundingRadiusRangeCheck = false;
	bool m_useTargetBoundingRadiusRangeCheck = false;
	
	std::vector<Collisions> m_collisions;
	size_t m_collisionCount = 1;
};

class TargetSpell : public RangedSpell
{
public:
	TargetSpell(SpellSlot slot);
	~TargetSpell() = default;

public:
	virtual SpellType type() const { return SpellType::Target; }

	bool cast(IGameObject* target);

	bool canHit(IGameObject* target);

	IGameObject* target(float overrideRange = FLT_MAX, std::function<bool(IGameObject*)> filter = nullptr) const override;
};

class PositionSpell : public RangedSpell
{
public:
	PositionSpell(SpellSlot slot);
	~PositionSpell() = default;
	
public:
	virtual SpellType type() const { return SpellType::Position; }

	bool isInRange(const Vector3& position) const override;
	virtual bool cast(const Vector3& position);
	virtual bool castPrediction(IGameObject* target, Hitchance minHitchance = Hitchance::Instant, bool castOnUnitPosition = false);
	virtual bool castMultiPrediction(int minTargets, Hitchance minimumHitchance = Hitchance::Instant, std::function<bool(IGameObject*)> filter = nullptr);

	bool canHit(IGameObject* target, Hitchance minHitchance = Hitchance::Instant);

	PredictionInput getDefaultPredictionInput() const;

	MultiPredictionInput getDefaultMultiPredictionInput(int minTargets, Hitchance minimumHitchance = Hitchance::Instant) const;

	IGameObject* target(float overrideRange = FLT_MAX, std::function<bool(IGameObject*)> filter = nullptr) const override;

public:
	SkillshotType skillshotType() const;
	bool boundingRadiusCollision() const;

	void setSkillshotType(SkillshotType type);
	void setBoundingRadiusCollision(bool f);

private:
	SkillshotType m_skillshotType = SkillshotType::Unknown;
	bool m_boundingRadiusCollision = true;
};

class DoublePositionSpell : public RangedSpell
{
public:
	DoublePositionSpell(SpellSlot slot);
	~DoublePositionSpell() = default;

public:
	virtual SpellType type() const { return SpellType::DoublePosition; }

	virtual bool cast(const Vector3& startPosition, const Vector3& endPosition);

	IGameObject* target(float overrideRange = FLT_MAX, std::function<bool(IGameObject*)> filter = nullptr) const override;
};

class DashSpell : public SpellBase
{
public:
	DashSpell(SpellSlot slot);
	~DashSpell() = default;

public:
	virtual SpellType type() const { return SpellType::Dash; }

	bool cast(const Vector3& position);
	bool cast(IGameObject* target, const Vector3& position);
	bool cast(IGameObject* target);

	DashType dashType() const;
	float range() const;
	float speed() const;

	void setDashType(DashType type);
	void setRange(float range);
	void setSpeed(float speed);

	bool useSourceBoundingRadiusRangeCheck() const;
	bool useTargetBoundingRadiusRangeCheck() const;

	void setUseSourceBoundingRadiusRangeCheck(bool use);
	void setUseTargetBoundingRadiusRangeCheck(bool use);

	bool isInRange(const Vector3& position) const;
	bool isInRange(IGameObject* target) const;

	bool canDashToPosition(const Vector3& position) const;

private:
	bool canUseDash(const Vector3& position) const;

private:
	DashType m_dashType;
	float m_range;
	float m_speed;
	bool m_useSourceBoundingRadiusRangeCheck = false;
	bool m_useTargetBoundingRadiusRangeCheck = false;
};

class ChargeableSpell : public PositionSpell
{
public:
	ChargeableSpell(SpellSlot slot);
	~ChargeableSpell() = default;

public:
	virtual SpellType type() const { return SpellType::Chargeable; }

	bool startChargeing(const Vector3& position = Vector3(0,0,0));
	bool startChargeingPrediction(IGameObject* target, Hitchance minHitchance = Hitchance::Instant);
	bool cast(const Vector3& position) override;
	bool castPrediction(IGameObject* target, Hitchance minHitchance = Hitchance::Instant, bool castOnUnitPosition = false) override;

	bool isChargeing() const;

	void setMaxChargeingTime(int time);
	int maxChargeingTime() const;

	void overrideIsChargeingFunction(std::function<bool()> func);

private:
	int m_maxChargeingTime;
	int m_lastStartTick;

	Vector3 m_lastCastPosition;

	std::function<bool()> m_overrideIsChargeingFunction;
};