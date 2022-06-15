#ifndef __PLAYER_H
#define __PLAYER_H

#include "../../Utils/SharedPtr.hpp"
#include "../../Utils/String.h"

#include "MovableTileEntity.h"
#include "FightableEntity.h"

#include "Items/Armor.h"
#include "Items/Spell.h"
#include "Items/Weapon.h"
#include "Controllers/ItemManagerController.h"

class ItemExchangeMaster;
class FightMaster;

class Player : public MovableTileEntity, public FightableEntity
{
private:
	String name;
	SharedPtr <Spell> spell;
	SharedPtr <Armor> armor;
	SharedPtr <Weapon> weapon;

	SharedPtr<ItemManagerController> imc;
	ItemExchangeMaster &iem;

	float initialHealth;

public:
	Player(const String& name, int r, int c, float strength, float mana, float health, 
		   const FightController& fc, const ItemManagerController& imc, const MoveController& mc, 
		   ItemExchangeMaster &iem, FightMaster &fm);
protected:
	Player(const Player& other) = default;

public:
	bool canEnter() const override;
	Interactions getInteractionType() const override;
	char getSymbol() const override;

	void attack(FightableEntity& other) const override;
	void receiveDamage(float damage) override;
	void postBattleAction() override;

public:
	bool acquireSpell(SharedPtr<Spell> s);
	bool acquireArmor(SharedPtr<Armor> a);
	bool acquireWeapon(SharedPtr<Weapon> w);

public:
	const Spell* getSpell() const;
	const Armor* getArmor() const;
	const Weapon* getWeapon() const;

public:
	void interact(GameEntity* other) override;
	void interactInternal(GameEntity* other) override;
};

#endif
