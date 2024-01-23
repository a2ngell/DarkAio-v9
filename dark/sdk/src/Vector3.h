#pragma once

#include <cmath>
#include <limits>

#include "Vector2.h"

class Vector3;
struct IntersectionResult
{
	bool intersects;
	Vector2 point;
};

class Vector3
{
public:
	float x, y, z;

	Vector3(float xx, float yy, float zz) : x(xx), y(yy), z(zz) {}
	Vector3(float xx, float zz) : x(xx), y(0), z(zz) {}
	Vector3();

	bool operator==(const Vector3& other) const;
	bool operator!=(const Vector3& other) const;
	bool operator<(const Vector3& other) const;
	bool operator>(const Vector3& other) const;

	Vector3& operator*=(const Vector3& v);
	Vector3& operator*=(float s);

	Vector3& operator/=(const Vector3& v);
	Vector3& operator/=(float s);

	Vector3& operator+=(const Vector3& v);
	Vector3& operator+=(float fl);

	Vector3& operator-=(const Vector3& v);
	Vector3& operator-=(float fl);

	Vector3 operator-(const Vector3& v) const;
	Vector3 operator-(float mod) const;

	Vector3 operator+(const Vector3& v) const;
	Vector3 operator+(float mod) const;

	Vector3 operator/(const Vector3& v) const;
	Vector3 operator/(float mod) const;
	Vector3 operator*(const Vector3& v) const;
	Vector3 operator*(float mod) const;

	Vector3& operator=(const Vector3& v);
	Vector3& operator=(float mod);

	float distance3D(const Vector3& v) const;
	float distance(const Vector3& v) const;
	float distanceSquared(const Vector3& v) const;

	Vector2 to2DVector() const;

	Vector2 toScreen(bool* isOnScreen = nullptr) const;
	bool isOnScreen(float tolerance = 0) const;

	std::string toString() const;

	float length() const;
	Vector3 normalized() const;

	float dot(const Vector3& other) const;
	Vector3 crossProduct(const Vector3& other) const;
	Vector3 perpendicular() const;
	Vector3 projectionOn(const Vector3& other) const;
	Vector3 sameDirectionAs(const Vector3& other) const;
	Vector3 to2D() const;
	float angleBetween(const Vector3& other) const;

	IntersectionResult intersection(const Vector3& lineSegmentEnd, const Vector3& lineSegment2Start, const Vector3& lineSegment2End) const;

	bool isInEnemyTowerRange(float additionalRange = 0) const;
	bool isInAllyTowerRange(float additionalRange = 0) const;

	Vector3 extend(const Vector3& to, float distance) const;

	bool isWithinRange(float lower, float upper) const;

	void adjustWorldY();
	Vector3 toWorld() const;
};
