#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#include "../src/String.h"
#include "../src/Pair.hpp"
#include "../src/Vector.hpp"

#include "../src/Player.h"
#include "../src/Treasure.h"
#include "../src/ArmorTreasure.h"
#include "../src/SpellTreasure.h"
#include "../src/WeaponTreasure.h"

#include "../src/FightController.h"
#include "../src/RandomFightController.h"
#include "../src/OptimalItemManagerController.h"

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
		Player p("stoyan", 1, 1, 10, 10, 10, RandomFightController(), OptimalItemManagerController());

		Treasure *t1 = new ArmorTreasure(1, 1, Armor("bronq1", 1, 20));
		Treasure *t2 = new ArmorTreasure(1, 1, Armor("bronq2", 1, 10));
		Treasure *t3 = new ArmorTreasure(1, 1, Armor("bronq3", 1, 30));
		
		CHECK(t1->giveToPlayer(p)==true);
		CHECK(t2->giveToPlayer(p)==false);
		CHECK(t3->giveToPlayer(p)==true);
		
		delete t1;
		delete t2;
		delete t3;
	}
}