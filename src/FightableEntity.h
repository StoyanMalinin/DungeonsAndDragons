#ifndef __FIGHTABLEENTITY_H
#define __FIGHTABLEENTITY_H

#include "FightController.h"
#include "SharedPtr.hpp"

class FightableEntity
{
private:
	float strength, mana, health;

protected:
	SharedPtr<FightController> fc;

public:
	FightableEntity(float strength, float mana, float health, const FightController& fc);
protected:
	FightableEntity(const FightableEntity& other) = default;

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

public:
	virtual ~FightableEntity();
};

#endif // !__FIGHTABLEENTITY_H