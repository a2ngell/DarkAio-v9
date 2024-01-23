#include "Orbwalker.h"

IGameObject* Orbwalker::getTarget()
{
	return nullptr;
}

IGameObject* Orbwalker::defaultGetComboTarget()
{
	return nullptr;
}

IGameObject* Orbwalker::defaultGetHarassTarget()
{
	return nullptr;
}

IGameObject* Orbwalker::defaultGetLaneClearTarget()
{
	return nullptr;
}

IGameObject* Orbwalker::defaultGetLastHitTarget()
{
	return nullptr;
}

IGameObject* Orbwalker::defaultGetJungleTarget()
{
	return nullptr;
}

void Orbwalker::overrideGetComboTarget(std::function<IGameObject* ()> fn)
{
}

void Orbwalker::overrideGetHarassTarget(std::function<IGameObject* ()> fn)
{
}

void Orbwalker::overrideGetLaneClearTarget(std::function<IGameObject* ()> fn)
{
}

void Orbwalker::overrideGetLastHitTarget(std::function<IGameObject* ()> fn)
{
}

void Orbwalker::overrideGetJungleTarget(std::function<IGameObject* ()> fn)
{
}

IGameObject* Orbwalker::lastTarget()
{
	return nullptr;
}

Vector3 Orbwalker::lastMovePosition()
{
	return Vector3();
}

int Orbwalker::lastAATick()
{
	return 0;
}

int Orbwalker::lastMoveTick()
{
	return 0;
}

bool Orbwalker::canAttack()
{
	return false;
}

bool Orbwalker::canMove()
{
	return false;
}

float Orbwalker::missileSpeed()
{
	return 0.0f;
}

void Orbwalker::overrideMissileSpeed(std::function<float()> fn)
{
}

void Orbwalker::resetAA()
{
}

void Orbwalker::resetMove()
{
}

void Orbwalker::setBlockAttack(bool block)
{
}

bool Orbwalker::blockAttack()
{
	return false;
}

void Orbwalker::setBlockMove(bool block)
{
}

bool Orbwalker::blockMove()
{
	return false;
}

bool Orbwalker::isComboMode()
{
	return false;
}

bool Orbwalker::isHarassMode()
{
	return false;
}

bool Orbwalker::isLaneClearMode()
{
	return false;
}

bool Orbwalker::isLastHitMode()
{
	return false;
}

bool Orbwalker::isFleeMode()
{
	return false;
}

bool Orbwalker::isAnyMode()
{
	return false;
}

bool Orbwalker::isWindingUp()
{
	return false;
}

bool Orbwalker::isWindingDown()
{
	return false;
}

void Orbwalker::attack(IGameObject* target)
{
}

void Orbwalker::move(const Vector3& position)
{
}

bool Orbwalker::isJungleAOEClear()
{
	return false;
}

int Orbwalker::lastKilledLaneMinion()
{
	return 0;
}

float Orbwalker::windingUpTimeLeft()
{
	return 0.0f;
}

float Orbwalker::windingDownTimeLeft()
{
	return 0.0f;
}

bool Orbwalker::isCastingSpell()
{
	return false;
}

void Orbwalker::onProcessSpell(OnProcessSpellEventArgs* args)
{
}

void Orbwalker::onUpdate(GameUpdateEventArgs* args)
{
}
