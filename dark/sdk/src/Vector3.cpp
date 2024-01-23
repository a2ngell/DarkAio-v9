#include <cmath>
#include <algorithm>
#include "SDK.h"

#include "Vector3.h"

Vector3::Vector3()
{
	this->x = 0; this->y = 0; this->z = 0;
}

bool Vector3::operator==(Vector3 const& other) const
{
	return other.x == this->x && other.y == this->y && other.z == this->z;
}

bool Vector3::operator!=(Vector3 const& other) const {
	return !(other.x == this->x && other.y == this->y && other.z == this->z);
}

bool Vector3::operator<(const Vector3& other) const {
	if (x < other.x) return true;
	if (x > other.x) return false;
	if (y < other.y) return true;
	if (y > other.y) return false;
	return z < other.z;
}

bool Vector3::operator>(const Vector3& other) const {
	if (x > other.x) return true;
	if (x < other.x) return false;
	if (y > other.y) return true;
	if (y < other.y) return false;
	return z > other.z;
}

Vector3& Vector3::operator*=(const Vector3& v)
{
	this->x *= v.x;
	this->y *= v.y;
	this->z *= v.z;
	return *this;
}

Vector3& Vector3::operator*=(float s)
{
	this->x *= s;
	this->y *= s;
	this->z *= s;
	return *this;
}

Vector3& Vector3::operator/=(const Vector3& v)
{
	this->x /= v.x;
	this->y /= v.y;
	this->z /= v.z;
	return *this;
}

Vector3& Vector3::operator/=(float s)
{
	this->x /= s;
	this->y /= s;
	this->z /= s;
	return *this;
}

Vector3& Vector3::operator+=(const Vector3& v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	return *this;
}

Vector3& Vector3::operator+=(float fl)
{
	this->x += fl;
	this->y += fl;
	this->z += fl;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	return *this;
}

Vector3& Vector3::operator-=(float fl)
{
	this->x -= fl;
	this->y -= fl;
	this->z -= fl;
	return *this;
}

Vector3 Vector3::operator-(const Vector3& v) const
{
	Vector3 result(this->x - v.x, this->y - v.y, this->z - v.z);
	return result;
}

Vector3 Vector3::operator-(float mod) const
{
	Vector3 result(this->x - mod, this->y - mod, this->z - mod);
	return result;
}

Vector3 Vector3::operator+(const Vector3& v) const
{
	Vector3 result(this->x + v.x, this->y + v.y, this->z + v.z);
	return result;
}

Vector3 Vector3::operator+(float mod) const
{
	Vector3 result(this->x + mod, this->y + mod, this->z + mod);
	return result;
}

Vector3 Vector3::operator/(const Vector3& v) const
{
	Vector3 result(this->x / v.x, this->y / v.y, this->z / v.z);
	return result;
}

Vector3 Vector3::operator/(float mod) const
{
	Vector3 result(this->x / mod, this->y / mod, this->z / mod);
	return result;
}

Vector3 Vector3::operator*(const Vector3& v) const
{
	Vector3 result(this->x * v.x, this->y * v.y, this->z * v.z);
	return result;
}

Vector3 Vector3::operator*(float mod) const
{
	Vector3 result(this->x * mod, this->y * mod, this->z * mod);
	return result;
}

Vector3& Vector3::operator=(const Vector3& v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	return *this;
}

Vector3& Vector3::operator=(float mod)
{
	this->x = mod;
	this->y = mod;
	this->z = mod;
	return *this;
}

float Vector3::distance3D(const Vector3& v) const
{
	return (float)sqrt(pow(v.x - x, 2) + pow(v.z - z, 2) + pow(v.y - y, 2));
}

float Vector3::distance(const Vector3& v) const
{
	return (float)sqrt(pow(v.x - x, 2) + pow(v.z - z, 2));
}

float Vector3::distanceSquared(const Vector3& v) const
{
	return (float)(pow(v.x - x, 2) + pow(v.z - z, 2));
}

Vector2 Vector3::to2DVector() const
{
	return Vector2(this->x, this->z);
}

Vector2 Vector3::toScreen(bool* isOnScreen) const
{
	return g_world->w2s(*this, isOnScreen);
}

std::string Vector3::toString() const
{
	return std::string(xorstr_("x: ") + std::to_string(this->x) + xorstr_(" y: ") + std::to_string(this->y) + xorstr_(" z: ") + std::to_string(this->z));
}

float Vector3::length() const
{
	return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
}

Vector3 Vector3::normalized() const
{
	auto const length = this->length();
	if (length != 0)
	{
		auto const inv = 1.0f / length;
		return { this->x * inv, this->y * inv, this->z * inv };
	}

	return *this;
}

float Vector3::dot(const Vector3& other) const
{
	return (x * other.x + y * other.y + z * other.z);
}

Vector3 Vector3::crossProduct(const Vector3& other) const
{
	Vector3 n;

	n.x = x * other.z - z * other.y;
	n.y = z * other.x - x * other.z;
	n.z = x * other.y - y * other.x;

	return n;
}

Vector3 Vector3::perpendicular() const
{
	return Vector3(z, y, -x);
}

Vector3 Vector3::projectionOn(const Vector3& other) const
{
	Vector3 toProject = Vector3(x, y, z);
	float scale = (toProject.dot(other)) / (other.dot(other));
	return other * scale;
}

Vector3 Vector3::sameDirectionAs(const Vector3& other) const
{
	return other.normalized() * length();
}

Vector3 Vector3::to2D() const
{
	return Vector3(this->x, 0, this->z);
}

#undef min
#undef max

float Vector3::angleBetween(const Vector3& other) const
{
	auto u = this->normalized();
	auto v = other.normalized();
	double dotProduct = u.dot(v);

	dotProduct = std::max(-1.0, std::min(1.0, dotProduct));
	return std::acos(dotProduct);
}

IntersectionResult Vector3::intersection(const Vector3& lineSegmentEnd, const Vector3& lineSegment2Start, const Vector3& lineSegment2End) const
{
	const Vector2 side1 = { lineSegmentEnd.x - this->x, lineSegmentEnd.y - this->y };
	const Vector2 side2 = { lineSegment2End.x - lineSegment2Start.x, lineSegment2End.y - lineSegment2Start.y };

	const auto s = (-side1.y * (this->x - lineSegment2Start.x) + side1.x * (this->y - lineSegment2Start.y)) / (-side2.x * side1.y + side1.x * side2.y);
	const auto t = (side2.x * (this->y - lineSegment2Start.y) - side2.y * (this->x - lineSegment2Start.x)) / (-side2.x * side1.y + side1.x * side2.y);

	if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
		return { true,{ this->x + t * side1.x,  this->y + t * side1.y } };

	return { false,{} };
}

bool Vector3::isInEnemyTowerRange(float additionalRange) const
{
	auto enemyTower = g_objectManager->turrets().alive().enemies();
	for (auto p : enemyTower)
	{
		if (this->distance(p->position()) < 780 + p->boundingRadius() + additionalRange)
			return true;
	}
	return false;
}

bool Vector3::isInAllyTowerRange(float additionalRange) const
{
	auto allyTower = g_objectManager->turrets().alive().allies();
	for (auto p : allyTower)
	{
		if (this->distance(p->position()) < 780 + p->boundingRadius() + additionalRange)
			return true;
	}
	return false;
}

bool Vector3::isOnScreen(float tolerance) const
{
	return g_world->isOnScreen(*this, tolerance);
}

Vector3 Vector3::extend(const Vector3& to, float distance) const
{
	return *this + (to - *this).normalized() * distance;
}

bool Vector3::isWithinRange(float lower, float upper) const
{
	return x > lower && x < upper &&
		y > lower && y < upper &&
		z > lower && z < upper;
}

void Vector3::adjustWorldY()
{
	y = g_navMesh->heightForPosition(x, z);
}

Vector3 Vector3::toWorld() const
{
	return Vector3(x, g_navMesh->heightForPosition(x, z), z);
}
