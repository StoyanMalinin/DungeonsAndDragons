#ifndef __OPTIMALITEMMANAGERCONTROLLER_H
#define __OPTIMALITEMMANAGERCONTROLLER_H

#include "Spell.h"
#include "Armor.h"
#include "Weapon.h"
#include "SharedPtr.hpp"
#include "ItemManagerController.h"

class OptimalItemManagerController : public ItemManagerController
{
public:
	OptimalItemManagerController();
protected:
	OptimalItemManagerController(const OptimalItemManagerController& other);
public:
	OptimalItemManagerController& operator =(const OptimalItemManagerController& other) = delete;

public:
	bool acquireSpell(SharedPtr<Spell> oldSpell, SharedPtr<Spell> newSpell) override;
	bool acquireArmor(SharedPtr<Armor> oldArmor, SharedPtr<Armor> newArmor) override;
	bool acquireWeapon(SharedPtr<Weapon> oldWeapon, SharedPtr<Weapon> newWeapon) override;

public:
	ItemManagerController* clone() const override;
};

#endif // !__ITEMMANAGERCONTROLLER_H

