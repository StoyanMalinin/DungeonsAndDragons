#ifndef __RANDOMGENERATOR_H
#define __RANDOMGENERATOR_H

#include <random>

class RandomGenerator
{
private:
	std::mt19937 rnd;

public:
	RandomGenerator();
	RandomGenerator(size_t seed);

	uint32_t operator() ();
	int randIntInRange(int l, int r);
	float randFloat(); //returns a float number in the interval [0, 1]
	bool randBool();

	int peekRandIntInRange(int l, int r);
};

#endif

