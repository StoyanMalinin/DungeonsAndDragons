#ifndef __PLAYER_H
#define __PLAYER_H

#include "String.h"
#include "TileEntity.h"
#include "SharedPtr.hpp"
#include "FightableEntity.h"

#include "Armor.h"
#include "Spell.h"
#include "Weapon.h"
#include "ItemManagerController.h"

class Player : public TileEntity, public FightableEntity
{
private:
	String name;
	SharedPtr <Spell> spell;
	SharedPtr <Armor> armor;
	SharedPtr <Weapon> weapon;
	SharedPtr<ItemManagerController> imc;

public:
	Player(const String& name, int r, int c, float strength, float mana, float health, const FightController& fc, const ItemManagerController& imc);

public:
	bool canEnter() const override;
	Interactions getInteractionType() const override;

	void attack(FightableEntity& other) const override;
	void receiveDamage(float damage) override;

public:
	bool acquireSpell(SharedPtr<Spell> s);
	bool acquireArmor(SharedPtr<Armor> a);
	bool acquireWeapon(SharedPtr<Weapon> w);
};

#endif
