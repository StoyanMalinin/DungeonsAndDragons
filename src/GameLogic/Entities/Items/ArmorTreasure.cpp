#include "ArmorTreasure.h"

ArmorTreasure::ArmorTreasure(int r, int c, ItemExchangeMaster& iem, const Armor& armor) : Treasure(r, c, iem), armor(armor)
{}

ArmorTreasure::ArmorTreasure(int r, int c, bool isTaken, ItemExchangeMaster & iem, const Armor & armor) : Treasure(r, c, isTaken, iem), armor(armor)
{}

Treasure* ArmorTreasure::clone() const
{
	return new ArmorTreasure(*this);
}

void ArmorTreasure::serialize(std::ostream& stream) const
{
	std::cout << "ArmorTreasure" << " " << r << " " << c << " " << isTaken << " ";
	armor.serialize(stream);
}

bool ArmorTreasure::giveToPlayer(Player & p)
{
	if(isTaken==true) return false;

	bool res = p.acquireArmor(SharedPtr<Armor>(new Armor(armor)));
	if (res == true) isTaken = true;

	return isTaken;
}
