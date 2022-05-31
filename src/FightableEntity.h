#ifndef __FIGHTABLEENTITY_H
#define __FIGHTABLEENTITY_H

#include "FightController.h"

class FightableEntity
{
private:
	float strength, mana, health;

protected:
	FightController* fc;

public:
	FightableEntity(float strength, float mana, float health, const FightController& fc);

public:
	virtual void attack(FightableEntity& other) const = 0;
	virtual void receiveDamage(float damage) = 0;
	bool isAlive() const;

protected:
	void setHealth(float health);

public:
	float getStrength() const;
	float getMana() const;
	float getHealth() const;
};

#endif // !__FIGHTABLEENTITY_H