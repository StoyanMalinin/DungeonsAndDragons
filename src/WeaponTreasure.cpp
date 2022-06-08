#include "WeaponTreasure.h"

WeaponTreasure::WeaponTreasure(int r, int c, const Weapon& weapon) : Treasure(r, c), weapon(weapon)
{}

Treasure* WeaponTreasure::clone() const
{
	return new WeaponTreasure(*this);
}

bool WeaponTreasure::giveToPlayer(Player & p)
{
	if (isTaken == true) return false;

	bool res = p.acquireWeapon(SharedPtr<Weapon>(new Weapon(weapon)));
	if (res == true) isTaken = true;

	return isTaken;
}


