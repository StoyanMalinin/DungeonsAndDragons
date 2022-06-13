#ifndef __ARMORTREASURE_H
#define __ARMORTREASURE_H

#include "Armor.h"
#include "Treasure.h"

class ArmorTreasure : public Treasure
{
private:
	Armor armor;

public:
	ArmorTreasure(int r, int c, ItemExchangeMaster& iem, const Armor& armor);
	Treasure* clone() const override;
	
public:
	bool giveToPlayer(Player& p) override;
};

#endif // !__ARMORTREASURE_H

