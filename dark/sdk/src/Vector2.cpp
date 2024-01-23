#include <cmath>
#include "Vector2.h"

#include "SDK.h"

Vector2& Vector2::operator+=(const Vector2& v)
{
	this->x += v.x;
	this->y += v.y;
	return *this;
}

Vector2& Vector2::operator+=(float fl)
{
	this->x += fl;
	this->y += fl;
	return *this;
}

Vector2 Vector2::operator+(const Vector2& v) const
{
	Vector2 result(this->x + v.x, this->y + v.y);
	return result;
}

Vector2 Vector2::operator+(float mod) const
{
	Vector2 result(this->x + mod, this->y + mod);
	return result;
}

Vector2& Vector2::operator-=(const Vector2& v)
{
	this->x -= v.x;
	this->y -= v.y;
	return *this;
}

Vector2& Vector2::operator-=(float fl)
{
	this->x -= fl;
	this->y -= fl;
	return *this;
}

Vector2 Vector2::operator-(const Vector2& v) const
{
	Vector2 result(this->x - v.x, this->y - v.y);
	return result;
}

Vector2 Vector2::operator-(float mod) const
{
	Vector2 result(this->x - mod, this->y - mod);
	return result;
}

Vector2& Vector2::operator*=(const Vector2& v)
{
	this->x *= v.x;
	this->y *= v.y;
	return *this;
}

Vector2& Vector2::operator*=(float s)
{
	this->x *= s;
	this->y *= s;
	return *this;
}

Vector2 Vector2::operator*(const Vector2& v) const
{
	Vector2 result(this->x * v.x, this->y * v.y);
	return result;
}

Vector2 Vector2::operator*(float mod) const
{
	Vector2 result(this->x * mod, this->y * mod);
	return result;
}

Vector2& Vector2::operator/=(const Vector2& v)
{
	this->x /= v.x;
	this->y /= v.y;
	return *this;
}

Vector2& Vector2::operator/=(float s)
{
	this->x /= s;
	this->y /= s;
	return *this;
}

Vector2 Vector2::operator/(const Vector2& v) const
{
	Vector2 result(this->x / v.x, this->y / v.y);
	return result;
}

Vector2 Vector2::operator/(float mod) const
{
	Vector2 result(this->x / mod, this->y / mod);
	return result;
}

Vector2& Vector2::operator=(const Vector2& v)
{
	this->x = v.x;
	this->y = v.y;
	return *this;
}

Vector2& Vector2::operator=(float mod)
{
	this->x = mod;
	this->y = mod;
	return *this;
}

bool Vector2::operator==(const Vector2& v) const
{
	return this->x == v.x && this->y == v.y;
}

bool Vector2::operator!=(const Vector2& v) const
{
	return !(*this == v);
}

float Vector2::distance(const Vector2& v) const
{
	return (float)sqrt(pow(v.x - x, 2) + pow(v.y - y, 2));
}

float Vector2::distanceSquared(const Vector2& v) const
{
	return (float)(pow(v.x - x, 2) + pow(v.y - y, 2));
}

std::string Vector2::toString() const
{
	return std::string(xorstr_("x: ") + std::to_string(this->x) + xorstr_(" y: ") + std::to_string(this->y));
}

bool Vector2::isOnScreen(float tolerance) const
{
	return g_world->isOnScreen(*this, tolerance);
}

Vector2 Vector2::extend(const Vector2& to, float distance) const
{
	Vector2 result = (to - *this).normalized();
	result *= distance;
	result += *this;
	return result;
}

float Vector2::length() const
{
	return (float)sqrt(pow(x, 2) + pow(y, 2));
}

Vector2 Vector2::normalized() const
{
	float len = length();
	Vector2 result(x / len, y / len);
	return result;
}

#undef min 
#undef max

float Vector2::angleBetween(const Vector2& v) const
{
	double dotProduct = this->dot(v);
	double lengthsMultiplied = this->length() * v.length();
	double value = dotProduct / lengthsMultiplied;

	value = std::max(-1.0, std::min(1.0, value));

	return std::acos(value);
}

float Vector2::dot(const Vector2& v) const
{
	return x * v.x + y * v.y;
}

Vector2 Vector2::perpendicular() const
{
	return Vector2(-y, x);
}

Vector2 Vector2::rotate(float angle, const Vector2& origin) const
{
	float sinA = sin(angle);
	float cosA = cos(angle);

	Vector2 translatedPoint = *this - origin;

	Vector2 rotatedPoint(
		translatedPoint.x * cosA - translatedPoint.y * sinA,
		translatedPoint.x * sinA + translatedPoint.y * cosA
	);

	Vector2 newPoint = rotatedPoint + origin;
	return newPoint;
}

Vector2 Vector2::rotated(float angle) const
{
	float cosAngle = cos(angle);
	float sinAngle = sin(angle);

	return Vector2(
		x * cosAngle - y * sinAngle,
		x * sinAngle + y * cosAngle
	);
}

float Vector2::magnitude() const
{
	return std::sqrt(x * x + y * y);
}

float Vector2::magnitudeSquared() const
{
	return x * x + y * y;
}

float Vector2::dotProduct(const Vector2& other) const
{
	return x * other.x + y * other.y;
}

Vector2 Vector2::appendVector(const Vector2& other, float dist) const
{
	return other + (other - *this).normalized() * dist;
}

ProjectionInfo Vector2::projectOn(const Vector2& segmentStart, const Vector2& segmentEnd) const
{
	float rs;
	auto const cx = x;
	auto const cy = y;
	auto const ax = segmentStart.x;
	auto const ay = segmentStart.y;
	auto const bx = segmentEnd.x;
	auto const by = segmentEnd.y;

	const auto rl = ((cx - ax) * (bx - ax) + (cy - ay) * (by - ay)) / (pow(bx - ax, 2) + pow(by - ay, 2));
	const auto pointLine = Vector2(ax + rl * (bx - ax), ay + rl * (by - ay));

	if (rl < 0)
	{
		rs = 0;
	}
	else if (rl > 1)
	{
		rs = 1;
	}
	else
	{
		rs = rl;
	}

	auto const isOnSegment = rs == rl;
	auto const pointSegment = isOnSegment ? pointLine : Vector2(ax + rs * (bx - ax), ay + rs * (by - ay));

	return ProjectionInfo { isOnSegment, pointLine, pointSegment };
}

Vector2 Vector2::closestOnSegment(const Vector2& s1, const Vector2& s2) const
{
	Vector2 ap = *this - s1;
	Vector2 ab = s2 - s1;
	float t = ap.dot(ab) / (ab.x * ab.x + ab.y * ab.y);
	return t < 0 ? s1 : t > 1 ? s2 : (s1 + ab * t);
}

bool Vector2::isWithinRange(float lower, float upper) const
{
	return x > lower && x < upper &&
		y > lower && y < upper;
}

Vector2 Vector2::quantize() const
{
	return Vector2(std::round(x), std::round(y));
}
