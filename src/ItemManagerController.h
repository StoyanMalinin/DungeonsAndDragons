#ifndef __ITEMMANAGERCONTROLLER_H
#define __ITEMMANAGERCONTROLLER_H

#include "Spell.h"
#include "Armor.h"
#include "Weapon.h"
#include "SharedPtr.hpp"

class ItemManagerController
{
public:
	ItemManagerController();
protected:
	ItemManagerController(const ItemManagerController& other);
public:
	ItemManagerController& operator =(const ItemManagerController& other) = delete;

public:
	virtual bool acquireSpell(SharedPtr<Spell> oldSpell, SharedPtr<Spell> newSpell) = 0;
	virtual bool acquireArmor(SharedPtr<Armor> oldArmor, SharedPtr<Armor> newArmor) = 0;
	virtual bool acquireWeapon(SharedPtr<Weapon> oldWeapon, SharedPtr<Weapon> newWeapon) = 0;

public:
	virtual ItemManagerController* clone() const = 0;

public:
	virtual ~ItemManagerController();
};

#endif // !__ITEMMANAGERCONTROLLER_H
