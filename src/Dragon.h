#ifndef __DRAGON_H
#define __DRAGON_H

#include "TileEntity.h"
#include "FightableEntity.h"

#include "FightController.h"

#include "Armor.h"

class Dragon : public TileEntity, public FightableEntity
{
private:
	Armor armor;

public:
	Dragon(int r, int c, float strength, float mana, float health, const FightController& fc);

public:
	bool canEnter() const override;
	Interactions getInteractionType() const override;
	char getSymbol() const override;

	void attack(FightableEntity& other) const override;
	void receiveDamage(float damage) override;
};

#endif

