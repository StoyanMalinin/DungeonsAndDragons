#include "UIItemManagerController.h"

UIItemManagerController::UIItemManagerController(UIHandler& uih) :uih(uih)
{}

bool UIItemManagerController::acquireSpell(SharedPtr<Spell> oldSpell, SharedPtr<Spell> newSpell)
{
	return (uih.requestItemManagementDecision(oldSpell.getRaw(), newSpell.getRaw())=='y');
}

bool UIItemManagerController::acquireArmor(SharedPtr<Armor> oldArmor, SharedPtr<Armor> newArmor)
{
	return (uih.requestItemManagementDecision(oldArmor.getRaw(), newArmor.getRaw()) == 'y');
}

bool UIItemManagerController::acquireWeapon(SharedPtr<Weapon> oldWeapon, SharedPtr<Weapon> newWeapon)
{
	return (uih.requestItemManagementDecision(oldWeapon.getRaw(), newWeapon.getRaw()) == 'y');
}

ItemManagerController* UIItemManagerController::clone() const
{
	return new UIItemManagerController(*this);
}
