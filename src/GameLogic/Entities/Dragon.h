#ifndef __DRAGON_H
#define __DRAGON_H

#include "Items/Armor.h"
#include "TileEntity.h"
#include "FightableEntity.h"

#include "Controllers/FightController.h"

class FightMaster;

class Dragon : public TileEntity, public FightableEntity
{
private:
	Armor armor;

public:
	Dragon(int r, int c, float strength, float mana, float health, const FightController& fc, FightMaster &fm);
protected:
	Dragon(const Dragon& other) = default;

public:
	bool canEnter() const override;
	Interactions getInteractionType() const override;
	char getSymbol() const override;

	void attack(FightableEntity& other) const override;
	void receiveDamage(float damage) override;

public:
	void interact(GameEntity* other) override;
	void interactInternal(GameEntity* other) override;

public:
	void write(std::ostream& os) const override;

public:
	void serialize(std::ostream& stream) const override;
	TileEntity* clone() const override;
};

#endif

