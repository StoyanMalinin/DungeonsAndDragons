#ifndef __FIGHTABLEENTITY_H
#define __FIGHTABLEENTITY_H

#include "Controllers/FightController.h"
#include "../../Utils/SharedPtr.hpp"
#include "GameEntity.h"

#include <iostream>

class FightMaster;

class FightableEntity : public virtual GameEntity
{
private:
	float strength, mana, health;

protected:
	SharedPtr<FightController> fc;
	FightMaster& fm;

public:
	FightableEntity(float strength, float mana, float health, const FightController& fc, FightMaster &fm);
protected:
	FightableEntity(const FightableEntity& other) = default;
public:
	FightableEntity& operator=(FightableEntity& other) = delete;

public:
	virtual void attack(FightableEntity& other) const = 0;
	virtual void receiveDamage(float damage) = 0;
	virtual void postBattleAction();
	bool isAlive() const;

protected:
	void setHealth(float health);
	void setStregth(float strength);
	void setMana(float mana);

public:
	float getStrength() const;
	float getMana() const;
	float getHealth() const;

public:
	void interact(GameEntity* other) override;
	virtual void interactInternal(FightableEntity* other);

public:
	virtual void write(std::ostream& os) const;
	void writeln(std::ostream& os) const;

public:
	virtual ~FightableEntity();
};

#endif // !__FIGHTABLEENTITY_H