#pragma once

class IGameObject;
class IHealthPrediction
{
public:
	virtual ~IHealthPrediction() = default;

public:
	virtual bool hasIncomingDamage(IGameObject* target, float time) = 0;

	virtual float getHealthPrediction(IGameObject* target, float time) = 0; //time between start and end
};