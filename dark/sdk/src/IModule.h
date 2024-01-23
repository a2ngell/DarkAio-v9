#pragma once

#include "Enums.h"

class IModule
{
public:
	virtual ~IModule() = default;

public:
	virtual void load() = 0;
	virtual void unload() = 0;
	virtual ModuleType type() const = 0;
};