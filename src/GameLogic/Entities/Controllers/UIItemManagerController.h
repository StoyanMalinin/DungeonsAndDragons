#ifndef __UIITEMMANAGERCONTROLLER_H
#define __UIITEMMANAGERCONTROLLER_H

class UIHandler;
#include "ItemManagerController.h"

class UIItemManagerController : public ItemManagerController
{
private:
	UIHandler &uih;

public:
	UIItemManagerController(UIHandler& uih);

public:
	bool acquireSpell(SharedPtr<Spell> oldSpell, SharedPtr<Spell> newSpell) override;
	bool acquireArmor(SharedPtr<Armor> oldArmor, SharedPtr<Armor> newArmor) override;
	bool acquireWeapon(SharedPtr<Weapon> oldWeapon, SharedPtr<Weapon> newWeapon) override;

public:
	ItemManagerController* clone() const override;
};

#endif // !__UIITEMMANAGERCONTROLLER_H
