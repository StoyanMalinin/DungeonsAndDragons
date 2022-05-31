#include "FightableEntity.h"

FightableEntity::FightableEntity(float strength, float mana, float health, const FightController& fc) : strength(strength), mana(mana), health(health), fc(fc.clone())
{}

bool FightableEntity::isAlive() const
{
	return health>0.0f;
}

void FightableEntity::setHealth(float health)
{
	if (health < 0) health = 0;
	this->health = health;
}

float FightableEntity::getStrength() const
{
	return strength;
}

float FightableEntity::getMana() const
{
	return mana;
}

float FightableEntity::getHealth() const
{
	return health;
}
