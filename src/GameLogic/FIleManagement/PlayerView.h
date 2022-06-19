#ifndef __PLAYERVIEW_H
#define __PLAYERVIEW_H

#include <iostream>
#include "../../Utils/String.h"

class Player;
#include "../Entities/Player/Player.h"
//#include "../Entities/Controllers/MoveController.h"
//#include "../Entities/Controllers/FightController.h"
//#include "../Entities/Controllers/ItemManagerController.h"
class ItemManagerController;
class PointsDistributionController;
class ItemExchangeMaster;
class FightMaster;

struct PlayerView
{
public:
	char type;
	String name;
	int r, c;
	float strength, mana, health;
	float initialHealth;
	SharedPtr<Spell> spell;
	SharedPtr<Armor> armor;
	SharedPtr<Weapon> weapon;

	PlayerView(std::iostream& stream);
	void deserialize(std::iostream &stream);
	Player* getPlayer(const FightController& fc, const ItemManagerController& imc, const MoveController& mc, const PointsDistributionController& pdc, ItemExchangeMaster& iem, FightMaster& fm) const;

private:
	void checkForError(std::iostream& stream);
};

#endif // !__PLAYERVIEW_H

