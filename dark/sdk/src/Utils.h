#pragma once

#include <string>
#include <vector>
#include <string_view>
#include <sstream>
#include <algorithm>

#include "Vector3.h"

namespace Utils
{
	struct VectorMovementCollisionResult
	{
		float t1;
		bool isValid;
		Vector2 position;
	};

	std::string randomString(size_t length);
	std::string ptrToHex(uintptr_t ptr);
	std::vector<std::string> split(const std::string& s, char delimiter);
	std::string toLower(std::string_view string);
	VectorMovementCollisionResult vectorMovementCollision(const Vector2& startPoint1, const Vector2& endPoint, float v1, const Vector2& startPoint2, float v2, float delay);
	std::vector<Vector3> circlePoints(const Vector3& from, float radius, int points, bool isWallValid = false);
}