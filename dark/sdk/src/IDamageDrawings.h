#pragma once

#include <Windows.h>

class IGameObject;
class IDamageDrawings
{
public:
	virtual ~IDamageDrawings() = default;

public:
	virtual void drawDamage(IGameObject* target, float damage) = 0;
};