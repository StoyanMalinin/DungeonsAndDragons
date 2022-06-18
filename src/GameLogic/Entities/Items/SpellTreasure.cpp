#include "SpellTreasure.h"

SpellTreasure::SpellTreasure(int r, int c, ItemExchangeMaster& iem, const Spell& spell) : Treasure(r, c, iem), spell(spell)
{}

SpellTreasure::SpellTreasure(int r, int c, bool isTaken, ItemExchangeMaster & iem, const Spell & spell) : Treasure(r, c, isTaken, iem), spell(spell)
{}

Treasure* SpellTreasure::clone() const
{
	return new SpellTreasure(*this);
}

void SpellTreasure::serialize(std::ostream& stream) const
{
	stream << "SpellTreasure" << " " << r << " " << c << " " << isTaken << " ";
	spell.serialize(stream);
}

bool SpellTreasure::giveToPlayer(Player & p)
{
	if (isTaken == true) return false;

	bool res = p.acquireSpell(SharedPtr<Spell>(new Spell(spell)));
	if (res == true) isTaken = true;

	return isTaken;
}
