#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#include "../src/String.h"

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
