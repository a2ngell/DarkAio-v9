#pragma once

#include <Windows.h>
#include <string>

struct ProjectionInfo;

class Vector2
{
public:
	float x, y;

	Vector2() = default;
	Vector2(float xx, float yy) : x(xx), y(yy) {}

	Vector2& operator+=(const Vector2& v);
	Vector2& operator+=(float fl);
	Vector2 operator+(const Vector2& v) const;
	Vector2 operator+(float mod) const;

	Vector2& operator-=(const Vector2& v);
	Vector2& operator-=(float fl);
	Vector2 operator-(const Vector2& v) const;
	Vector2 operator-(float mod) const;

	Vector2& operator*=(const Vector2& v);
	Vector2& operator*=(float s);
	Vector2 operator*(const Vector2& v) const;
	Vector2 operator*(float mod) const;

	Vector2& operator/=(const Vector2& v);
	Vector2& operator/=(float s);
	Vector2 operator/(const Vector2& v) const;
	Vector2 operator/(float mod) const;

	Vector2& operator=(const Vector2& v);
	Vector2& operator=(float mod);

	bool operator==(const Vector2& v) const;
	bool operator!=(const Vector2& v) const;

	float distance(const Vector2& v) const;
	float distanceSquared(const Vector2& v) const;

	std::string toString() const;

	bool isOnScreen(float tolerance = 0) const;

	Vector2 extend(const Vector2& to, float distance) const;

	float length() const;
	Vector2 normalized() const;

	float angleBetween(const Vector2& v) const;
	float dot(const Vector2& v) const;
	
	Vector2 perpendicular() const;

	Vector2 rotate(float angle, const Vector2& origin) const;
	Vector2 rotated(float angle) const;

	float magnitude() const;
	float magnitudeSquared() const;

	float dotProduct(const Vector2& other) const;

	Vector2 appendVector(const Vector2& other, float dist) const;

	ProjectionInfo projectOn(const Vector2& segmentStart, const Vector2& segmentEnd) const;

	Vector2 closestOnSegment(const Vector2& s1, const Vector2& s2) const;

	bool isWithinRange(float lower, float upper) const;

	Vector2 quantize() const;
};

struct ProjectionInfo
{
	bool isOnSegment;
	Vector2 LinePoint;
	Vector2 SegmentPoint;
};