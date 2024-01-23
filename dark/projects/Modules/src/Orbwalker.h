#pragma once

#include <SDK/src/SDK.h>

class Orbwalker : public IOrbwalker
{
public:
	Orbwalker() = default;
	~Orbwalker() = default;

public:
	IGameObject* getTarget() override;

	IGameObject* defaultGetComboTarget() override;
	IGameObject* defaultGetHarassTarget() override;
	IGameObject* defaultGetLaneClearTarget() override;
	IGameObject* defaultGetLastHitTarget() override;
	IGameObject* defaultGetJungleTarget() override;

	void overrideGetComboTarget(std::function<IGameObject* ()> fn) override;
	void overrideGetHarassTarget(std::function<IGameObject* ()> fn) override;
	void overrideGetLaneClearTarget(std::function<IGameObject* ()> fn) override;
	void overrideGetLastHitTarget(std::function<IGameObject* ()> fn) override;
	void overrideGetJungleTarget(std::function<IGameObject* ()> fn) override;

	IGameObject* lastTarget() override;
	Vector3 lastMovePosition() override;

	int lastAATick() override;
	int lastMoveTick() override;

	bool canAttack() override;
	bool canMove() override;

	float missileSpeed() override;
	void overrideMissileSpeed(std::function<float()> fn) override;

	void resetAA() override;
	void resetMove() override;

	void setBlockAttack(bool block) override;
	bool blockAttack() override;

	void setBlockMove(bool block) override;
	bool blockMove() override;

	bool isComboMode() override;
	bool isHarassMode() override;
	bool isLaneClearMode() override;
	bool isLastHitMode() override;
	bool isFleeMode() override;
	bool isAnyMode() override;

	bool isWindingUp() override;
	bool isWindingDown() override;

	void attack(IGameObject* target) override;
	void move(const Vector3& position) override;

	bool isJungleAOEClear() override;
	int lastKilledLaneMinion() override;

	float windingUpTimeLeft() override;
	float windingDownTimeLeft() override;

	bool isCastingSpell() override;

public:
	void onProcessSpell(OnProcessSpellEventArgs* args);
	void onUpdate(GameUpdateEventArgs* args);
};