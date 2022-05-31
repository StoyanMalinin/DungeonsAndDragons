#include "OptimalItemManagerController.h"

OptimalItemManagerController::OptimalItemManagerController()
{}

OptimalItemManagerController::OptimalItemManagerController(const OptimalItemManagerController& other) : ItemManagerController(other)
{}

bool OptimalItemManagerController::acquireSpell(SharedPtr<Spell> oldSpell, SharedPtr<Spell> newSpell)
{
	if (newSpell.isNull() == true) return false;
	if (oldSpell.isNull() == true || oldSpell->getC() < newSpell->getC()) return true;

	return false;
}

bool OptimalItemManagerController::acquireArmor(SharedPtr<Armor> oldArmor, SharedPtr<Armor> newArmor)
{
	if (newArmor.isNull() == true) return false;
	if (oldArmor.isNull() == true || oldArmor->getC() < newArmor->getC()) return true;

	return false;
}

bool OptimalItemManagerController::acquireWeapon(SharedPtr<Weapon> oldWeapon, SharedPtr<Weapon> newWeapon)
{
	if (newWeapon.isNull() == true) return false;
	if (oldWeapon.isNull() == true || oldWeapon->getC() < newWeapon->getC()) return true;

	return false;
}

ItemManagerController* OptimalItemManagerController::clone() const
{
	return new OptimalItemManagerController(*this);
}
