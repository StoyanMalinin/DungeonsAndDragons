#ifndef __FIGHTABLEENTITY_H
#define __FIGHTABLEENTITY_H

#include "Controllers/FightController.h"
#include "../../Utils/SharedPtr.hpp"
#include "GameEntity.h"

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
	bool isAlive() const;

protected:
	void setHealth(float health);

public:
	float getStrength() const;
	float getMana() const;
	float getHealth() const;

protected:
	void interact(GameEntity* other) override;
	virtual void interactInternal(FightableEntity* other);

public:
	virtual ~FightableEntity();
};

#endif // !__FIGHTABLEENTITY_H