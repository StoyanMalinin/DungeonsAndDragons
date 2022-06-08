#include "ArmorTreasure.h"

ArmorTreasure::ArmorTreasure(int r, int c, const Armor& armor) : Treasure(r, c), armor(armor)
{}

Treasure* ArmorTreasure::clone() const
{
	return new ArmorTreasure(*this);
}

bool ArmorTreasure::giveToPlayer(Player & p)
{
	if(isTaken==true) return false;

	bool res = p.acquireArmor(SharedPtr<Armor>(new Armor(armor)));
	if (res == true) isTaken = true;

	return isTaken;
}
