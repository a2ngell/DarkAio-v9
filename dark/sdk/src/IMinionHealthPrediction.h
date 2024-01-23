#pragma once

class IGameObject;
class IMinionHealthPrediction
{
public:
	virtual ~IMinionHealthPrediction() = default;

public:
	virtual float getHealthPrediction(IGameObject* minion, float time) = 0; // time between start and end

	virtual int predictedMissileTravelTime(IGameObject* from, IGameObject* target, float speed) = 0;

	virtual int lastTurretAttackTick(IGameObject* turret) = 0; // cast tick of the attack

	virtual int lastTurretMinion(IGameObject* turret) = 0; // last minion targeted by turret

	virtual int lastAllyMinionTargetID(IGameObject* minion) = 0; // last ally lane minion target networkID

	virtual bool calculateExtraDamage(IGameObject* allyMinion) = 0;

};