#ifndef __WEAPONTREASURE_H
#define __WEAPONTREASURE_H

#include "Armor.h"
#include "Treasure.h"

class WeaponTreasure : public Treasure
{
private:
	Weapon weapon;

public:
	WeaponTreasure(int r, int c, ItemExchangeMaster& iem, const Weapon& weapon);
	WeaponTreasure(int r, int c, bool isTaken, ItemExchangeMaster& iem, const Weapon& weapon);
	Treasure* clone() const override;

public:
	void serialize(std::ostream& stream) const override;

public:
	bool giveToPlayer(Player& p) override;
};

#endif // !__WEAPONTREASURE_H

