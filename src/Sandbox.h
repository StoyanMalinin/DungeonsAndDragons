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
#include "GameLogic/Entities/Controllers/UIPointsDistributionController.h"
#include "GameLogic/Entities/Controllers/EvenPointsDistributionController.h"
#include "GameLogic/Entities/Items/ArmorTreasure.h"

#include "Application.h"

void walkingTest()
{
	ItemExchangeMaster iem;
	FightMaster fm;

	UIHandler uih(std::cin, std::cout);

	GameMap mp(MapProperties(20, 20, 2, 2, 10, 10, 10, 5, 5, 5), 22);
	Player p("stoyan", 0, 0, 10, 10, 10, RandomFightController(), OptimalItemManagerController(), UIMoveController(uih, mp), EvenPointsDistributionController(), iem, fm);

	while (true) p.move();
}

void fightingTest()
{
	ItemExchangeMaster iem;
	FightMaster fm;

	UIHandler uih(std::cin, std::cout);

	Player p("stoyan", 0, 0, 4, 5, 10, UIFightController(uih), OptimalItemManagerController(), OnlyDownMoveController(), EvenPointsDistributionController(), iem, fm);
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
	Player p("stoyan", 0, 0, 4, 5, 10, RandomFightController(), UIItemManagerController(uih), OnlyDownMoveController(), EvenPointsDistributionController(), iem, fm);

	Armor armor("strong armor", 1, 0.10f);
	ArmorTreasure at(1, 1, iem, armor);

	at.interact(&p);

	if (p.getArmor() == nullptr)
		std::cout << "no armor" << '\n';
	else
		std::cout << p.getArmor()->getName() << '\n';
}

void levelTest(size_t seed)
{
	UIHandler uih(std::cin, std::cout);
	GameMap mp(MapProperties(15, 15, 2, 2, 10, 10, 10, 5, 5, 5), seed);

	Player p("stoyan", 0, 0, 4, 5, 20, UIFightController(uih), UIItemManagerController(uih), UIMoveController(uih, mp), UIPointsDistributionController(uih),
		     ItemExchangeMaster::getGlobalInstance(), FightMaster::getGlobalInstance());

	Level level(1, mp, p);
	LevelOutcome outcome = level.play();
	
	if (outcome == LevelOutcome::PLAYER_DIED)
		std::cout << "Player died" << '\n';
	else if (outcome == LevelOutcome::COMPLETED)
		std::cout << "Level successfully completed" << '\n';
}

void playerSerializationTest()
{
	Player p("stoyan", 0, 0, 4, 5, 10, RandomFightController(), OptimalItemManagerController(), OnlyDownMoveController(), EvenPointsDistributionController(), 
		     ItemExchangeMaster::getGlobalInstance(), FightMaster::getGlobalInstance());

	p.setSpell(SharedPtr<Spell>(new Spell("magiq", 2, 20)));
	p.serialize(std::cout);
}

void sandbox()
{
	//playerSerializationTest();

	Application* app = new Application();
	app->run();
	delete app;
}

#endif // !__SANDBOX_H
