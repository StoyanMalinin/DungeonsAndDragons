#ifndef __SPELLTREASURE_H
#define __SPELLTREASURE_H

#include "Armor.h"
#include "Treasure.h"

class SpellTreasure : public Treasure
{
private:
	Spell spell;

public:
	SpellTreasure(int r, int c, const Spell& spell);
	Treasure* clone() const override;

public:
	bool giveToPlayer(Player& p) override;
};

#endif // !__SPELLTREASURE_H

