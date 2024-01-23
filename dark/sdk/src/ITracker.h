#pragma once

#include "IVisibilityTracker.h"

class ITracker
{
public:
	virtual ~ITracker() = default;

public:
	virtual std::shared_ptr<IVisibilityTracker> getVisibilityTracker() const = 0;
};