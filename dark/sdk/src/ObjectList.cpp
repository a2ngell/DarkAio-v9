#include "ObjectList.h"
#include "SDK.h"

#include <algorithm>
#include <iterator>

ObjectList ObjectList::alive() const
{
	return this->filter([](IGameObject* obj)
		{
			return obj->isAlive();
		});
}

ObjectList ObjectList::dead() const
{
	return this->filter([](IGameObject* obj)
		{
			return !obj->isAlive();
		});
}

ObjectList ObjectList::allies() const
{
	return alliesFrom(g_localPlayer->team());
}

ObjectList ObjectList::enemies() const
{
	return enemiesFrom(g_localPlayer->team());
}

ObjectList ObjectList::alliesFrom(ObjectTeam team) const
{
	return filter([team](IGameObject* obj)
		{
			return obj->team() == team;
		});
}

ObjectList ObjectList::enemiesFrom(ObjectTeam team) const
{
	return filter([team](IGameObject* obj)
		{
			return obj->team() != team;
		});
}

ObjectList ObjectList::visible() const
{
	return filter([](IGameObject* obj)
		{
			return obj->isVisible();
		});
}

ObjectList ObjectList::targetable() const
{
	return filter([](IGameObject* obj)
		{
			return obj->isTargetable();
		});
}

ObjectList ObjectList::inAutoAttackRange(IGameObject* from, float additionalRange) const
{
	return filter([from, additionalRange](IGameObject* obj)
		{
			return from->isInAutoAttackRange(obj, additionalRange);
		});
}

IGameObject* ObjectList::byNetworkID(unsigned int networkID) const
{
	for (auto obj : *this)
	{
		if (obj->networkID() == networkID)
			return obj;
	}
	return nullptr;

}

ObjectList ObjectList::byName(const std::string& name) const
{
	return filter([&](IGameObject* obj)
		{
			return obj->name() == name;
		});
}

ObjectList ObjectList::byModelName(const std::string& modelName) const
{
	return filter([&](IGameObject* obj)
		{
			return obj->modelName() == modelName;
		});
}

ObjectList ObjectList::byChampionID(ChampionID championID) const
{
	return filter([&](IGameObject* obj)
		{
			return obj->championID() == championID;
		});
}

IGameObject* ObjectList::byIndex(unsigned short index) const
{
	for (auto obj : *this)
	{
		if (obj->index() == index)
			return obj;
	}
	return nullptr;
}

ObjectList ObjectList::onScreen() const
{
	return filter([](IGameObject* obj)
		{
			return obj->isOnScreen();
		});
}

ObjectList ObjectList::laneMinion() const
{
	ObjectList ret;
	std::copy_if(this->begin(), this->end(), std::back_inserter(ret), [](IGameObject* obj)
		{
			return obj->isLaneMinion();
		});
	return ret;
}

ObjectList ObjectList::jungleMinion() const
{
	ObjectList ret;
	std::copy_if(this->begin(), this->end(), std::back_inserter(ret), [](IGameObject* obj)
		{
			return obj->isJungleMonster();
		});
	return ret;
}

ObjectList ObjectList::filter(const std::function<bool(IGameObject*)>& predicate) const
{
	ObjectList ret;
	ret.reserve(this->size());
	for (auto obj : *this)
	{
		if (predicate(obj))
			ret.push_back(obj);
	}
	return ret;
}

ObjectList ObjectList::byType(ObjectType type) const
{
	return filter([type](IGameObject* obj)
		{
			return obj->type() == type;
		});
}

ObjectList ObjectList::byTeam(ObjectTeam team) const
{
	return filter([team](IGameObject* obj)
		{
			return obj->team() == team;
		});
}

ObjectList ObjectList::nearestTo(IGameObject* from) const
{
	if (this->empty())
		return ObjectList();

	auto nearest = [&](IGameObject* obj1, IGameObject* obj2)
	{
		return obj1->distance(from) < obj2->distance(from);
	};
	
	auto nearestObj = std::min_element(this->begin(), this->end(), nearest);
	
	return ObjectList({ *nearestObj });
}

ObjectList ObjectList::nearestTo(const Vector3& from) const
{
	if (this->empty())
		return ObjectList();

	auto nearest = [&](IGameObject* obj1, IGameObject* obj2)
	{
		return obj1->distance(from) < obj2->distance(from);
	};

	auto nearestObj = std::min_element(this->begin(), this->end(), nearest);
	return ObjectList({ *nearestObj });
}

ObjectList ObjectList::nearestTo(const Vector2& from) const
{
	if (this->empty())
		return ObjectList();

	auto nearest = [&](IGameObject* obj1, IGameObject* obj2)
	{
		return obj1->position().to2DVector().distance(from) < obj2->position().to2DVector().distance(from);
	};

	auto nearestObj = std::min_element(this->begin(), this->end(), nearest);
	return ObjectList({ *nearestObj });
}

ObjectList ObjectList::without(const ObjectList& list) const
{
	ObjectList ret;
	std::copy_if(this->begin(), this->end(), std::back_inserter(ret), [&](IGameObject* obj)
		{
			return std::find(list.begin(), list.end(), obj) == list.end();
		});
	return ret;
}

ObjectList ObjectList::without(IGameObject* object) const
{
	return without(object->networkID());
}

ObjectList ObjectList::without(int ID) const
{
	return filter([ID](IGameObject* obj)
		{
			return obj->networkID() != ID;
		});
}

ObjectList ObjectList::withoutMe()
{
	return filter([](IGameObject* obj)
		{
			return !obj->isMe();
		});
}

ObjectList ObjectList::inRange(IGameObject* from, float range, bool useTargetBoundingRadius) const
{
	return filter([&](IGameObject* obj)
		{
			return obj->distance(from) <= range + (useTargetBoundingRadius ? obj->boundingRadius() : 0);
		});
}

ObjectList ObjectList::inRange(const Vector3& from, float range) const
{
	return filter([&](IGameObject* obj)
		{
			return obj->distance(from) <= range;
		});
}
