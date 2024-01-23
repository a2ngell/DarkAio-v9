#pragma once

#include "Enums.h"

class ObjectList;
class IGameObject;
class IObjectManager
{
public:
	virtual ~IObjectManager() = default;
	
public:
	virtual IGameObject* localPlayer() = 0;

	virtual ObjectList objects() = 0;

	virtual IGameObject* object(unsigned short index) = 0;

	virtual IGameObject* objectByNetworkID(unsigned int networkID) = 0;

	virtual ObjectList byType(ObjectType type) = 0;
	
	virtual ObjectList players() = 0;

	virtual ObjectList turrets() = 0;
	
	virtual ObjectList minions() = 0;

	virtual ObjectList missiles() = 0;

	virtual ObjectList troys() = 0;
	
	virtual ObjectList spawnPoints() = 0;

	virtual ObjectList shops() = 0;

	virtual ObjectList inhibitors() = 0;

	virtual ObjectList hqs() = 0;

	virtual IGameObject* neutralCampByID(NeutralCampID id) = 0;
};