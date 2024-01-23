#pragma once

#include <Windows.h>

#include "Enums.h"

typedef uintptr_t tLeagueScreenBuffer;

class IGameObject;
class IRenderer
{
public:
	virtual ~IRenderer() = default;

public:
	virtual unsigned int screenWidth() = 0;

	virtual unsigned int screenHeight() = 0;

	virtual EngineType engineType() = 0;

	virtual Vector2 screenStart() = 0;
	
	virtual Vector2 screenEnd() = 0;

	virtual Vector2 calculateScreenEdgeIntersection(const Vector2& start, const Vector2& end) = 0;

	// Use this only inside onRenderMouseOvers
	virtual bool renderGlowEffect(tLeagueScreenBuffer screenBufferPtr, IGameObject* unit, int color, int width, int glowAccuracy) = 0;
};