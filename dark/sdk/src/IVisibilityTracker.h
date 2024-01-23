#pragma once

#include <optional>

struct VisibilityData
{
	int stateSinceTick;
	bool isVisible;
};

class IVisibilityTracker
{
public:
	virtual ~IVisibilityTracker() = default;
	
public:
	virtual std::optional<VisibilityData> getVisibilityData(int networkId) const = 0;
};