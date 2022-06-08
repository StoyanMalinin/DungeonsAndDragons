#include "SpellTreasure.h"

SpellTreasure::SpellTreasure(int r, int c, const Spell& spell) : Treasure(r, c), spell(spell)
{}

Treasure* SpellTreasure::clone() const
{
	return new SpellTreasure(*this);
}

bool SpellTreasure::giveToPlayer(Player & p)
{
	if (isTaken == true) return false;

	bool res = p.acquireSpell(SharedPtr<Spell>(new Spell(spell)));
	if (res == true) isTaken = true;

	return isTaken;
}
