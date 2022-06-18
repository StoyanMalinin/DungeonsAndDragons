#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#include "../src/Utils/String.h"
#include "../src/Utils/Pair.hpp"
#include "../src/Utils/Vector.hpp"

#include "../src/GameLogic/Entities/Dragon.h"
#include "../src/GameLogic/Entities/Player/Player.h"
#include "../src/GameLogic/Entities/Player/MagePlayer.h"
#include "../src/GameLogic/Entities/Player/WarriorPlayer.h"
#include "../src/GameLogic/Entities/Player/HumanPlayer.h"
#include "../src/GameLogic/Entities/Items/Treasure.h"
#include "../src/GameLogic/Entities/Items/ArmorTreasure.h"
#include "../src/GameLogic/Entities/Items/SpellTreasure.h"
#include "../src/GameLogic/Entities/Items/WeaponTreasure.h"

#include "../src/GameLogic/Entities/Controllers/FightController.h"
#include "../src/GameLogic/Entities/Controllers/RandomFightController.h"
#include "../src/GameLogic/Entities/Controllers/OnlyDownMoveController.h"
#include "../src/GameLogic/Entities/Controllers/OptimalItemManagerController.h"
#include "../src/GameLogic/Entities/Controllers/EvenPointsDistributionController.h"

#include "../src/GameLogic/ItemExchangeMaster.h"
#include "../src/GameLogic/FightMaster.h"

#include "../src/GameLogic/FIleManagement/PlayerView.h"
#include "../src/GameLogic/FIleManagement/GameLogicFileManager.h"

int cmpFloat(float a, float b)
{
	if (fabs(a - b) < 0.00001f) return 0;
	
	if (a < b) return -1;
	return +1;
}

TEST_SUITE("string tests")
{
	TEST_CASE("constructor and getLen")
	{
		String s = "hey";
		CHECK(s.getLen() == 3);
	}

	TEST_CASE("constructor and operator==")
	{
		String s("abcal");
		CHECK(s == String("abcal"));
	}

	TEST_CASE("substring finding 1")
	{
		String s("bababc");
		CHECK(s.findSubstr((const char*)"babc") == true);
		CHECK(s.findSubstr((const char*)"baba") == true);
		CHECK(s.findSubstr((const char*)"abd") == false);
	}

	TEST_CASE("substring finding 2")
	{
		String s("alabala");

		CHECK(s.findSubstr(String("ala")) == true);
		CHECK(s.findSubstr(String("ab")) == true);
		CHECK(s.findSubstr(String("ac")) == false);
	}

	TEST_CASE("substring finding and prefix function")
	{
		String s("alabala");
		size_t* f1 = String::getPrefixFunction("ala", 3);
		size_t* f2 = String::getPrefixFunction("ab", 2);
		size_t* f3 = String::getPrefixFunction("ac", 2);

		CHECK(s.findSubstr(String("ala"), f1) == true);
		CHECK(s.findSubstr(String("ab"), f2) == true);
		CHECK(s.findSubstr(String("ac"), f3) == false);

		delete[] f1;
		delete[] f2;
		delete[] f3;
	}

	TEST_CASE("toString")
	{
		CHECK(String::toString(100) == "100");
		CHECK(String::toString(0) == "0");
	}

	TEST_CASE("string format")
	{
		CHECK(String::format("5", 2, '0', false) == "05");
		CHECK(String::format("5", 2, ' ', true) == "5 ");
	}

	TEST_CASE("concatenation 1")
	{
		String s = "hello";
		s += "world";

		CHECK(s == "helloworld");
		CHECK(String("ala") + String("bala") == String("alabala"));
		CHECK(String("a") + String("") == "a");
	}

	TEST_CASE("concatentaion 2")
	{
		CHECK(String("a") + 'c' == "ac");
		CHECK(String("ala") + 'b' == "alab");
		CHECK('b' + String("ala") + 'b' == "balab");
	}

	TEST_CASE("comparisons")
	{
		CHECK(String("aa") != String("b"));
		CHECK(String("aa") == String("aa"));
		CHECK(String("aa") <= String("aa"));
		CHECK(String("ab") > String("aa"));
		CHECK(String("aac") < String("ab"));
		CHECK(String("adc") >= String("ab"));
	}
}

TEST_SUITE("pair tests")
{
	TEST_CASE("constructor")
	{
		Pair<int, int> p1(2, 3);
		CHECK(p1.first == 2);
		CHECK(p1.second == 3);

		Pair<size_t, char> p2(22, 'y');
		CHECK(p2.first == 22);
		CHECK(p2.second == 'y');
	}
}

TEST_SUITE("vector tests")
{
	TEST_CASE("default constructor")
	{
		Vector <int> v;
		CHECK(v.getLen() == 0);
	}

	TEST_CASE("insert and erase")
	{
		Vector <int> v;

		v.insert(0, 2);//2
		v.insert(1, 3);//2 3
		v.insert(1, 4);//2 4 3
		v.insert(2, 5);//2 4 5 3

		CHECK(v.getLen() == 4);
		CHECK(v[0] == 2);
		CHECK(v[1] == 4);
		CHECK(v[2] == 5);
		CHECK(v[3] == 3);
	
		v.erase(2);//2 4 3

		CHECK(v.getLen() == 3);
		CHECK(v[0] == 2);
		CHECK(v[1] == 4);
		CHECK(v[2] == 3);

		v.erase(0);//4 3

		CHECK(v.getLen() == 2);
		CHECK(v[0] == 4);
		CHECK(v[1] == 3);
	}

	TEST_CASE("pushBack, popFront and resizing")
	{
		const size_t n = 100;

		Vector <int> v;
		for (size_t i = 0; i < n; i++) v.pushBack(i);

		for (size_t i = 0; i < n; i++)
		{
			CHECK(v.getLen() == n - i);
			for (size_t j = 0; j < n - i; j++) CHECK(v[j] == i + j);
			v.popFront();
		}

		CHECK(v.getLen() == 0);
	}
}

TEST_SUITE("treasure and player tests")
{
	TEST_CASE("give armor to player")
	{
		Player p("stoyan", 1, 1, 10, 10, 10, RandomFightController(), OptimalItemManagerController(), OnlyDownMoveController(), EvenPointsDistributionController(), ItemExchangeMaster::getGlobalInstance(), FightMaster::getGlobalInstance());

		Treasure *t1 = new ArmorTreasure(1, 1, ItemExchangeMaster::getGlobalInstance(), Armor("bronq1", 1, 0.20f));
		Treasure *t2 = new ArmorTreasure(1, 1, ItemExchangeMaster::getGlobalInstance(), Armor("bronq2", 1, 0.10f));
		Treasure *t3 = new ArmorTreasure(1, 1, ItemExchangeMaster::getGlobalInstance(), Armor("bronq3", 1, 0.30f));
		
		CHECK(t1->giveToPlayer(p)==true);
		CHECK(t2->giveToPlayer(p)==false);
		CHECK(t3->giveToPlayer(p)==true);
		
		delete t1;
		delete t2;
		delete t3;
	}
}

TEST_SUITE("interaction tests")
{
	TEST_CASE("treasure vs treasure")
	{
		ArmorTreasure t1(1, 1, ItemExchangeMaster::getGlobalInstance(), Armor("strong armor", 1, 0.10f));
		SpellTreasure t2(1, 1, ItemExchangeMaster::getGlobalInstance(), Spell("dark spell", 2, 0.22f));

		t1.interact(&t2);
		CHECK(t1.getIsTaken() == false);
	}

	TEST_CASE("dragon vs treasure")
	{
		Dragon d(1, 1, 10, 10, 10, RandomFightController(), FightMaster::getGlobalInstance());
		ArmorTreasure t(1, 1, ItemExchangeMaster::getGlobalInstance(), Armor("strong armor", 1, 0.10f));

		t.interact(&d);
		CHECK(t.getIsTaken()==false);
	}

	TEST_CASE("player vs treasure 1")
	{
		Player p("stoyan", 1, 1, 10, 10, 10, RandomFightController(), OptimalItemManagerController(), OnlyDownMoveController(), EvenPointsDistributionController(), ItemExchangeMaster::getGlobalInstance(), FightMaster::getGlobalInstance());
		Armor armor("strong armor", 1, 0.10f);
		ArmorTreasure at(1, 1, ItemExchangeMaster::getGlobalInstance(), armor);
		
		Spell spell("dark magic", 2, 0.20f);
		SpellTreasure st(1, 1, ItemExchangeMaster::getGlobalInstance(), spell);

		p.interact(&at);
		st.interact(&p);

		CHECK(p.getArmor() != nullptr);
		CHECK(p.getArmor()->getName()==armor.getName());
		CHECK(p.getArmor()->getLevel()==armor.getLevel());
		CHECK(at.getIsTaken() == true);

		CHECK(p.getSpell() != nullptr);
		CHECK(p.getSpell()->getName() == spell.getName());
		CHECK(p.getSpell()->getLevel() == spell.getLevel());
		CHECK(at.getIsTaken() == true);
	}

	TEST_CASE("player vs treasure 2")
	{
		Player p("stoyan", 1, 1, 10, 10, 10, RandomFightController(), OptimalItemManagerController(), OnlyDownMoveController(), EvenPointsDistributionController(), ItemExchangeMaster::getGlobalInstance(), FightMaster::getGlobalInstance());
		
		Weapon w1("w1", 1, 0.10f), w2("w2", 1, 0.20f);
		WeaponTreasure wt1(1, 1, ItemExchangeMaster::getGlobalInstance(), w1);
		WeaponTreasure wt2(1, 1, ItemExchangeMaster::getGlobalInstance(), w2);

		p.interact(&wt1);
		CHECK(p.getWeapon() != nullptr);
		CHECK(p.getWeapon()->getName() == w1.getName());
		CHECK(p.getWeapon()->getLevel() == w1.getLevel());
		CHECK(wt1.getIsTaken() == true);
	
		wt2.interact(&p);
		CHECK(p.getWeapon() != nullptr);
		CHECK(p.getWeapon()->getName() == w2.getName());
		CHECK(p.getWeapon()->getLevel() == w2.getLevel());
		CHECK(wt2.getIsTaken() == true);
	}

	TEST_CASE("player vs treasure 3")
	{
		Player p("stoyan", 1, 1, 10, 10, 10, RandomFightController(), OptimalItemManagerController(), OnlyDownMoveController(), EvenPointsDistributionController(), ItemExchangeMaster::getGlobalInstance(), FightMaster::getGlobalInstance());

		Weapon w1("w1", 1, 0.10f), w2("w2", 1, 0.05f);
		WeaponTreasure wt1(1, 1, ItemExchangeMaster::getGlobalInstance(), w1);
		WeaponTreasure wt2(1, 1, ItemExchangeMaster::getGlobalInstance(), w2);

		p.interact(&wt1);
		CHECK(p.getWeapon() != nullptr);
		CHECK(p.getWeapon()->getName() == w1.getName());
		CHECK(p.getWeapon()->getLevel() == w1.getLevel());
		CHECK(wt1.getIsTaken() == true);
		
		p.interact(&wt2);
		CHECK(p.getWeapon() != nullptr);
		CHECK(p.getWeapon()->getName() == w1.getName());
		CHECK(p.getWeapon()->getLevel() == w1.getLevel());
		CHECK(wt2.getIsTaken() == false);
	}

	TEST_CASE("player vs dragon")
	{
		Player p("stoyan", 1, 1, 100, 100, 100, RandomFightController(), OptimalItemManagerController(), OnlyDownMoveController(), EvenPointsDistributionController(), ItemExchangeMaster::getGlobalInstance(), FightMaster::getGlobalInstance());
		Dragon d(1, 1, 10, 10, 10, RandomFightController(), FightMaster::getGlobalInstance());
	
		p.interact(&d);
		CHECK(d.isAlive() == false);
	}

	TEST_CASE("dragon vs dragon")
	{
		Dragon d1(1, 1, 10, 10, 10, RandomFightController(), FightMaster::getGlobalInstance());
		Dragon d2(1, 1, 10, 10, 10, RandomFightController(), FightMaster::getGlobalInstance());

		d1.interact(&d2);
		CHECK(!(d1.isAlive()==true && d2.isAlive()==true));
	}

	TEST_CASE("post battle player action")
	{
		for (size_t iter = 0; iter < 50; iter++)
		{
			const float playerInitialHealth = 15;
			Player p("stoyan", 1, 1, 20, 20, playerInitialHealth, RandomFightController(), OptimalItemManagerController(), OnlyDownMoveController(), EvenPointsDistributionController(), ItemExchangeMaster::getGlobalInstance(), FightMaster::getGlobalInstance());
			Dragon d(1, 1, 10, 10, 10, RandomFightController(), FightMaster::getGlobalInstance());

			p.interact(&d);
			CHECK(d.isAlive() == false);
			CHECK(p.getHealth() + 0.000001f >= playerInitialHealth * 0.5);
		}
		
	}
}

TEST_SUITE("controller tests")
{
	TEST_CASE("move player 1")
	{
		Player p("stoyan", 1, 1, 10, 10, 10, RandomFightController(), OptimalItemManagerController(), OnlyDownMoveController(), EvenPointsDistributionController(), ItemExchangeMaster::getGlobalInstance(), FightMaster::getGlobalInstance());

		CHECK(p.peekNxtPosition() == Pair<int, int>(2, 1));
		p.move();
		CHECK(p.getR() == 2);
		CHECK(p.getC() == 1);
	}
}

TEST_SUITE("serialization tests")
{
	TEST_CASE("weapon serialization and deserialization")
	{
		std::stringstream stream;

		Weapon w1("mech", 2, 0.12f);
		w1.serialize(stream);

		Weapon w2(stream);

		CHECK(w2.getName() == "mech");
		CHECK(w2.getLevel() == 2);
		CHECK(cmpFloat(w2.getC(), 0.12f)==0);
	}

	TEST_CASE("player serialization and deserialization")
	{
		std::stringstream stream;

		Player p1("stoyan", 1, 1, 10, 11, 12, RandomFightController(), OptimalItemManagerController(), OnlyDownMoveController(), EvenPointsDistributionController(), ItemExchangeMaster::getGlobalInstance(), FightMaster::getGlobalInstance());
		p1.serialize(stream);

		PlayerView pv(stream);
		Player* p2 = pv.getPlayer(RandomFightController(), OptimalItemManagerController(), OnlyDownMoveController(), EvenPointsDistributionController(), 
			                      ItemExchangeMaster::getGlobalInstance(), FightMaster::getGlobalInstance());

		CHECK(p2 != nullptr);
		CHECK(p2->getName() == "stoyan");
		CHECK(cmpFloat(p2->getStrength(), 10) == 0);
		CHECK(cmpFloat(p2->getMana(), 11) == 0);
		CHECK(cmpFloat(p2->getHealth(), 12) == 0);
		CHECK(p2->getR() == 1);
		CHECK(p2->getC() == 1);

		delete p2;
	}

	TEST_CASE("mage player serialization and deserialization")
	{
		std::stringstream stream;

		MagePlayer p1("stoyan maga", 1, 3, RandomFightController(), OptimalItemManagerController(), OnlyDownMoveController(), EvenPointsDistributionController(), ItemExchangeMaster::getGlobalInstance(), FightMaster::getGlobalInstance());
		p1.serialize(stream);

		PlayerView pv(stream);
		Player* p2 = pv.getPlayer(RandomFightController(), OptimalItemManagerController(), OnlyDownMoveController(), EvenPointsDistributionController(),
			                      ItemExchangeMaster::getGlobalInstance(), FightMaster::getGlobalInstance());

		CHECK(p2 != nullptr);
		CHECK(p2->getName() == "stoyan maga");
		CHECK(cmpFloat(p2->getStrength(), 10) == 0);
		CHECK(cmpFloat(p2->getMana(), 40) == 0);
		CHECK(cmpFloat(p2->getHealth(), 50) == 0);
		CHECK(p2->getR() == 1);
		CHECK(p2->getC() == 3);

		delete p2;
	}

	TEST_CASE("warrior player serialization and deserialization with items")
	{
		std::stringstream stream;

		WarriorPlayer p1("stoyan boec", 1, 3, RandomFightController(), OptimalItemManagerController(), OnlyDownMoveController(), EvenPointsDistributionController(), ItemExchangeMaster::getGlobalInstance(), FightMaster::getGlobalInstance());
		p1.acquireArmor(SharedPtr<Armor>(new Armor("bronq", 2, 15)));
		p1.acquireWeapon(SharedPtr<Weapon>(new Weapon("qtagan", 222, 420)));
		p1.serialize(stream);

		PlayerView pv(stream);
		Player* p2 = pv.getPlayer(RandomFightController(), OptimalItemManagerController(), OnlyDownMoveController(), EvenPointsDistributionController(),
			                      ItemExchangeMaster::getGlobalInstance(), FightMaster::getGlobalInstance());

		CHECK(p2 != nullptr);
		CHECK(p2->getName() == "stoyan boec");
		CHECK(cmpFloat(p2->getStrength(), 40) == 0);
		CHECK(cmpFloat(p2->getMana(), 10) == 0);
		CHECK(cmpFloat(p2->getHealth(), 50) == 0);
		CHECK(p2->getR() == 1);
		CHECK(p2->getC() == 3);
		CHECK(p2->getArmor() != nullptr);
		CHECK(p2->getArmor()->getName()=="bronq");
		CHECK(p2->getArmor()->getLevel()==2);
		CHECK(cmpFloat(p2->getArmor()->getC(), 15)==0);
		CHECK(p2->getWeapon()->getName() == "qtagan");
		CHECK(p2->getWeapon()->getLevel() == 222);
		CHECK(cmpFloat(p2->getWeapon()->getC(), 420) == 0);

		delete p2;
	}

	TEST_CASE("human player serialization and deserialization with items")
	{
		std::stringstream stream;

		HumanPlayer p1("stoyan chovek", 1, 3, RandomFightController(), OptimalItemManagerController(), OnlyDownMoveController(), EvenPointsDistributionController(), 
			           ItemExchangeMaster::getGlobalInstance(), FightMaster::getGlobalInstance());
		p1.acquireArmor(SharedPtr<Armor>(new Armor("bronq", 2, 15)));
		p1.acquireWeapon(SharedPtr<Weapon>(new Weapon("qtagan", 222, 420)));
		p1.serialize(stream);

		Player* p2 = GameLogicFileManager::deserializePlayer(stream, RandomFightController(), OptimalItemManagerController(), OnlyDownMoveController(), 
			                                                 EvenPointsDistributionController(), ItemExchangeMaster::getGlobalInstance(), FightMaster::getGlobalInstance());

		CHECK(p2 != nullptr);
		CHECK(p2->getName() == "stoyan chovek");
		CHECK(cmpFloat(p2->getStrength(), 30) == 0);
		CHECK(cmpFloat(p2->getMana(), 20) == 0);
		CHECK(cmpFloat(p2->getHealth(), 50) == 0);
		CHECK(p2->getR() == 1);
		CHECK(p2->getC() == 3);
		CHECK(p2->getArmor() != nullptr);
		CHECK(p2->getArmor()->getName() == "bronq");
		CHECK(p2->getArmor()->getLevel() == 2);
		CHECK(cmpFloat(p2->getArmor()->getC(), 15) == 0);
		CHECK(p2->getWeapon()->getName() == "qtagan");
		CHECK(p2->getWeapon()->getLevel() == 222);
		CHECK(cmpFloat(p2->getWeapon()->getC(), 420) == 0);

		delete p2;
	}

	TEST_CASE("wall tile serialization and deserialization")
	{
		std::stringstream stream;

		WallTile wt1(19, 11);
		wt1.serialize(stream);
		WallTile* wt2 = GameLogicFileManager::deserializeWallTile(stream);

		CHECK(wt2 != nullptr);
		CHECK(wt2->getR() == 19);
		CHECK(wt2->getC() == 11);
	}

	TEST_CASE("WeaponTreasure serialization and deserialization 1")
	{
		std::stringstream stream;
		
		Weapon w("mech", 2, 0.12f);
		WeaponTreasure wt1(2, 3, ItemExchangeMaster::getGlobalInstance(), w);
		wt1.serialize(stream);
		
		WeaponTreasure* wt2 = GameLogicFileManager::deserializeWeaponTreasure(stream, ItemExchangeMaster::getGlobalInstance());
		
		CHECK(wt2 != nullptr);
		CHECK(wt2->getR() == 2);
		CHECK(wt2->getC() == 3);
		
		HumanPlayer p("stoyan chovek", 1, 3, RandomFightController(), OptimalItemManagerController(), OnlyDownMoveController(), EvenPointsDistributionController(),
			ItemExchangeMaster::getGlobalInstance(), FightMaster::getGlobalInstance());
		p.interact(wt2);

		CHECK(p.getWeapon() != nullptr);
		CHECK(p.getWeapon()->getName() == "mech");
		CHECK(p.getWeapon()->getLevel() == 2);
		CHECK(cmpFloat(p.getWeapon()->getC(), 0.12f)==0);
	}

	TEST_CASE("WeaponTreasure serialization and deserialization 2")
	{
		std::stringstream stream;

		Weapon w("mech", 2, 0.12f);
		WeaponTreasure wt1(2, 3, ItemExchangeMaster::getGlobalInstance(), w);
		wt1.serialize(stream);

		Treasure* wt2 = GameLogicFileManager::deserializeTreasure(stream, ItemExchangeMaster::getGlobalInstance());

		CHECK(wt2 != nullptr);
		CHECK(wt2->getR() == 2);
		CHECK(wt2->getC() == 3);

		HumanPlayer p("stoyan chovek", 1, 3, RandomFightController(), OptimalItemManagerController(), OnlyDownMoveController(), EvenPointsDistributionController(),
			          ItemExchangeMaster::getGlobalInstance(), FightMaster::getGlobalInstance());
		p.interact(wt2);

		CHECK(p.getWeapon() != nullptr);
		CHECK(p.getWeapon()->getName() == "mech");
		CHECK(p.getWeapon()->getLevel() == 2);
		CHECK(cmpFloat(p.getWeapon()->getC(), 0.12f) == 0);
	}
}