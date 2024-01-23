#pragma once

#include <functional>

class IOrbwalker
{
public:
	virtual ~IOrbwalker() = default;

public:
	virtual IGameObject* getTarget() = 0;
	virtual IGameObject* defaultGetComboTarget() = 0;
	virtual IGameObject* defaultGetHarassTarget() = 0;
	virtual IGameObject* defaultGetLaneClearTarget() = 0;
	virtual IGameObject* defaultGetLastHitTarget() = 0;
	virtual IGameObject* defaultGetJungleTarget() = 0;

	virtual void overrideGetComboTarget(std::function<IGameObject* ()> fn) = 0;
	virtual void overrideGetHarassTarget(std::function<IGameObject* ()> fn) = 0;
	virtual void overrideGetLaneClearTarget(std::function<IGameObject* ()> fn) = 0;
	virtual void overrideGetLastHitTarget(std::function<IGameObject* ()> fn) = 0;
	virtual void overrideGetJungleTarget(std::function<IGameObject* ()> fn) = 0;
	
	virtual IGameObject* lastTarget() = 0;
	virtual Vector3 lastMovePosition() = 0;

	virtual int lastAATick() = 0;
	virtual int lastMoveTick() = 0;

	virtual float missileSpeed() = 0;
	virtual void overrideMissileSpeed(std::function<float()> fn) = 0;

	virtual bool canAttack() = 0;
	virtual bool canMove() = 0;

	virtual void resetAA() = 0;
	virtual void resetMove() = 0;

	virtual void setBlockAttack(bool block) = 0;
	virtual bool blockAttack() = 0;

	virtual void setBlockMove(bool block) = 0;
	virtual bool blockMove() = 0;

	virtual bool isComboMode() = 0;
	virtual bool isHarassMode() = 0;
	virtual bool isLaneClearMode() = 0;
	virtual bool isLastHitMode() = 0;
	virtual bool isFleeMode() = 0;
	virtual bool isAnyMode() = 0;

	virtual bool isWindingUp() = 0;
	virtual bool isWindingDown() = 0;

	virtual void attack(IGameObject* target) = 0;
	virtual void move(const Vector3& position) = 0;

	virtual bool isJungleAOEClear() = 0;

	virtual int lastKilledLaneMinion() = 0; // networkID

	virtual float windingUpTimeLeft() = 0;
	virtual float windingDownTimeLeft() = 0;

	virtual bool isCastingSpell() = 0;
};