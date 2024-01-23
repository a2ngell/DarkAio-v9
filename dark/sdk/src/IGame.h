#pragma once

#include "Enums.h"

class IGame
{
public:
	virtual ~IGame() = default;
	
public:
	virtual float gameTime() = 0;

	virtual float getPing() = 0;

	virtual int tickCount() = 0;

	virtual GameState gameState() = 0;

	virtual const char* translateString(const char* string) = 0;

	virtual bool isShopOpen() = 0;
};