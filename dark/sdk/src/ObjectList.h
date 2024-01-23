#pragma once

#include "IGameObject.h"

#include "Vector2.h"
#include "Vector3.h"

#include <vector>
#include <functional>

class ObjectList : public std::vector<IGameObject*>
{
public:
	using std::vector<IGameObject*>::vector;
	~ObjectList() = default;

	ObjectList alive() const;
	ObjectList dead() const;
	ObjectList allies() const;
	ObjectList enemies() const;
	ObjectList alliesFrom(ObjectTeam team) const;
	ObjectList enemiesFrom(ObjectTeam team) const;
	ObjectList visible() const;
	ObjectList targetable() const;
	ObjectList inAutoAttackRange(IGameObject* from, float additionalRange = 0) const;
	IGameObject* byNetworkID(unsigned int networkID) const;
	ObjectList byName(const std::string& name) const;
	ObjectList byModelName(const std::string& modelName) const;
	ObjectList byChampionID(ChampionID championID) const;
	IGameObject* byIndex(unsigned short index) const;
	ObjectList onScreen() const;
	ObjectList laneMinion() const;
	ObjectList jungleMinion() const;
	ObjectList filter(const std::function<bool(IGameObject*)>& predicate) const;
	ObjectList byType(ObjectType type) const;
	ObjectList byTeam(ObjectTeam team) const;
	ObjectList nearestTo(IGameObject* from) const;
	ObjectList nearestTo(const Vector3& from) const;
	ObjectList nearestTo(const Vector2& from) const;
	ObjectList without(const ObjectList& list) const;
	ObjectList without(IGameObject* object) const;
	ObjectList without(int ID) const;
	ObjectList withoutMe();
	ObjectList inRange(IGameObject* from, float range, bool useTargetBoundingRadius = false) const;
	ObjectList inRange(const Vector3& from, float range) const;
};