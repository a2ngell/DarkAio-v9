#pragma once

#include <vector>
#include "Vector3.h"

class IEvade
{
public:
	virtual ~IEvade() = default;

public:
	virtual bool isSafePath(const std::vector<Vector3>& path, float delay, float speed) const = 0;
	virtual bool isSafeToBlink(const Vector3& position, float delay) const = 0;
};