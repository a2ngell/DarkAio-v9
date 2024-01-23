#pragma once

#include "Vector3.h"
#include "Enums.h"
#include "ICollision.h"
#include "ObjectList.h"

#include <unordered_map>
#include <functional>

class IGameObject;

struct PredictionInput
{
	Vector3 from;
	Vector3 rangeCheckFrom;

	float delay = 0.f;
	float radius = 1.f;
	float range = 25000.f;

	float missileSpeed = FLT_MAX;
	float minMissileSpeed = FLT_MAX;
	float maxMissileSpeed = FLT_MAX;
	float missileAcceleration = FLT_MAX;

	std::function<float(const Vector2& from, const Vector2& to, const PredictionInput& input, bool usePing, bool useBoundingRadius)> overrideTimeToHit = nullptr;

	SkillshotType type;

	IGameObject* caster;
	IGameObject* target;

	bool useBoundingRadius = true;
	size_t collisionCount = 1;
	std::vector<Collisions> collisions;
};

struct PredictionOutput
{
	PredictionInput input;
	Hitchance hitchance = Hitchance::Impossible;
	
	Vector3 castPosition;
	Vector3 unitPosition;

	std::vector<IGameObject*> aoeTargetHit;
	std::vector<CollisionPoint> collisionPoints;

	bool isHitchanceMatching(Hitchance expected)
	{
		return static_cast<int>(hitchance) >= static_cast<int>(expected);
	}
};

struct FastPredictionResult
{
	bool isMoving;
	Vector3 predictedPosition;
};

struct MultiPredictionInput
{
	Vector3 from;
	Vector3 rangeCheckFrom;

	float delay = 0.f;
	float radius = 1.f;
	float range = 25000.f;
	float missileSpeed = FLT_MAX;
	float minMissileSpeed = FLT_MAX;
	float maxMissileSpeed = FLT_MAX;
	float missileAcceleration = FLT_MAX;

	std::function<float(const Vector2& from, const Vector2& to, const PredictionInput& input, bool usePing, bool useBoundingRadius)> overrideTimeToHit = nullptr;

	SkillshotType type;

	IGameObject* caster;

	int minimumTargets = 1;
	Hitchance minimumHitchance = Hitchance::Instant;

	bool useBoundingRadius = true;
	size_t collisionCount = 1;
	std::vector<Collisions> collisions;

	std::function<bool(IGameObject*)> additionalTargetFilter = nullptr;
};

struct MultiPredictionOutput
{
	bool isValid = false;
	int targetCount = 0;

	Vector3 castPosition = Vector3(0, 0, 0);
};

class IPrediction
{
public:
	virtual ~IPrediction() = default;
	
public:
	virtual PredictionOutput getPrediction(const PredictionInput& input) = 0;

	virtual FastPredictionResult getFastPrediction(const Vector3& from, IGameObject* target, float delay, float speed) = 0;

	virtual MultiPredictionOutput getMultiPrediction(const MultiPredictionInput& input) = 0;

	virtual MultiPredictionOutput getFastMultiPrediction(const ObjectList& targets, const MultiPredictionInput& input) = 0;
};