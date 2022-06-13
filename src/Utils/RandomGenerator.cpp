#include "RandomGenerator.h"
#include "Rectangle.h"

#include <random>
#include <chrono>

RandomGenerator::RandomGenerator() : rnd((uint32_t)std::chrono::steady_clock::now().time_since_epoch().count()) {}
RandomGenerator::RandomGenerator(size_t seed) : rnd(seed) {}

uint32_t RandomGenerator::operator()()
{
	return rnd();
}

int RandomGenerator::randIntInRange(int l, int r)
{
	return l + rnd() % (r - l + 1);
}

float RandomGenerator::randFloat()
{
	const int maxNum = (1 << 10);
	int x = abs((int)rnd());

	return ((float)(x % (maxNum))) / ((float)(maxNum - 1));
}

bool RandomGenerator::randBool()
{
	return rnd() % 2;
}

int RandomGenerator::peekRandIntInRange(int l, int r)
{
	std::mt19937 rndCpy(rnd);
	int res = randIntInRange(l, r);
	rnd = rndCpy;

	return res;
}
