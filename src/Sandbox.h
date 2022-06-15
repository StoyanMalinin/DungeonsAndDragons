#ifndef __SANDBOX_H

#include "GameLogic/Level.h"
#include "GameLogic/GameMap.h"

#include "GameLogic/FightMaster.h"
#include "GameLogic/ItemExchangeMaster.h"

#include "GameLogic/Entities/Controllers/OptimalItemManagerController.h"
#include "GameLogic/Entities/Controllers/RandomFightController.h"
#include "GameLogic/Entities/Controllers/UIFightController.h"
#include "GameLogic/Entities/Controllers/UIMoveController.h"
#include "GameLogic/Entities/Controllers/UIItemManagerController.h"
#include "GameLogic/Entities/Controllers/OnlyDownMoveController.h"
#include "GameLogic/Entities/Items/ArmorTreasure.h"

void walkingTest()
{
	ItemExchangeMaster iem;
	FightMaster fm;

	UIHandler uih(std::cin, std::cout);

	GameMap mp(MapProperties(20, 20, 2, 2, 10, 10, 10, 5, 5, 5), 22);
	Player p("stoyan", 0, 0, 10, 10, 10, RandomFightController(), OptimalItemManagerController(), UIMoveController(uih, mp), iem, fm);

	while (true) p.move();
}

void fightingTest()
{
	ItemExchangeMaster iem;
	FightMaster fm;

	UIHandler uih(std::cin, std::cout);

	Player p("stoyan", 0, 0, 4, 5, 10, UIFightController(uih), OptimalItemManagerController(), OnlyDownMoveController(), iem, fm);
	Dragon d(1, 1, 5, 5, 5, RandomFightController(), fm);

	while (p.isAlive() == true && d.isAlive() == true)
		p.interact(&d);

	std::cout << p.isAlive() << " " << d.isAlive() << '\n';
}

void itemManagementTest()
{
	ItemExchangeMaster iem;
	FightMaster fm;

	UIHandler uih(std::cin, std::cout);
	Player p("stoyan", 0, 0, 4, 5, 10, RandomFightController(), UIItemManagerController(uih), OnlyDownMoveController(), iem, fm);

	Armor armor("strong armor", 1, 0.10f);
	ArmorTreasure at(1, 1, iem, armor);

	at.interact(&p);

	if (p.getArmor() == nullptr)
		std::cout << "no armor" << '\n';
	else
		std::cout << p.getArmor()->getName() << '\n';
}

void sandbox()
{
	itemManagementTest();
}

#endif // !__SANDBOX_H
