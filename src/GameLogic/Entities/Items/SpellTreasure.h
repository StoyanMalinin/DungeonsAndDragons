#ifndef __SPELLTREASURE_H
#define __SPELLTREASURE_H

#include "Spell.h"
#include "Treasure.h"

class SpellTreasure : public Treasure
{
private:
	Spell spell;

public:
	SpellTreasure(int r, int c, ItemExchangeMaster& iem, const Spell& spell);
	SpellTreasure(int r, int c, bool isTaken, ItemExchangeMaster& iem, const Spell& spell);
	Treasure* clone() const override;

public:
	void serialize(std::ostream& stream) const override;

public:
	bool giveToPlayer(Player& p) override;
};

#endif // !__SPELLTREASURE_H

