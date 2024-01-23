#pragma once

#include "ObjectList.h"

class IGameObject;
class ITargetSelector
{
public:
	virtual ~ITargetSelector() = default;

public:
	virtual IGameObject* getTarget(const ObjectList& list, bool isAutoAttack = false, bool isTargetAction = true) = 0;
	virtual ObjectList getTargetsSorted(const ObjectList& list, bool isAutoAttack = false, bool isTargetAction = true) = 0;
	virtual IGameObject* getSelectedTarget() = 0;
};