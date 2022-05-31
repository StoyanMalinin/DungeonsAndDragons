#include "GlobalRandomGenerator.h"

RandomGenerator GlobalRandomGenerator::rnd = RandomGenerator();

void GlobalRandomGenerator::reseed(size_t seed)
{
	GlobalRandomGenerator::rnd = RandomGenerator(seed);
}

int GlobalRandomGenerator::randIntInRange(int l, int r)
{
	return rnd.randIntInRange(l, r);
}

float GlobalRandomGenerator::randFloat()
{
	return rnd.randFloat();
}

bool GlobalRandomGenerator::randBool()
{
	return rnd.randBool();
}
