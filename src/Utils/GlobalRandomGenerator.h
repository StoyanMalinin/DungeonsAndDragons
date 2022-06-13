#ifndef __GLOBALRANDOMGENERATOR_H
#define __GLOBALRANDOMGENERATOR_H

#include "RandomGenerator.h"

class GlobalRandomGenerator
{
private:
	static RandomGenerator rnd;

public:
	GlobalRandomGenerator() = delete;
	GlobalRandomGenerator(const GlobalRandomGenerator& other) = delete;
	GlobalRandomGenerator& operator =(const GlobalRandomGenerator& other) = delete;

public:
	static void reseed(size_t seed);
	static int randIntInRange(int l, int r);
	static float randFloat(); //returns a float number in the interval [0, 1]
	static bool randBool();
};

#endif // !__GLOBALRANDOMGENERATOR_H