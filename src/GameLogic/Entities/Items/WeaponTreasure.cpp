#include "WeaponTreasure.h"
#include "../../../Utils/SharedPtr.hpp"
#include "../Player/Player.h"

WeaponTreasure::WeaponTreasure(int r, int c, ItemExchangeMaster& iem, const Weapon& weapon) : Treasure(r, c, iem), weapon(weapon)
{}

WeaponTreasure::WeaponTreasure(int r, int c, bool isTaken, ItemExchangeMaster & iem, const Weapon & weapon) : Treasure(r, c, isTaken, iem), weapon(weapon)
{}

Treasure* WeaponTreasure::clone() const
{
	return new WeaponTreasure(*this);
}

void WeaponTreasure::serialize(std::ostream& stream) const
{
	stream << "WeaponTreasure" << " " << r << " " << c << " " << isTaken << " ";
	weapon.serialize(stream);
}

bool WeaponTreasure::giveToPlayer(Player & p)
{
	if (isTaken == true) return false;

	bool res = p.acquireWeapon(SharedPtr<Weapon>(new Weapon(weapon)));
	if (res == true) isTaken = true;

	return isTaken;
}


